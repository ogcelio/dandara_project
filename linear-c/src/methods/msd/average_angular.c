/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/average_angular.h"

#include "../../../include/core/common.h"
#include <math.h>

void
calc_average_angular(
    const int N,
    const double SIGMA_TH,
    const double INV_SIGMA_TH,
    const double PART_SOL,
    const double ALPHA[SCR N],
    const double LAMBDA[SCR N],
    const double NU[SCR N],
    const double EIGENVEC[SCR (N * N)],
    double psim[SCR N])
{
    const double * restrict eigenvec = &EIGENVEC[0];
    for (int m = 0; m < N; m++)
    {
        double sum = 0.0;
        for (int l = 0; l < N; l++)
        {
            if (LAMBDA[l] > 0)
            {
                sum += ALPHA[l] * NU[l] * eigenvec[l] * (1 - exp(-SIGMA_TH * LAMBDA[l]));
            }
            else
            {
                sum += ALPHA[l] * NU[l] * eigenvec[l] * (exp(SIGMA_TH * LAMBDA[l]) - 1);
            }
        }

        psim[m] = INV_SIGMA_TH * sum + PART_SOL;

        eigenvec += N;
    }
}
