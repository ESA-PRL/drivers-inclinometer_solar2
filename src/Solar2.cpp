#include <iostream>
#include <chrono>

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
		readPacket(buffer, MAX_PACKET_SIZE, 2000, 2000);
	
		auto stop = std::chrono::high_resolution_clock::now(); 
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>((stop - start)/1000); 
		  
		// PRINT TIME
		// To get the value of duration use the count() 
		// member function on the duration object 
		printf("--------------\n");
		printf("Elapsed: %d ms\n", duration.count());


		// PRINT MESSAGE
		printf("Received Message: ");

		// find \r and replace with readable \r
		for (int j = 0; j < 18; j++)
		{
			if (buffer[j] == '\r')	std::cout << "\\r";
			else std::cout << buffer[j];
		}

		printf("\n");

		return true;
	}

	catch(int timeout_error)
	{
        std::cout << "inclinometerSolar2_Driver: Timeout error" << std::endl;
        return false;
	}

}


// Virtual method, must be redefined to process custom packet
int Solar2::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{
	// if (buffer[0] == '\r')	std::cout << "r";
	// else std::cout << buffer[0] << "    " <<  buffer_size << std::endl;
	

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
		// PRINT LOST BYTES
		printf("Discarded Bytes: %d\n", removed_bytes);
		removed_bytes = 0;
		return CASC_MSG_SIZE;
	}

	removed_bytes = removed_bytes + 1;

	// Remove one byte at beginning of the device buffer 
	return -1;
}