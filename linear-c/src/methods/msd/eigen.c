/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/eigen.h"

#include "../../../include/core/common.h"
#include <stdlib.h>
#include <stdio.h>
#include "lapacke.h"

void
calc_eig(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double W[SCR N],
    const double MI[SCR N],
    const double C0[NUM_REGS],
    double lambda[SCR (NUM_REGS * N)],
    double eigenvec[SCR (NUM_REGS * N * N)])
{
    int SQR_N = N * N;

    // IMAGINARY EIGENVALUES
    double *im = malloc(N * sizeof(double));
    if (!im)
    {
        printf("Error in the memory allocation of the IMAGINARY EIGENVALUES.");
        return;
    }

    double *a_matrix = malloc(SQR_N * sizeof(double));
    if (!a_matrix)
    {
        printf("Error in the memory allocation of the MATRIX OF EIGENVALUES/VECTORS.");
        free(im);
        return;
    }

    double *INV_MI = malloc(N * sizeof(double));
    if (!INV_MI)
    {
        printf("Error in the memory allocation of the INVERSE OF MI.");
        free(a_matrix);
        free(im);
        return;
    }

    double * restrict reg_lambda = &lambda[0];

    double * restrict reg_evec = &eigenvec[0];

    for (int m = 0; m < HALF_N; m++)
    {
        INV_MI[m] = 1 / MI[m];

        INV_MI[m + HALF_N] = -INV_MI[m];
    }

    for (int r = 0; r < NUM_REGS; r++)
    {
        double * restrict matrix = &a_matrix[0];
        double c0 = C0[r];
        for (int m = 0; m < N; m++)
        {
            double mi = INV_MI[m];
            double c0_mi = -(0.5 * c0 * mi);

            for (int n = 0; n < N; n++)
            {
                matrix[n] = c0_mi * W[n];
            }

            matrix[m] += mi;

            matrix += N;
        }

        LAPACKE_dgeev(
            LAPACK_ROW_MAJOR,
            'N',            // jobvl (Left)
            'V',            // jobvr (Right)
            N,              // N
            a_matrix,       // A
            N,              // LDA
            reg_lambda,     // WR (Real Eigenvalues)
            im,             // WI (Imaginary Eigenvalues)
            NULL,           // VL (Ignorado, pois jobvl='N')
            1,              // LDVL (Placeholder)
            reg_evec,       // VR (Onde salvamos os autovetores corretos)
            N               // LDVR
        );

        reg_lambda += N;
        reg_evec += SQR_N;
    }

    free(im);
    free(a_matrix);
    free(INV_MI);
}
