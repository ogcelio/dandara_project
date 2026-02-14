/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/calc/absorption_rate.h"

#include "../../include/core/common.h"
#include <stdio.h>
#include <stdlib.h>

double
*abs_rate(
    const int NUM_REGS,
    const int TOTAL_NODES,
    const int NUM_NODES[SCR NUM_REGS],
    const int REGS[SCR NUM_REGS],
    const double AVG_FI[SCR TOTAL_NODES],
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS],
    const double SIGMA_S0[SCR NUM_REGS])
{
    double *abs_rate = malloc(NUM_REGS * sizeof(double));
    if (!abs_rate)
    {
        printf("Error in the memory allocation of the ABSORPTION RATE.");
        return NULL;
    }

    int node = 0;

    for (int r = 0; r < NUM_REGS; r++)
    {
        double sigma_a = SIGMA_T[r] - SIGMA_S0[r];

        double sum = 0;
        for (int j = 0; j < NUM_NODES[r]; j++, node++)
        {
            sum += AVG_FI[node];
        }
        abs_rate[r] = sum * sigma_a * H[r];
    }

    return abs_rate;
}
