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
	std::cout << buffer << std::endl;


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
	std::cout << buffer[0] << std::endl;
	return -1;
}