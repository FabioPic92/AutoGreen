#!/bin/bash

set -e 

echo "Processing Dataset..."
python3 src/process_dataset.py

echo "Generating yaml file..."
python3 src/generate_yaml.py

echo "Creating file yolo.py..."
python3 src/convert_to_yolo.py

echo "Done!"