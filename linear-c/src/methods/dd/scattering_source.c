/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../../include/core/common.h"

void
calc_scattering_source(
    const int N,
    const int TOTAL_NODES,
    const double W[SCR N],
    const double H_S0[SCR TOTAL_NODES],
    const double psim[SCR (TOTAL_NODES * N)],
    double ss[SCR TOTAL_NODES])
{
    for (int _ = 0; _ < TOTAL_NODES; _++) {ss[_] = 0.0;}

    const double* restrict actual_psim = &psim[0];

    for (int m = 0; m < N; m++)
    {
        const double w = W[m];
        for (int j = 0; j < TOTAL_NODES; j++)
        {
            ss[j] += w * actual_psim[j];
        }
        actual_psim += TOTAL_NODES;
    }

    for (int _ = 0; _ < TOTAL_NODES; _++) {ss[_] *= H_S0[_];}
}
