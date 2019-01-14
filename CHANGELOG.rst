^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for inclinometer_solar2 package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TODO
------------------
* implement full check to see what message arrives in buffer.
* implement logger
* implement different responses than OK in sendCmd()
* add purge method
* change output to RADs

KNOWN BUGS
------------------
* When the buffer is purged it is directly full again for some reason. Occurs at rate = 50 ms.

NICE TO HAVE
------------------
* Online configuration and zeroing


0.1 (2019-01-08)
------------------
* rate was removed from initialization as it can anyway only be changed after the serial port was started
* added methods to adjust parameters of sensor
* turns off continuous transmission to change settings
* parses sensor values to port
* test script start.rb works
* filled update hook and configuration hook
* started programming orogen component
* sending a command works and the respons can be read.
* managed to concatenate message from two uint8_t variables
* sending a test command to configure the sensor works
* fixed timing issue and buffer parsing
* parsing of serial readout implemented
* readout of continuous serial communication works