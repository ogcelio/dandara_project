#include <math.h>

double
relative_deviation(int TOTAL_NODES, double initial_fi[], double final_fi[])
{
    double result_higher = fabs(initial_fi[0] - final_fi[0]);
    double final_higher = fabs(final_fi[0]);

    double result_temp, final_temp;

    for (int j = 1; j < (TOTAL_NODES + 1); j++)
    {
        result_temp = fabs(initial_fi[j] - final_fi[j]);

        if (result_temp > result_higher)
            result_higher = result_temp;

        final_temp = fabs(final_fi[j]);

        if (final_temp > final_higher)
            final_higher = final_temp;
    }

    return (result_higher / final_higher);
}
