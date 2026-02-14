/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/methods/msd.h"

// COMMON ALGORITHMS
#include "../../include/calc/trivial_solution_test.h"
#include "../../include/calc/quadrature.h"
#include "../../include/calc/scalar_flux.h"
#include "../../include/calc/relative_deviation.h"
#include "../../include/calc/absorption_rate.h"
#include "../../include/calc/escape_rate.h"
#include "../../include/core/init.h"
#include "../file/file_ops.h"
#include <stdio.h>
#include <stdlib.h>

// MODIFIED SPECTRAL DETERMINISTIC METHODS
#include "../../include/methods/msd/alpha.h"
#include "../../include/methods/msd/alpha_matrix.h"
#include "../../include/methods/msd/angular_flux.h"
#include "../../include/methods/msd/average_angular.h"
#include "../../include/methods/msd/eigen.h"
#include "../../include/methods/msd/particular_solution.h"
#include "../../include/methods/msd/scattering_source.h"
#include "../../include/methods/msd/solution_difference.h"

int
modified_spectral_deterministic(const char* DATA_PATH, const char* OUTPUT_PATH)
{
    // IMPORTING SIMULATION DATA
    IMPORT_DATA(
        DATA_PATH,
        N,
        NUM_REGS,
        CCE,
        CCD,
        PREC,
        REGS,
        NUM_NODES,
        Q,
        SIGMA_T,
        SIGMA_S0,
        ESP_REGS);

    // TRIVIAL SOLUTION TEST
    if (trivial_solution_test(NUM_REGS, REGS, CCE, CCD, Q))
    {
        // INITIALING CONST WITH 0s
        unsigned TOTAL_NODES = total_nodes(NUM_REGS, NUM_NODES);

        double ESCAPE_RATE[2] = {0};

        double *ABS_RATE = calloc(NUM_REGS, sizeof(double));

        double *PSI = angular_flux(N, N / 2, TOTAL_NODES, CCE, CCD);

        double *FINAL_FI = calloc(TOTAL_NODES, sizeof(double));

        // SAVING OUTPUT
        SAVE_OUTPUT(
            OUTPUT_PATH,
            N,
            0,
            TOTAL_NODES,
            NUM_REGS,
            FINAL_FI,
            ABS_RATE,
            ESCAPE_RATE,
            PSI);

        free(ABS_RATE);
        free(PSI);
        free(FINAL_FI);

        return 1;
    }

    // INITIALIZING CONSTANTS
    unsigned HALF_N = N / 2;

    unsigned SQR_N = N * N;

    unsigned TOTAL_NODES = total_nodes(NUM_REGS, NUM_NODES);

    double *MI = malloc(N * sizeof(double));
    double *W = malloc(N * sizeof(double));
    calc_quadrature(N, MI, W);

    double *H = height(NUM_REGS, NUM_NODES, ESP_REGS);

    double *HALF_SIGMA_S0 = half_sigma_s0(NUM_REGS, SIGMA_S0);

    double *SIGMA_TH = sigma_th(NUM_REGS, H, SIGMA_T);

    double *INV_SIGMA_TH = inv_sigma_th(NUM_REGS, SIGMA_TH);

    double *C0 = c0(NUM_REGS, SIGMA_S0, SIGMA_T);

    double *MI_H = mi_h(N, HALF_N, NUM_REGS, MI, H);

    // INITIALIZING VARIABLES
    unsigned iteration = 0;

    double *psi = angular_flux(N, HALF_N, TOTAL_NODES, CCE, CCD);

    double *psim = malloc(TOTAL_NODES * N * sizeof(double));

    double *initial_fi = malloc((TOTAL_NODES + 1) * sizeof(double));

    double *final_fi = malloc((TOTAL_NODES + 1) * sizeof(double));

    double *alpha = malloc(N * sizeof(double));

    double *sol_dif = malloc(N * sizeof(double));

    // PRE-ROUTINE EVALUATIONS

    // EIGENVALUES AND EIGENVECTORS
    double *LAMBDA = malloc(NUM_REGS * N * sizeof(double));
    double *EIGENVEC = malloc(NUM_REGS * N * N * sizeof(double));
    calc_eig(N, HALF_N, NUM_REGS, W, MI, C0, LAMBDA, EIGENVEC);

    double *NU = lambda_to_nu(N, NUM_REGS, LAMBDA);

    // PARTICULAR SOLUTION
    double *PART_SOL = particular_solution(NUM_REGS, Q, SIGMA_T, SIGMA_S0);

    // ALPHA MATRIX
    double *ALPHA_MATRIX = alpha_matrix(N, HALF_N, NUM_REGS, SIGMA_TH, LAMBDA, EIGENVEC);

    // INITIAL SCALAR FLUXES
    calc_scalar_flux(N, TOTAL_NODES, W, psi, initial_fi);

    // MAIN ROUTINE
    while (1)
    {
        int node = 0;

        double *matrix = &ALPHA_MATRIX[0];

        double *mih = &MI_H[0];

        double *lambda = &LAMBDA[0];
        double *nu = &NU[0];
        double *evec = &EIGENVEC[0];

        double *curr_psim = &psim[0];

        for (int r = 0; r < NUM_REGS; r++)
        {
            int num_nodes = NUM_NODES[r];
            double part_sol = PART_SOL[r];
            double h_s0 = HALF_SIGMA_S0[r];
            double q = Q[r];
            double st = SIGMA_T[r];
            double sth = SIGMA_TH[r];
            double inv_sth = INV_SIGMA_TH[r];

            for (int j = 0; j < num_nodes; j++, node++, curr_psim += N)
            {
                // SOLUTION DIFFERENCE
                calc_solution_difference(N, HALF_N, node, TOTAL_NODES, part_sol, psi, sol_dif);

                // ALPHA
                calc_alpha(N, matrix, sol_dif, alpha);

                // AVERAGE ANGULAR FLUX
                calc_average_angular(N, sth, inv_sth, part_sol, alpha, lambda, nu, evec, curr_psim);

                // SCATTERING SOURCE
                double ss = scattering_source(N, h_s0, W, curr_psim);

                // ANGULAR FLUX
                calc_angular_flux(N, HALF_N, TOTAL_NODES, node, ss, q, st, mih, curr_psim, psi);
            }
            matrix += SQR_N;
            evec += SQR_N;
            lambda += N;
            nu += N;
            mih += N;
        }

        // FINAL SCALAR FLUXES
        calc_scalar_flux(N, TOTAL_NODES, W, psi, final_fi);

        iteration += 1;

        // RELATIVE DEVIATION
        if (relative_deviation(TOTAL_NODES, initial_fi, final_fi) < PREC)
            break;

        // SWAPPING SCALAR FLUXES
        double *temp = initial_fi;
        initial_fi = final_fi;
        final_fi = temp;
    }

    // AVERAGE SCALAR FLUXES
    double *AVG_FI = malloc(TOTAL_NODES * sizeof(double));
    calc_scalar_flux(N, TOTAL_NODES - 1, W, psim, AVG_FI);

    // ABSORPTION RATE
    double *ABS_RATE = abs_rate(NUM_REGS, TOTAL_NODES, NUM_NODES,
                                REGS, AVG_FI, H, SIGMA_T, SIGMA_S0);

    double *ESCAPE_RATE = escape_rate(N, HALF_N, TOTAL_NODES, MI, W, psi);

    // SAVING OUTPUT
    SAVE_OUTPUT(
        OUTPUT_PATH,
        N,
        iteration,
        TOTAL_NODES,
        NUM_REGS,
        final_fi,
        ABS_RATE,
        ESCAPE_RATE,
        psi);

    // FREEING MEMORY
    free(MI);
    free(W);
    free(H);
    free(HALF_SIGMA_S0);
    free(psi);
    free(psim);
    free(initial_fi);
    free(final_fi);
    free(AVG_FI);
    free(ABS_RATE);
    free(ESCAPE_RATE);

    return 0;
}
