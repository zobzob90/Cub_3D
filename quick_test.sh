#!/bin/bash

echo "Testing memory fix by running cub3D briefly..."

# Kill any existing cub3D processes
pkill -f cub3D 2>/dev/null

# Run with valgrind for just a moment
timeout 3s valgrind --leak-check=full --show-leak-kinds=definite --error-exitcode=1 ./cub3D maps/valid/tuto.cub 2>&1 | grep -E "(definitely lost|ERROR SUMMARY)" || echo "Test timed out - checking process..."

echo "Memory test completed."
