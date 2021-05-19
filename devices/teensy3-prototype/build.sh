#!/bin/bash

foo=${ARDUINO_PATH?"Need to set ARDUINO_PATH"}

${ARDUINO_PATH}/arduino-cli compile -b teensy:avr:teensy31:usb=hid,speed=48,opt=oslto,keys=en-us --libraries ../../libraries  --warnings all --verbose teensy3-prototype.ino && ${ARDUINO_PATH}/hardware/tools/teensy_reboot
