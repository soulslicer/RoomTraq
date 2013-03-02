# RoomTraq

This is the device and app that I built for NUS Hackers Hackathon 2013 in a space of 24 hours alone and somehow won 3rd prize :) 

Basically, it is a little box you can bring around and place it at any event or space you like. As people walk in and out, the sensors and it's internal algorithms will count if someone has entered or exited. Then every 30s, it automatically updates the server with the latest results, including what time the person entered or left!

![ScreenShot](http://a-iats.com/App/Image.png)

### Hardware Needed

1. Breadboard or Solder+Circuit board
2. Arduino Nano
3. RN-XV WiFly Device
4. 2 URM37 Ultrasonic Sensors
4. 5V Power source (USB Battery perhaps)
5. Sparkfun Explorer breakout+Sparkfun explorer USB
6. 10k resistor, LEDS and 220 ohm resistors
7. Wires and wire stripper
8. USB Cables

### Software Needed

1. ArduinoCore Library (Provided)
2. Atmel Studio Windows (C++ and Atmega328P)
3. Mac OSX, Xcode and iPhone (If you want to use another platform, read below)
4. CoolTerm for Windows
5. FTDI USB Driver for OSX/Windows


## Setting Up Software/Hardware

The exact connections to be made to your arduino board can be found on RoomTraq.cpp in the Arduino folder. Read RoomTraq.cpp on how to use the device. You need to set-up RoomTraq for the first time by hitting the interrupt button and using the app to send your SSID and password.

Currently, the various states can only be seen serially, but you can add LED's to your project to see it cycle through the different modes. Once the system goes into a CONNECTED mode, it was start checking for users and sending data every 30s.

PHP files can be loaded onto a server of your choice, but both the WiFly.cpp sendResponse() function's URL and TableController.m URL must be changed accordingly

## Notes

* iOS App written in Objective-C
* GCDAsynSocket Library used for telnet connection
* Arduino programmed in C++ via Atmel Studio
* ArduinoCore packaged by me, contains all required drivers. Using Arduino Libraries
* All devices can be purchased from Robot-R-Us (Singapore)

LICENSE
-------

Copyright (C) 2012 by Raaj

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
