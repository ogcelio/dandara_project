/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef EIGEN_H
#define EIGEN_H

void calc_eig(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double W[SCR N],
    const double MI[SCR N],
    const double C0[NUM_REGS],
    double lambda[SCR (NUM_REGS * N)],
    double eigenvec[SCR (NUM_REGS * N * N)]);

#endif
