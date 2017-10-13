#!/bin/bash

foo=${ARDUINO_PATH?"Need to set ARDUINO_PATH"}

${ARDUINO_PATH}/arduino-builder -compile -hardware ${ARDUINO_PATH}/hardware -tools ${ARDUINO_PATH}/tools-builder -tools ${ARDUINO_PATH}/hardware/tools/avr -built-in-libraries ${ARDUINO_PATH}/libraries -libraries ../../libraries -fqbn=teensy:avr:teensy31:usb=hid,speed=48,opt=oslto,keys=en-us -warnings=all -verbose ./teensy3-prototype.ino && ${ARDUINO_PATH}/hardware/tools/teensy_reboot
