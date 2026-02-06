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
    const double psi[SCR ((TOTAL_NODES + 1) * N)],
    double fi[SCR (TOTAL_NODES + 1)])
{
    const double * restrict actual_psi = &psi[0];

    // for de j pode ser paralelizado
    for (int j = 0; j <= TOTAL_NODES; j++)
    {
        double sum = 0.0;

        for (int m = 0; m < N; m++)
        {
            sum += W[m] * actual_psi[m];
        }

        fi[j] = 0.5 * sum;

        actual_psi += N;
    }
}
