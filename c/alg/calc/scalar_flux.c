void
calc_fi(int N, int TOTAL_NODES, double W[N], double psi[TOTAL_NODES + 1][N], double fi[TOTAL_NODES + 1])
{
    double sum;
    int j, m;

    for (j = 0; j < (TOTAL_NODES + 1); j++)
    {
        sum = 0;
        for (m = 0; m < N; m++)
        {
            sum += W[m] * psi[j][m];
        }
        fi[j] = 0.5 * sum;
    }
}
