/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/scattering_source.h"

#include "../../../include/core/common.h"

double
scattering_source(
    const int N,
    const double HALF_SIGMA_S0,
    const double W[SCR N],
    const double PSIM[SCR N])
{
    double sum = 0.0;

    for (int n = 0; n < N; n++)
    {
        sum += W[n] * PSIM[n];
    }

    return (HALF_SIGMA_S0 * sum);
}
