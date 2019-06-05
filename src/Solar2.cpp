#include <iostream>
#include <chrono>
#include <string.h>

#include "Solar2.hpp"

using namespace inclinometer_solar2;

Solar2::Solar2():
	Driver(MAX_PACKET_SIZE)
{
}


Solar2::~Solar2()
{
    // Close the serial connection if it is still valid
    if(isValid())
    {
        close();
    }
}

int Solar2::getFileDescriptor()
{
    return Driver::getFileDescriptor();
}

bool Solar2::update(float * inclinations)
{
    uint8_t packet[MAX_PACKET_SIZE];

	auto start = std::chrono::high_resolution_clock::now();

	try
	{
		// Timeout at 10s as this is the lowest transmission rate in streaming mode
		readPacket(packet, MAX_PACKET_SIZE, 10000, 10000);

		if (print_stream)
		{

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>((stop - start)/1000);

			// PRINT TIME
			// To get the value of duration use the count()
			// member function on the duration object
			printf("--------------\n");
			printf("Elapsed: %ld ms\n", duration.count());


			// PRINT MESSAGE
			printf("Received Message [°]: ");

			// find \r and replace with readable \r
			for (int j = 0; j < 18; j++)
			{
				if (packet[j] == '\r')	std::cout << "\\r";
				else std::cout << packet[j];
			}

			printf("\n");
		}

		// TODO: implement full check to see what message it is.
		// Parse the message into a float array if the message does not contain an OK.
		if(packet[0] != 'O' && packet[1] != 'K'){

			// Extract the x & y values from the message packet.
		 	uint8_t x[9];
	    uint8_t y[9];

	    std::copy(packet, packet + 8, x);
	    std::copy(packet + 9, packet + 18, y);

	    // Parse the uint8_t arrays into a a float array containing x & y.
			float incs[2] = {ui8tof(x), ui8tof(y)};
			// Copy data to provided address
			memcpy(inclinations, &incs, sizeof(incs));
		}

		return true;
	}

	catch(int timeout_error)
	{
        std::cout << "inclinometerSolar2_Driver: Timeout error" << std::endl;
        return false;
	}

}


bool Solar2::sendMsg(uint8_t *message, bool expect_ok, uint8_t *response)
{
	int count = 0;
    uint8_t packet[MAX_PACKET_SIZE];

	writePacket(message, sizeof(message)/sizeof(message[0])-1);
	if(expect_ok)
	{
		while (count < 100) {
			readPacket(packet, MAX_PACKET_SIZE, 2*rate_, 2*rate_);
			if(packet[0] == 'O' && packet[1] == 'K') return true;

			count++;
		}
		printf("ERROR: No response received!\n");
	}
	else
	{
		return true;
	}

	return false;
}

bool Solar2::sendCmd(std::string command, bool expect_ok, uint8_t *response)
{
	if(!sendMsg(strtoui8t("stpcasc"), true))
	{
		printf("ERROR: Couldn't stop the stream.\n");
		return false;
	}

	if(!sendMsg(strtoui8t(command), 	expect_ok))
	{
		printf("ERROR: Couldn't send the command.\n");
		return false;
	}

	if(!sendMsg(strtoui8t("setcasc"),false))
	{
		printf("ERROR: Couldn't start the stream.\n");
		return false;
	}

	return true;
}


// Early testing function for commands.
bool Solar2::setRate(int rate)
{
	if (rate >= 50 && rate <= 9999)
	{

		// Build message
		rate_ = rate;
		std::string rate_message = "str";

		for (int i=0; i<(4-nrOfDigits(rate)); i++) rate_message.append("0");

		rate_message.append(std::to_string(rate));


		if(sendCmd(rate_message,true))
		{
			printf("Rate successfully set to %i ms.\n", rate);
			return true;
		}

	}
	else
	{
		printf("ERROR: chosen rate out of bounds.\n");
	}

	return false;
}


// Virtual method, must be redefined to process custom packet
int Solar2::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{
	if(print_buffer)
	{
		printf("BS:\t%lu \n", buffer_size);
		printf("BF:\t\t");
		for (uint j = 0; j < buffer_size; j++)
		{
			if (buffer[j] == '\r')	std::cout << "\\r";
			else std::cout << buffer[j];
		}
		printf("\n");
	}

	if(purge_buffer){
		purge_buffer = false;

		printf("\t\t\t\t\t\t\t\t%lu Elements removed from buffer.\n", buffer_size);
		return -buffer_size;
	}


	if(buffer[0] == 'O' && buffer[1] == 'K' && buffer_size >= 2)
	{
		// printf("\t\t\t\t\t\t\t\tReceived OK from sensor.\n");
		return 2;
	}

	// One packet must be at least as long as a message
	if(buffer_size < CASC_MSG_SIZE)
	{
		return 0;
	}

	// Each message paket is terminated with a carriage return (\r).
	// Once this is in the buffer at the last position (17) we know the whole message is in the buffer
	// and the message size is returned.
	if (buffer[17] == '\r')
	{
		if (print_stream)
		{

			// PRINT LOST BYTES
			printf("Discarded Bytes: %d\n", removed_bytes);
			removed_bytes = 0;
		}

		return CASC_MSG_SIZE;
	}

	removed_bytes = removed_bytes + 1;

	// Remove one byte at beginning of the device buffer
	return -1;
}


float Solar2::ui8tof(uint8_t *input) {
    std::string s;
    s.assign(input, input + sizeof(input));
    return std::stof(s);
}

uint8_t* Solar2::strtoui8t(std::string input) {

    uint8_t* output;
    output = new uint8_t[input.length() + 1];
    memcpy(output, input.c_str(), input.length() + 1);
    return output;
}

int Solar2::nrOfDigits(int input){

	int length = 1;
	while ( input /= 10 )
	   length++;
	return length;
}
