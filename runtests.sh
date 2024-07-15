#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Call the makefile to build the project
make

# Directory containing test files
TEST_DIR="tests"
OUTPUT_DIR="testoutputs"

# Check if the tests directory exists
if [ ! -d "$TEST_DIR" ]; then
    echo "Tests directory not found!"
    exit 1
fi

# Create the testoutputs directory if it doesn't exist
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# Run the chess executable for each test file in the tests directory
for test_file in "$TEST_DIR"/*.in; 
do
    # Extract the base name of the test file (without directory and extension)
    base_name=$(basename "$test_file" .in)
    output_file="$OUTPUT_DIR/$base_name.out"
    
    echo "Running test with input file: $test_file, output file: $output_file"
    ./chess < "$test_file" > "$output_file"
done
