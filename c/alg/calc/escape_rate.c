/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "escape_rate.h"
#include <math.h>

void
calc_escape_rate(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    double MI[N],
    double W[N],
    double PSI[TOTAL_NODES + 1][N],
    double escape_rate[2])
{
    int n;
    double sum_0 = 0;
    double sum_H = 0;

    for (n = 0; n < HALF_N; n++)
    {
        sum_0 += fabs(MI[n + HALF_N] * W[n + HALF_N] * PSI[0][n + HALF_N]);

        sum_H += fabs(MI[n] * W[n] * PSI[TOTAL_NODES][n]);
    }

    escape_rate[0] = sum_0;
    escape_rate[1] = sum_H;
}
