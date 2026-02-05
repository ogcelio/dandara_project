/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../core/common.h"

#ifndef ABSORPTION_RATE_H
#define ABSORPTION_RATE_H

double *abs_rate(
    const int NUM_REGS,
    const int TOTAL_NODES,
    const int NUM_NODES[SCR NUM_REGS],
    const int REGS[SCR NUM_REGS],
    const double AVG_FI[SCR TOTAL_NODES],
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS],
    const double SIGMA_S0[SCR NUM_REGS]);

#endif
