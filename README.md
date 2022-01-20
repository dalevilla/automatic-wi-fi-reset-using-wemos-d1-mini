# automatic-wi-fi-reset-using-wemos-d1-mini
This device resets the wi-fi router when internet connection is lost.

# Hardware
* Wemos D1 Mini (esp8266)
The controls of the project. It is connected to the Wi-Fi, and upon disconnection, activates the normally closed relay to reset the router.
* 5VDC Mechanical Relay SRD-05VDC-SL-C
Connected to the 12V 2A router wall adapter. The relay has a a maximum contact capacity of 7A 28VDC [1].
* 5VDC Wall adapter
Micro-usb to power the Wemos.

#References
[1] https://www.circuitbasics.com/wp-content/uploads/2015/11/SRD-05VDC-SL-C-Datasheet.pdf
