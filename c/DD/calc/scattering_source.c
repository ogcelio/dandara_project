void
calc_ss(
    int N,
    int NUM_REGS,
    int REGS[NUM_REGS],
    int NUM_NODES[],
    double W[N],
    double HALF_SIGMA_S0[NUM_REGS],
    double psim[N],
    double ss[])
{
    double sum;
    int i, j, n, num_nodes;
    int node = 0;

    for (i = 0; i < NUM_REGS; i++)
    {
        num_nodes = NUM_NODES[i];
        for (j = 0; j < num_nodes; j++, node++)
        {
            sum = 0;

            for (n = 0; n < N; n++)
            {
                sum += W[n] * psim[n];
            }

            ss[node] = (HALF_SIGMA_S0[i] * sum);
        }
    }
}
