/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/calc/scalar_flux.h"

#include "../../include/core/common.h"

void
calc_scalar_flux(
    const int N,
    const int TOTAL_NODES,
    const double W[SCR N],
    const double psi[SCR (TOTAL_NODES * N)],
    double fi[SCR (TOTAL_NODES + 1)])
{
    for (int _ = 0; _ < (TOTAL_NODES + 1); _++) {fi[_] = 0.0;}

    const double* restrict actual_psi = &psi[0];

    for (int m = 0; m < N; m++)
    {
        const double w = W[m];
        for (int j = 0; j < (TOTAL_NODES + 1); j++)
        {
            fi[j] += w * actual_psi[j];
        }

        actual_psi += (TOTAL_NODES + 1);
    }

    for (int _ = 0; _ < (TOTAL_NODES + 1); _++) {fi[_] *= 0.5;}
}
