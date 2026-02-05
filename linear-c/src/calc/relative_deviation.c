/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/calc/relative_deviation.h"

#include "../../include/core/common.h"

#include <math.h>

double
relative_deviation(
    const int TOTAL_NODES,
    const double initial_fi[SCR (TOTAL_NODES + 1)],
    const double final_fi[SCR (TOTAL_NODES + 1)])
{
    double result_higher = fabs(initial_fi[0] - final_fi[0]);
    double final_higher = fabs(final_fi[0]);

    double result_temp, final_temp;

    for (int j = 1; j <= TOTAL_NODES; j++)
    {
        result_temp = fabs(initial_fi[j] - final_fi[j]);
        result_higher = fmax(result_higher, result_temp);

        final_temp = fabs(final_fi[j]);
        final_higher = fmax(final_higher, final_temp);
    }

    return (result_higher / final_higher);
}
