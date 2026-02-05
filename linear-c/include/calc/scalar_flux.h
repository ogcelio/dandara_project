/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../core/common.h"

#ifndef SCALAR_FLUX_H
#define SCALAR_FLUX_H

void calc_scalar_flux(
    const int N,
    const int TOTAL_NODES,
    const double W[SCR N],
    const double psi[SCR ((TOTAL_NODES + 1) * N)],
    double fi[SCR (TOTAL_NODES + 1)]);

#endif
