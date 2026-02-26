#!/bin/bash

# Compilar C (CMake)
echo "--- Compilando C ---"
cd linear-c
mkdir -p build && cd build
cmake ..
make -j$(nproc)
cd ../..

# Compilar Rust (Cargo)
echo -e "\n--- Compilando Rust ---"
cd linear-rust
cargo build --release
cd ..

echo -e "\n--- Processo de Compilação Finalizado ---"
