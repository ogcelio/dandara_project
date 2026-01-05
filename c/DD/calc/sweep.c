void
calc_foward(int N, int TOTAL_NODES, int NUM_REGS, int NUM_NODES[], int REGS[], double H[], double SS[], double Q[], double SIGMA_T[], double MI[N], double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, reg, num_nodes;
    int node = 1;
    int HALF_N = N / 2;

    double half_sigma_t;
    double mi_h[HALF_N];


    for (i = 0; i < NUM_REGS; i++)
    {
        reg = REGS[i] - 1;
        num_nodes = NUM_NODES[i];

        half_sigma_t = SIGMA_T[reg] / 2;

        for (m = 0; m < HALF_N; m++)
        {
            mi_h[m] = MI[m] / H[i];
        }

        for (j = 0; j < num_nodes; j++, node++)
        {
            for (m = 0; m < HALF_N; m++)
            {
                psi[node][m] = ((mi_h[m] - half_sigma_t) * psi[node - 1][m] + SS[node - 1] + Q[reg]) / (mi_h[m] + half_sigma_t);
            }
        }
    }

}
