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

    inclinometer_solar2::Solar2 inclinometer;

    std::string const port = "/dev/ttyUSB0";

    // TODO This error catcher doesn't seem to work...
    if(!inclinometer.openSerial(port, 38400))
    {
        std::cout << "Could not open device on port " << port << std::endl;
        return 0;
    }
    else printf("Port %s opened.\n", port.c_str());

    int action;
    float inclinations[2];

    while(true){
        printf("-----------------------------------------\n");
        printf("1. Display data to terminal.\n");
        printf("2. Change transmission rate.\n");
        printf("3. Send string command (works only for 'OK' responses atm).\n");
        printf("-----------------------------------------\n");
        
        scanf("%i", &action);


        switch (action) {

            case 1:
                inclinometer.activatePrinting();
                while(true)
                {
                    inclinometer.update(inclinations);
                }
                break;  

            case 2:
                int rate;

                printf("Input Transmission Rate [50, 9999 ms]:\n");
                scanf("%i", &rate);
                inclinometer.setRate(rate);
                break;  

            case 3:
                char command[256];

                printf("Input the command to be sent:\n");
                scanf( "%255s" , command);

                inclinometer.sendCmd(std::string(command), true);
                break;  
        }


    }

    printf("Program finished. \n");

    return 0;
}
