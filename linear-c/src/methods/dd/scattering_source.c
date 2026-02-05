/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../../include/core/common.h"

void
calc_scattering_source(
    const int N,
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int REGS[SCR NUM_REGS],
    const int NUM_NODES[SCR NUM_REGS],
    const double W[SCR N],
    const double HALF_SIGMA_S0[SCR NUM_REGS],
    const double psim[SCR (TOTAL_NODES * N)],
    double ss[SCR TOTAL_NODES])
{
    int node = 0;
    const double * restrict actual_psim = &psim[0];
    for (int r = 0; r < NUM_REGS; r++)
    {
        const int num_nodes = NUM_NODES[r];
        const double h_s0 = HALF_SIGMA_S0[r];

        for (int j = 0; j < num_nodes; j++, node++)
        {
            double sum = 0.0;

            for (int n = 0; n < N; n++)
            {
                sum += W[n] * actual_psim[n];
            }

            ss[node] = h_s0 * sum;
            actual_psim += N;
        }
    }
}
