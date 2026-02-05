/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "../core/common.h"

#ifndef RELATIVE_DEVIATION_H
#define RELATIVE_DEVIATION_H

double relative_deviation(
    const int TOTAL_NODES,
    const double initial_fi[SCR (TOTAL_NODES + 1)],
    const double final_fi[SCR (TOTAL_NODES + 1)]);

#endif
