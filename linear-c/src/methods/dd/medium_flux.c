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
    const double * restrict actual_psi = &psi[0];
    double * restrict actual_psim = &psim[0];

    for (int m = 0; m < N; m++)
    {
        for (int j = 0; j < TOTAL_NODES; j++)
        {
            actual_psim[m] = 0.5 * (actual_psi[j] + actual_psi[j + 1]);
        }

        actual_psim += TOTAL_NODES;
        actual_psi += (TOTAL_NODES + 1);
    }
}
