int
trivial_solution_test(int NUM_REGS, int REGS[NUM_REGS], double CCE, double CCD, double Q[])
{
    if (CCE != 0 && CCD != 0)
        return 0;

    int reg;

    for (int i = 0; i < NUM_REGS; i++)
    {
        reg = REGS[i] - 1;

        if (Q[reg] != 0)
            return 0;
    }

    return 1;
}
