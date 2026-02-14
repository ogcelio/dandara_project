/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../../core/common.h"

#ifndef SOLUTION_DIFFERENCE_H
#define SOLUTION_DIFFERENCE_H

void calc_solution_difference(
    const int N,
    const int HALF_N,
    const int NODE,
    const int TOTAL_NODES,
    const double PART_SOL,
    const double PSI[SCR ((TOTAL_NODES + 1) * N)],
    double sol_dif[SCR N]);

#endif
