#include <iostream>
#include "Solar2.hpp"
#include <chrono>

int main(int argc, char** argv)
{
    solar2::Solar2 inclinometer(50);

    int testint = 22;
    uint8_t test8 = testint;

    std::cout << unsigned(test8) << std::endl;

    std::string const port = "/dev/ttyUSB0";

    // TODO This error catcher doesn't seem to work...
    if(!inclinometer.openSerial(port, 38400))
    {
        std::cout << "Could not open device on port " << port << std::endl;
    }

    int action;

    printf("Welcome to the inclinometer test software\n");
    printf("-----------------------------------------\n");
    printf("1. Read data for 5 s.\n");
    printf("2. Change transmission rate.\n");
    scanf("%i", &action);

    switch (action) {

        case 1:
            // auto start = std::chrono::high_resolution_clock::now(); 
            // auto stop = std::chrono::high_resolution_clock::now(); 
            // auto duration = std::chrono::duration_cast<std::chrono::microseconds>((stop - start)/1000); 

            // long int runtime = 5000; // How long the sensor is read out in ms


            // float *output;
            // while(duration < runtime)
            printf("in case 1\n");
            while(true)
            {
            	inclinometer.update();    	
                // stop = std::chrono::high_resolution_clock::now(); 
                // duration = std::chrono::duration_cast<std::chrono::microseconds>((stop - start)/1000); 
            }
        
        case 2:
            printf("in case 2\n");

            int rate;

            scanf("Enter rate in ms: %i", &rate);
            inclinometer.setRate(rate);
    }


    printf("Program finished. \n");

    return 0;
}
