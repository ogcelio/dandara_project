#!/bin/bash

# Function to benchmark a command
benchmark() {
    local cmd=$1
    local name=$2
    local iterations=1000
    local total_time=0

    echo "Benchmarking $name ($iterations runs)..."

    for ((i=1; i<=iterations; i++)); do
        # Record start time in nanoseconds
        start=$(date +%s%N)
        
        # Execute binary and suppress output
        $cmd > /dev/null 2>&1
        
        # Record end time
        end=$(date +%s%N)
        
        # Calculate delta
        delta=$((end - start))
        total_time=$((total_time + delta))
    done

    # Calculate average in milliseconds using awk
    average=$(echo "$total_time $iterations" | awk '{printf "%.6f", ($1 / $2) / 1000000}')
    echo "Average execution time for $name: $average ms"
    echo "------------------------------------------"
}

# Run benchmarks for Rust
benchmark "./linear-rust/target/release/exec_dd" "Rust exec_dd"
benchmark "./linear-rust/target/release/exec_msd" "Rust exec_msd"
