void
init_psi(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    double CCE,
    double CCD,
    double psi[TOTAL_NODES + 1][N])
{
    for (int m = 0; m < HALF_N; m++)
    {
        psi[0][m] = CCE;
        psi[TOTAL_NODES][HALF_N + m] = CCD;
    }
}

void
init_h(
    int NUM_REGS,
    int NUM_NODES[NUM_REGS],
    double ESP_REGS[NUM_REGS],
    double h[NUM_REGS])
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        h[i] = ESP_REGS[i] / NUM_NODES[i];
    }
}

void
init_mi_h(
    int N,
    int NUM_REGS,
    double MI[N],
    double H[NUM_REGS],
    double mi_h[NUM_REGS][N])
{
    int i, m;

    for (i = 0; i < NUM_REGS; i++)
    {
        for (m = 0; m < N; m++)
        {
            mi_h[i][m] = MI[m] / H[i];
        }
    }
}

void
init_half_sigma_t(
    int NUM_REGS,
    double SIGMA_T[NUM_REGS],
    double half_sigma_t[NUM_REGS])
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        half_sigma_t[i] = SIGMA_T[i] / 2;
    }
}

void
init_half_sigma_s0(
    int NUM_REGS,
    double SIGMA_S0[NUM_REGS],
    double half_sigma_s0[NUM_REGS])
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        half_sigma_s0[i] = SIGMA_S0[i] / 2;
    }
}
