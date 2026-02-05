/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef MEDIUM_FLUX_H
#define MEDIUM_FLUX_H

void calc_medium_flux(
    const int N,
    const int TOTAL_NODES,
    const double psi[SCR (TOTAL_NODES + 1) * N],
    double psim[SCR (TOTAL_NODES * N)]);

#endif
