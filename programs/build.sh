#!/bin/bash

# Check if a file name was passed as a parameter
if [ -z "$1" ]; then
    echo "Usage: $0 source_file_name_without_extension [output_directory]"
    exit 1
fi

SOURCE_NAME="$1"
OUTPUT_DIR="${2:-../bin}"  # Default output directory is "bin" if not specified
SOURCE_FILE="${SOURCE_NAME}.c"
OUTPUT_FILE="${OUTPUT_DIR}/${SOURCE_NAME}"

# Check if the source file exists
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file '$SOURCE_FILE' does not exist."
    exit 1
fi

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

# Compile the source file
gcc "$SOURCE_FILE" -o "$OUTPUT_FILE"

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful: $OUTPUT_FILE"
else
    echo "Compilation failed."
    exit 1
fi
