/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../include/methods/msd.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char* input_path = "data/input.json";
    const char* output_path = "data/output.json";

    printf("Starting Modified Spectral Deterministic calculation...\n");
    int result = modified_spectral_deterministic(input_path, output_path);

    if (result == 0) {
        printf("Modified Spectral Deterministic calculation completed successfully.\n");
        printf("Output written to %s\n", output_path);
    } else {
        printf("Modified Spectral Deterministic calculation failed.\n");
    }

    return result;
}
