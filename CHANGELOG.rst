^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for inclinometer_solar2 package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TODO
------------------
* turn off continuous transmission to change settings
  OR
  use threads for reading and writing
* add methods to adjust parameters of sensor
* implement full check to see what message arrives in buffer.

KNOWN BUGS
------------------
* When the buffer is purged it is directly full again for some reason. Occurs at rate = 50 ms.

NICE TO HAVE
------------------
* convert the input int into uint8_t
* configuration of sensor at class initialization


0.1 (2019-01-08)
------------------
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