/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef ANGULAR_FLUX_H
#define ANGULAR_FLUX_H

void calc_angular_flux(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const int NODE,
    const double SS,
    const double Q,
    const double SIGMA_T,
    const double MI_H[SCR N],
    const double PSIM[SCR N],
    double psi[SCR ((TOTAL_NODES + 1) * N)]);

#endif
