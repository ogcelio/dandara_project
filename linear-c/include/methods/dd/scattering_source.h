/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef SCATTERING_SOURCE_H
#define SCATTERING SOURCE_H

void calc_scattering_source(
    const int N,
    const int TOTAL_NODES,
    const double W[SCR N],
    const double H_S0[SCR TOTAL_NODES],
    const double psim[SCR (TOTAL_NODES * N)],
    double ss[SCR TOTAL_NODES]);

#endif
