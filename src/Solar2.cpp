#include <iostream>
#include "Solar2.hpp"

using namespace solar2;

Solar2::Solar2():
	Driver(512),
	rate_(9999)
{

}

Solar2::Solar2(unsigned int rate):
	Driver(512),
	rate_(rate)
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


bool Solar2::update()
{
	// try
	// {	

    uint8_t buffer[MAX_PACKET_SIZE];
	readPacket(buffer, MAX_PACKET_SIZE, 1000, 1000);
	printf("%s\n", buffer);

	return true;
	// // }

	// catch(int timeout_error)
	// {
 //        std::cout << "inclinometerSolar2_Driver: Timeout error" << std::endl;
 //        return false;
	// }

}


// Virtual method, must be redefined to process custom packet
int Solar2::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{
	// One packet must be at least as long as a message
	if(buffer_size < CASC_MSG_SIZE)
	{
		return 0;
	}

	// Each message paket is terminated with a carriage return (\r).
	// Once this is in the buffer we know the whole message is in the buffer
	// and the message size is returned.
	if (buffer[0] == '\r')
	{
		return CASC_MSG_SIZE;
	}

	// Remove one byte at beginning of the device buffer 
	return -1;
}