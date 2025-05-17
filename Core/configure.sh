#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SCRIPT_DIR/external/paho/paho.mqtt.cpp/build/src
