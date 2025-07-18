#!/bin/bash

# Test script to check memory leaks after gun firing
echo "Testing memory leaks with gun firing..."

# Run the program with valgrind and simulate some activity
timeout 5s valgrind --leak-check=full --show-leak-kinds=definite ./cub3D maps/valid/tuto.cub 2>&1 | tee valgrind_output.txt

# Check if there are definite memory leaks
if grep -q "definitely lost: 0 bytes" valgrind_output.txt; then
    echo "✅ SUCCESS: No definite memory leaks detected!"
else
    echo "❌ FAILURE: Memory leaks still present"
    grep "definitely lost" valgrind_output.txt
fi

# Clean up
rm -f valgrind_output.txt
