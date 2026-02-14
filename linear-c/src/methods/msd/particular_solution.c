/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/particular_solution.h"

#include "../../../include/core/common.h"
#include <stdio.h>
#include <stdlib.h>

double
*particular_solution(
    const int NUM_REGS,
    const double Q[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS],
    const double SIGMA_S0[SCR NUM_REGS])
{
    double *part_sol = malloc(NUM_REGS * sizeof(double));
    if (!part_sol)
    {
        printf("Error in the memory allocation of the PARTICULAR SOLUTION.");
        return NULL;
    }


    for (int r = 0; r < NUM_REGS; r++)
    {
        part_sol[r] = Q[r] / (SIGMA_T[r] - SIGMA_S0[r]);
    }

    return part_sol;
}
