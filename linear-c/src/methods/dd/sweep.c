/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../../include/core/common.h"

void
calc_sweep(
    const int N,
    const int TOTAL_NODES,
    const double Q[SCR TOTAL_NODES],
    const double SS[SCR TOTAL_NODES],
    const double FW[SCR (TOTAL_NODES * N)],
    const double BW[SCR (TOTAL_NODES * N)],
    double psi[SCR ((TOTAL_NODES + 1) * N)])
{
    double* restrict actual_psi = &psi[0];
    for (int m = 0; m < N; m++)
    {
        for (int j = 0; j < TOTAL_NODES; j++)
        {
            actual_psi[j + 1] = (SS[j] + Q[j] - actual_psi[j] * FW[j]) * BW[j];
        }
        actual_psi += (TOTAL_NODES + 1);
    }
}
