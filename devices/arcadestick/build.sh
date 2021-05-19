#!/bin/bash

foo=${ARDUINO_PATH?"Need to set ARDUINO_PATH"}

${ARDUINO_PATH}/arduino-cli compile -b adafruit:samd:adafruit_feather_m0 --libraries ../../libraries --warnings all --verbose ./arcadestick.ino
