/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

void
calc_sol_dif(
    int N,
    int HALF_N,
    int NODE,
    double PSI[][N],
    double PART_SOL[N],
    double sol_dif[N])
{
    for (int i = 0; i < HALF_N; i++)
    {
        sol_dif[i] = PSI[NODE][i] - PART_SOL[i];
        sol_dif[i + HALF_N] = PSI[NODE + 1][i + HALF_N] - PART_SOL[i + HALF_N];
    }
}
