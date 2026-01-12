void
calc_foward(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    int NUM_REGS,
    int NUM_NODES[],
    int REGS[NUM_REGS],
    double SS[TOTAL_NODES],
    double Q[NUM_REGS],
    double HALF_SIGMA_T[NUM_REGS],
    double MI_H[NUM_REGS],
    double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, num_nodes;
    int node = 1;

    for (i = 0; i < NUM_REGS; i++)
    {
        num_nodes = NUM_NODES[i];

        for (j = 0; j < num_nodes; j++, node++)
        {
            for (m = 0; m < HALF_N; m++)
            {
                psi[node][m] = (SS[node - 1] + Q[i] + (MI_H[m] - HALF_SIGMA_T[i]) * psi[node - 1][m])
                                /
                                (MI_H[m] + HALF_SIGMA_T[i]);
            }
        }
    }
}

void
calc_backward(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    int NUM_REGS,
    int NUM_NODES[],
    int REGS[],
    double SS[],
    double Q[],
    double HALF_SIGMA_T[],
    double MI_H[],
    double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, num_nodes;
    int node = TOTAL_NODES - 1;

    for (i = NUM_REGS; i > 0; i--)
    {
        num_nodes = NUM_NODES[i];

        for (j = 0; j < num_nodes; j++, node--)
        {
            for (m = HALF_N; m < N; m++)
            {
                psi[node][m] = (SS[node] + Q[i] - (MI_H[m] + HALF_SIGMA_T[i]) * psi[node + 1][m])
                                /
                                (HALF_SIGMA_T[i] - MI_H[m]);
            }
        }
    }
}
