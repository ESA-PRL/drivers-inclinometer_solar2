#ifndef _SOLAR2_HPP_
#define _SOLAR2_HPP_

#include <iodrivers_base/Driver.hpp>

// Use cutecom for Ubuntu Console

namespace inclinometer_solar2
{
    class Solar2: public iodrivers_base::Driver
    {
    public:
        Solar2();

        ~Solar2();

        bool update(float * inclinations);
        void activatePrinting() {print_stream = true;}
        bool setRate(int rate);
        // Sends a command using sendMsg() but deactivates the streaming first and activates the streaming afterwards again.
        // set expect_ok to true if the response should be an ok and otherwise provide the location of the response.
        bool sendCmd(std::string command,  bool expect_ok=false, uint8_t *response = NULL); 
        // Sends the message and reads a response
        // TODO: Implement responses other than OK
        bool sendMsg(uint8_t *message,  bool expect_ok=false, uint8_t *response = NULL); // Sends a single message and checks if the answer is OK. Change expect_ok to false if the response is different than OK.
        
        // Functions for fd-driven tasks
        int getFileDescriptor();
        // int getIndex();

    private:
        static const unsigned int CASC_MSG_SIZE = 18;  // Number of bytes per message in streaming mode
        static const unsigned int MAX_PACKET_SIZE = 512; // Has to be >512
        mutable int removed_bytes = 0; // Number bytes that were removed during 
        mutable bool purge_buffer = false;
        int rate_;

        // Plot Options
        bool print_stream = false;
        bool print_buffer = false;

        // Comm functions
        virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
        bool writeMessage();

        // Helper functions
        float ui8tof(uint8_t *input);   // parses a uint8_t ascii array into a float.
        uint8_t* strtoui8t(std::string input);
        int nrOfDigits(int input);

    };
}

#endif