#!/bin/bash

foo=${ARDUINO_PATH?"Need to set ARDUINO_PATH"}

${ARDUINO_PATH}/arduino-builder -compile -hardware ${ARDUINO_PATH}/hardware -hardware ~/.arduino15/packages -tools ${ARDUINO_PATH}/tools-builder -tools ${ARDUINO_PATH}/hardware/tools/avr -tools ~/.arduino15/packages -built-in-libraries ${ARDUINO_PATH}/libraries -libraries ../../libraries -fqbn=adafruit:samd:adafruit_feather_m0  -vid-pid=0X239A_0X800B -warnings=all -verbose ./arcadestick_usb.ino
