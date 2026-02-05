/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/calc/trivial_solution_test.h"

#include "../../include/core/common.h"

int
trivial_solution_test(
    const int NUM_REGS,
    const int REGS[SCR NUM_REGS],
    const double CCE,
    const double CCD,
    const double Q[SCR NUM_REGS])
{
    if (CCE != 0 || CCD != 0)
        return 0;

    for (int i = 0; i < NUM_REGS; i++)
    {
        if (Q[i] != 0)
            return 0;
    }

    return 1;
}
