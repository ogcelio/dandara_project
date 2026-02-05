/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../../include/core/common.h"

void
calc_foward(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const int REGS[SCR NUM_REGS],
    const double Q[SCR NUM_REGS],
    const double FW[SCR (NUM_REGS * N)],
    const double BW[SCR (NUM_REGS * N)],
    const double SS[SCR TOTAL_NODES],
    double psi[SCR ((TOTAL_NODES + 1) * N)])
{
    int node = 0;
    double * restrict actual_psi = &psi[N];
    double * restrict minus_half = &psi[0];

    const double * restrict fw = &FW[0];
    const double * restrict bw = &BW[0];

    for (int r = 0; r < NUM_REGS; r++)
    {
        int num_nodes = NUM_NODES[r];
        double q = Q[r];

        for (int j = 0; j < num_nodes; j++, node++)
        {
            double ss = SS[node];

            for (int m = 0; m < HALF_N; m++)
            {
                actual_psi[m] = (ss + q - fw[m] * minus_half[m]) * bw[m];
            }

            actual_psi += N;
            minus_half += N;
        }

        fw += N;
        bw += N;
    }
}

void
calc_backward(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const int REGS[SCR NUM_REGS],
    const double Q[SCR NUM_REGS],
    const double FW[SCR (NUM_REGS * N)],
    const double BW[SCR (NUM_REGS * N)],
    const double SS[SCR TOTAL_NODES],
    double psi[SCR ((TOTAL_NODES + 1) * N)])
{
    int node = TOTAL_NODES - 1;
    double * restrict actual_psi = &psi[(TOTAL_NODES - 1) * N];
    double * restrict plus_half = &psi[TOTAL_NODES * N];
    const double * restrict fw = &FW[(NUM_REGS - 1) * N];
    const double * restrict bw = &BW[(NUM_REGS - 1) * N];

    for (int r = NUM_REGS - 1; r >= 0; r--)
    {
        int num_nodes = NUM_NODES[r];
        double q = Q[r];

        for (int j = 0; j < num_nodes; j++, node--)
        {
            double ss = SS[node];

            for (int m = HALF_N; m < N; m++)
            {
                actual_psi[m] = (ss + q - fw[m] * plus_half[m]) * bw[m];
            }

            actual_psi -= N;
            plus_half -= N;
        }

        fw -= N;
        bw -= N;
    }
}
