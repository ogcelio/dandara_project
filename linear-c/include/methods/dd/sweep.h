/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef SWEEP_H
#define SWEEP_H

void calc_foward(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const int REGS[SCR NUM_REGS],
    const double Q[SCR NUM_REGS],
    const double FW[SCR (NUM_REGS * N)],
    const double BW[SCR (NUM_REGS * N)],
    const double SS[SCR TOTAL_NODES],
    double psi[SCR ((TOTAL_NODES + 1) * N)]);

void calc_backward(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const int REGS[SCR NUM_REGS],
    const double Q[SCR NUM_REGS],
    const double FW[SCR (NUM_REGS * N)],
    const double BW[SCR (NUM_REGS * N)],
    const double SS[SCR TOTAL_NODES],
    double psi[SCR ((TOTAL_NODES + 1) * N)]);

#endif
