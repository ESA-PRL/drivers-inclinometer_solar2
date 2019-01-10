^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for inclinometer_solar2 package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TODO
------------------
* fill update hook and configuration hook


KNOWN BUGS
------------------
* When the buffer is purged it is directly full again for some reason. Occurs at rate = 50 ms. 

NICE TO HAVE
------------------
* convert the input int into uint8_t
* turn off continuous transmission to change settings
  OR
  use threads for reading and writing
* configuration of sensor at class initialization
* add methods to adjust parameters of sensor



0.0.1 (2019-01-08)
------------------
* started programming orogen component
* sending a command works and the respons can be read.
* managed to concatenate message from two uint8_t variables
* sending a test command to configure the sensor works
* fixed timing issue and buffer parsing
* parsing of serial readout implemented
* readout of continuous serial communication works