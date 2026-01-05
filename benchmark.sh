#!/bin/bash

# 1. Executar Script Python
echo "--- Iniciando Python ---"
python3 quadrature.py

# 2. Compilar e Executar C
# É boa prática compilar antes de executar para garantir que a versão mais recente rode
echo -e "\n--- Compilando e Executando C ---"
gcc programa.c -o programa_c
if [ $? -eq 0 ]; then
    ./programa_c
else
    echo "Erro na compilação do C"
fi

# 3. Executar Script Julia
echo -e "\n--- Iniciando Julia ---"
julia script.jl

echo -e "\n--- Processo Finalizado ---"
