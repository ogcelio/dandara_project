/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/solution_difference.h"

#include "../../../include/core/common.h"

void
calc_solution_difference(
    const int N,
    const int HALF_N,
    const int NODE,
    const int TOTAL_NODES,
    const double PART_SOL,
    const double PSI[SCR ((TOTAL_NODES + 1) * N)],
    double sol_dif[SCR N])
{
    int MULTI = NODE * N;
    int MULTI_HN = MULTI + N + HALF_N;

    for (int n = 0; n < HALF_N; n++)
    {
        sol_dif[n] = PSI[MULTI + n] - PART_SOL;

        sol_dif[n + HALF_N] = PSI[MULTI_HN + n] - PART_SOL;
    }
}
