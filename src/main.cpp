#include <iostream>
#include "Solar2.hpp"

int main(int argc, char** argv)
{
    solar2::Solar2 inclinometer(50);

    std::string const port = "/dev/ttyUSB0";

    // TODO This error catcher doesn't seem to work...
    if(!inclinometer.openSerial(port, 38400))
    {
        std::cout << "Could not open device on port " << port << std::endl;
    }

    // float *output;
    while(true)
    {
    	inclinometer.update();    	
    }

    printf("Program finished. \n");

    return 0;
}
