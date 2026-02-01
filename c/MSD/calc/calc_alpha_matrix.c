/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include <math.h>
#include <cblas.h>
#include <lapacke.h>

void
calc_alpha_matrix(
    int N,
    int HALF_N,
    int NUM_REGS,
    double H[NUM_REGS],
    double SIGMA_TH[NUM_REGS],
    double EIGENVALUES[NUM_REGS][N],
    double EIGENVECTORS[NUM_REGS][N][N],
    double alpha_matrix[NUM_REGS][N][N])
{
    int i, j, r;

    #pragma omp parallel for schedule(static)
    for (r = 0; r < NUM_REGS; r++)
    {
        int ipiv[N];
        int info;
        double (*am_reg)[N] = (double (*)[N])alpha_matrix[r];
        double (*evectors)[N] = (double (*)[N])EIGENVECTORS[r];
        double (*evalues) = (double *) EIGENVALUES[r];

        for (i = 0; i < HALF_N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (evalues[j] > 0)
                {
                    // UPPER HALF OF THE MATRIX
                    am_reg[i][j] = evectors[i][j];

                    // LOWER HALF OF THE MATRIX
                    am_reg[i + HALF_N][j] = evectors[i + HALF_N][j] * exp(-SIGMA_TH[r] / evalues[j]);
                }
                else
                {
                    // UPPER HALF OF THE MATRIX
                    am_reg[i][j] = evectors[i][j] * exp(SIGMA_TH[r] / evalues[j]);

                    // LOWER HALF OF THE MATRIX
                    am_reg[i + HALF_N][j] = evectors[i + HALF_N][j];
                }
            }
        }

        // 1. Decomposição LU (Modifica alpha_matrix para conter L e U)
        LAPACKE_dgetrf(LAPACK_ROW_MAJOR, N, N, (double *)am_reg, N, ipiv);

        // 2. Inversão (Modifica alpha_matrix para conter a Inversa)
        LAPACKE_dgetri(LAPACK_ROW_MAJOR, N, (double *)am_reg, N, ipiv);
    }
}
