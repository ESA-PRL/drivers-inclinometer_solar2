#include <iostream>
#include "Solar2.hpp"
#include <chrono>

int main(int argc, char** argv)
{

    printf("Welcome to the inclinometer test software\n");

    solar2::Solar2 inclinometer(50);

    std::string const port = "/dev/ttyUSB0";

    // TODO This error catcher doesn't seem to work...
    if(!inclinometer.openSerial(port, 38400))
    {
        std::cout << "Could not open device on port " << port << std::endl;
        return 0;
    }
    else printf("Port %s opened.\n", port.c_str());

    int action;

    printf("-----------------------------------------\n");
    printf("1. Display data to terminal.\n");
    printf("2. Change transmission rate.\n");
    scanf("%i", &action);

    switch (action) {

        case 1:
            while(true)
            {
            	inclinometer.update();    	
            }
        
        case 2:
            int rate;

            // printf("Input Transmission Rate [50, 9999 ms]");
            // scanf("%i", &rate);
            inclinometer.setRate(rate);
            while(true)
            {
                inclinometer.update();      
            }
    }


    printf("Program finished. \n");

    return 0;
}
