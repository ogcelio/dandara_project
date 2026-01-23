/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "absorption_rate.h"

void
calc_abs_rate(
    int NUM_NODES[],
    int NUM_REGS,
    int REGS[NUM_REGS],
    double AVG_FI[],
    double H[NUM_REGS],
    double SIGMA_T[],
    double SIGMA_S0[],
    double abs_rate[NUM_REGS])
{
    int i, j, num_nodes;
    int node = 0;
    double sum, sigma_a;

    for (i = 0; i < NUM_REGS; i++)
    {
        sigma_a = SIGMA_T[i] - SIGMA_S0[i];

        num_nodes = NUM_NODES[i];
        sum = 0;
        for (j = 0; j < num_nodes; j++, node++)
        {
            sum += AVG_FI[node];
        }

        abs_rate[i] = sum * sigma_a * H[i];
    }
}
