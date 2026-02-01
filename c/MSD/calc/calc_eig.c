#include <lapacke.h>

void
calc_eig(
    int N,
    int NUM_REGS,
    double W[N],
    double MI[N],
    double C0[NUM_REGS],
    double eigenvalues[NUM_REGS][N],
    double eigenvectors[NUM_REGS][N][N])
{
    int i, j;
    double c0_mi, inv_mi;
    double wi[N];    // Autovalores Imaginários (nao utilizado)
    double A[N][N];

    /* LAPACKE_dgeev:
       - 'N': Não calcula autovetores à esquerda (ganha tempo)
       - 'V': Calcula os autovetores à direita
    */
    for (int r = 0; r < NUM_REGS; r++)
    {
        for (i = 0; i < N; i++)
        {
            inv_mi = 1 / MI[i];
            c0_mi = -C0[r] * 0.5 * inv_mi;
            for (j = 0; j < N; j++)
            {
                A[i][j] = c0_mi * W[j];
            }
            A[i][i] += inv_mi;
        }

        LAPACKE_dgeev(
            LAPACK_ROW_MAJOR,
            'N',
            'V',
            N,
            &A[0][0],
            N,
            eigenvalues[r],
            wi,
            NULL,
            N,
            &eigenvectors[r][0][0],
            N);
    }
}
