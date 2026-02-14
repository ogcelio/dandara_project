/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/alpha_matrix.h"

#include "../../../include/core/common.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>

double
*alpha_matrix(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double SIGMA_TH[SCR NUM_REGS],
    const double LAMBDA[SCR (NUM_REGS * N)],
    const double EIGENVECTORS[SCR (NUM_REGS * N * N)])
{
    int lower_jump = HALF_N * N;
    int sqr_n = N * N;

    double *alpha_matrix = malloc(NUM_REGS * sqr_n * sizeof(double));
    if (!alpha_matrix)
    {
        printf("Error in the memory allocation of the ALPHA MATRIX.");
        return NULL;
    }

    lapack_int *ipiv = malloc(N * sizeof(lapack_int));
    if (!ipiv)
    {
        printf("Error in the memory allocation of the IPIV.");
        free(alpha_matrix);
        return NULL;
    }

    const double * restrict evec = &EIGENVECTORS[0];
    const double * restrict lambda = &LAMBDA[0];
    double * restrict matrix = &alpha_matrix[0];

    double * restrict reg_matrix = &alpha_matrix[0];

    for (int r = 0; r < NUM_REGS; r++)
    {
        double sigma_th = SIGMA_TH[r];

        for (int m = 0; m < HALF_N; m++)
        {
            for (int l = 0; l < N; l++)
            {
                if (lambda[l] > 0)
                {
                    matrix[l] = evec[l];

                    matrix[lower_jump + l] = evec[lower_jump + l] * exp(-sigma_th * lambda[l]);
                }
                else
                {
                    matrix[l] = evec[l] * exp(sigma_th * lambda[l]);

                    matrix[lower_jump + l] = evec[lower_jump + l];
                }
            }

            matrix += N;
            evec += N;
        }

        lambda += N;
        evec += lower_jump;

        // LU DECOMPOSITION
        LAPACKE_dgetrf(LAPACK_ROW_MAJOR, N, N, reg_matrix, N, ipiv);

        // INVERSION
        LAPACKE_dgetri(LAPACK_ROW_MAJOR, N, reg_matrix, N, ipiv);

        matrix += lower_jump;
        reg_matrix += sqr_n;
    }

    free(ipiv);

    return alpha_matrix;
}
