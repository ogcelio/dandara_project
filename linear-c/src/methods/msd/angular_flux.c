/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/angular_flux.h"

#include "../../../include/core/common.h"

void
calc_angular_flux(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const int NODE,
    const double SS,
    const double Q,
    const double SIGMA_T,
    const double MI_H[SCR N],
    const double PSIM[SCR N],
    double psi[SCR ((TOTAL_NODES + 1) * N)])
{
    const double ssq = SS + Q;

    double *plus_half = &psi[(NODE + 1) * N];
    double *minus_half = &psi[NODE * N];

    for (int m = 0; m < HALF_N; m++)
    {
        plus_half[m] = MI_H[m] * (ssq - SIGMA_T * PSIM[m]) + minus_half[m];

        int n = m + HALF_N;

        minus_half[n] = MI_H[n] * (ssq - SIGMA_T * PSIM[n]) + plus_half[n];
    }
}
