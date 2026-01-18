#include "trival_solution_test.h"

int
trivial_solution_test(
    int NUM_REGS,
    int REGS[NUM_REGS],
    double CCE,
    double CCD,
    double Q[NUM_REGS])
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
