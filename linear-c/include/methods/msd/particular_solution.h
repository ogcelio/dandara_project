/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef PARTICULAR_SOLUTION_H
#define PARTICULAR_SOLUTION_H

double *particular_solution(
    const int NUM_REGS,
    const double Q[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS],
    const double SIGMA_S0[SCR NUM_REGS]);

#endif
