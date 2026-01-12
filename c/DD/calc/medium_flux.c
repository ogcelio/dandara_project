void
calc_psim(
    int N,
    int TOTAL_NODES,
    double psi[TOTAL_NODES + 1][N],
    double psim[TOTAL_NODES + 1][N])
{
    int j, m;

    for (j = 0; j < TOTAL_NODES; j++)
    {
        for (m = 0; m < N; m++)
        {
            psim[j][m] = 0.5 * (psi[j + 1][m] + psi[j][m]);
        }
    }
}
