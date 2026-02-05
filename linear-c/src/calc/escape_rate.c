/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/calc/escape_rate.h"

#include "../../include/core/common.h"
#include <stdlib.h>
#include <math.h>

double
*escape_rate(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const double MI[SCR N],
    const double W[SCR N],
    const double PSI[SCR ((TOTAL_NODES + 1) * N)])
{
    const long TOTAL_NUMS = TOTAL_NODES * N;

    double *esc_rate = calloc(2, sizeof(double));

    for (int m = 0; m < HALF_N; m++)
    {
        esc_rate[0] += fabs(MI[m + HALF_N] * W[m + HALF_N] * PSI[m + HALF_N]);

        esc_rate[1] += fabs(MI[m] * W[m] * PSI[TOTAL_NUMS + m]);
    }

    return esc_rate;
}
