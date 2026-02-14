/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef ALPHA_MATRIX_H
#define ALPHA_MATRIX_H

double *alpha_matrix(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double SIGMA_TH[SCR NUM_REGS],
    const double LAMBDA[SCR (NUM_REGS * N)],
    const double EIGENVECTORS[SCR (NUM_REGS * N * N)]);

#endif
