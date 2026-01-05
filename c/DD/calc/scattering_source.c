void
calc_ss(int N, int NUM_REGS, int REGS[NUM_REGS], int NUM_NODES[], double W[N], double SIGMA_S0[], double psim[N], double ss[])
{
    double sum;
    int i, j, n, reg, num_nodes;
    int node = 0;

    for (i = 0; i < NUM_REGS; i++)
    {
        reg = REGS[i] - 1;
        num_nodes = NUM_NODES[i];
        for (j = 0; j < num_nodes; j++, node++)
        {
            sum = 0;

            for (n = 0; n < N; n++)
            {
                sum += W[n] * psim[n];
            }

            ss[node] = ((SIGMA_S0[reg] / 2) * sum);
        }
    }
}
