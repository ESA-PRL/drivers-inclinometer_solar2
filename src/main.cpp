#include <iostream>
#include <cstring>
#include "Solar2.hpp"
#include <chrono>

float ui8tof(uint8_t *input) {
    std::string s;
    s.assign(input, input + sizeof(input));
    return std::stof(s);
}

int main(int argc, char** argv)
{

    printf("Welcome to the inclinometer test software\n");

    inclinometer_solar2::Solar2 inclinometer(50);

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

    float inclinations[2];

    switch (action) {

        case 1:
            while(true)
            {
            	inclinometer.update(inclinations);
            }
        
        case 2:
            int rate;

            // printf("Input Transmission Rate [50, 9999 ms]");
            // scanf("%i", &rate);
            inclinometer.setRate(rate);
            while(true)
            {
                inclinometer.update(inclinations);      
            }
    }


    printf("Program finished. \n");

    return 0;
}
