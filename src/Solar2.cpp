#include <iostream>
#include <chrono>
#include <string.h>

#include "Solar2.hpp"

using namespace solar2;

Solar2::Solar2():
	Driver(512),
	rate_(9999)
{
	removed_bytes = 0;
}

Solar2::Solar2(unsigned int rate):
	Driver(512),
	rate_(rate)
{
	removed_bytes = 0;
	print_stream = false;
	print_buffer = false;
}

Solar2::~Solar2()
{
    // Close the serial connection if it is still valid
    if(isValid())
    {
        close();
    }
}

// int Temperature::getFileDescriptor()
// {
//     return Driver::getFileDescriptor();
// }

bool Solar2::update()
{
    uint8_t buffer[MAX_PACKET_SIZE];
	
	auto start = std::chrono::high_resolution_clock::now(); 
	
	try
	{	
		// Timeout at 10s as this is is lowest transmission rate in streaming mode
		readPacket(buffer, MAX_PACKET_SIZE, 10000, 10000);
	
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
			printf("Received Message: ");

			// find \r and replace with readable \r
			for (int j = 0; j < 18; j++)
			{
				if (buffer[j] == '\r')	std::cout << "\\r";
				else std::cout << buffer[j];
			}

			printf("\n");
		}

		return true;
	}

	catch(int timeout_error)
	{
        std::cout << "inclinometerSolar2_Driver: Timeout error" << std::endl;
        return false;
	}

}

// Early testing function for commands.
bool Solar2::setRate(int rate)
{
	if (rate >= 50 || rate <= 9999)
	{

		// Assign rate to new_rate
		uint8_t buffer[8] = "str0000";
		uint8_t new_rate[5] = "0050"; // new_rate is added to message

		std::copy(&new_rate[0],&new_rate[3],&buffer[3]);

		printf("Rate set to: %s [ms]\n", new_rate);

		purge_buffer = true;
		writePacket(buffer, 7);

		// // Read Response
		// uint8_t response[MAX_PACKET_SIZE];
		// readPacket(response, MAX_PACKET_SIZE, 1000, 1000);

		// printf("RESPONSE:\n", response);

		rate_ = rate;
		return 1;
	}
	return 0;
}


bool writeMessage()
{
	printf("WriteMessage Function\n");
	return 1;
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
	// if(buffer_size > 2*CASC_MSG_SIZE){

		purge_buffer = false;

		printf("\t\t\t\t\t\t\t\t%lu elements removed from buffer.\n", buffer_size);
		return -buffer_size;
	}


	if(buffer[0] == 'O' && buffer[1] == 'K')
	{	
		printf("\t\t\t\t\t\t\t\tReceived OK from sensor.\n");
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