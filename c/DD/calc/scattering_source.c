#include "scattering_source.h"

void
calc_ss(
    int N,
    int TOTAL_NODES,
    int NUM_REGS,
    int REGS[NUM_REGS],
    int NUM_NODES[NUM_REGS],
    double W[N],
    double HALF_SIGMA_S0[NUM_REGS],
    double psim[TOTAL_NODES][N],
    double ss[TOTAL_NODES])
{
    double sum, half_sigma_s0;
    int i, j, n, num_nodes;
    int node = 0;

    for (i = 0; i < NUM_REGS; i++)
    {
        num_nodes = NUM_NODES[i];
        half_sigma_s0 = HALF_SIGMA_S0[i];
        for (j = 0; j < num_nodes; j++, node++)
        {
            sum = 0;
            for (n = 0; n < N; n++)
            {
                sum += W[n] * psim[node][n];
            }

            ss[node] = half_sigma_s0 * sum;
        }
    }
}
