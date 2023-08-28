#!/bin/sh  # This shebang line will work for both dash and bash

# Get the number of iterations from the command-line arguments or use a default value
iterations=${1:-10000}

echo iterations is $iterations

# Get the current time in seconds and nanoseconds
start_s=$(date +%s)
start_ns=$(date +%N)

# Your loop here
i=0
while [ $i -lt $iterations ]; do
    /bin/true
    i=$((i + 1))
done

# Get the current time in seconds and nanoseconds again
end_s=$(date +%s)
end_ns=$(date +%N)

# Calculate the elapsed time in floating-point seconds
elapsed_time=$(echo "scale=9; $end_s - $start_s + ($end_ns - $start_ns) / 1000000000" | bc)

# Calculate iterations per second
iterations_per_second=$(echo "scale=2; $iterations / $elapsed_time" | bc)

echo "Elapsed time: $elapsed_time seconds"
echo "Iterations per second: $iterations_per_second"
echo

