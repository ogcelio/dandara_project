#include "../include/methods/dd.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char* input_path = "data/input.json";
    const char* output_path = "data/output.json";

    printf("Starting Diamond Difference calculation...\n");
    int result = diamond_difference(input_path, output_path);

    if (result == 0) {
        printf("Diamond Difference calculation completed successfully.\n");
        printf("Output written to %s\n", output_path);
    } else {
        printf("Diamond Difference calculation failed.\n");
    }

    return result;
}
