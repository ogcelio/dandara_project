/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../../include/core/common.h"

void
calc_medium_flux(
    const int N,
    const int TOTAL_NODES,
    const double psi[SCR (TOTAL_NODES + 1) * N],
    double psim[SCR (TOTAL_NODES * N)])
{
    const double * restrict plus_half = &psi[N];
    const double * restrict minus_half = &psi[0];
    double * restrict actual_psim = &psim[0];

    for (int j = 0; j < TOTAL_NODES; j++)
    {
        for (int m = 0; m < N; m++)
        {
            actual_psim[m] = 0.5 * (plus_half[m] + minus_half[m]);
        }

        plus_half += N;
        minus_half += N;
        actual_psim += N;
    }
}
