#ifndef _SOLAR2_HPP_
#define _SOLAR2_HPP_

#include <iodrivers_base/Driver.hpp>

// Use cutecom for Ubuntu Console

namespace solar2
{
    class Solar2: public iodrivers_base::Driver
    {
    public:
        Solar2();

        Solar2(unsigned int rate);
        ~Solar2();

        bool update();
        bool setRate(int rate);

        // Functions for orogen
        // int getFileDescriptor();
        // int getIndex();

    private:
        unsigned int rate_; // Transmission rate in ms [50-999ms]
        static const unsigned int CASC_MSG_SIZE = 18;  // Number of bytes per message in streaming mode
        static const unsigned int MAX_PACKET_SIZE = 512; // Has to be >512
        mutable int removed_bytes;
        
        virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
        bool writeMessage();
    };
}

#endif