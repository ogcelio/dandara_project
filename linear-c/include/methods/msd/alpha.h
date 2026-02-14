/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef ALPHA_H
#define ALPHA_H

void calc_alpha(
    const int N,
    const double ALPHA_MATRIX[SCR (N * N)],
    const double SOL_DIF[SCR N],
    double alpha[SCR N]);

#endif
