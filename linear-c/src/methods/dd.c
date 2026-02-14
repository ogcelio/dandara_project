/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../include/methods/dd.h"

// COMMON ALGORITHMS
#include "../../include/calc/trivial_solution_test.h"
#include "../../include/calc/quadrature.h"
#include "../../include/calc/scalar_flux.h"
#include "../../include/calc/relative_deviation.h"
#include "../../include/calc/absorption_rate.h"
#include "../../include/calc/escape_rate.h"
#include "../../include/core/init.h"
#include "../file/file_ops.h"
#include <stdlib.h>

// DIAMOND DIFFERENCE ALGORITHMS
#include "../../include/methods/dd/medium_flux.h"
#include "../../include/methods/dd/scattering_source.h"
#include "../../include/methods/dd/sweep.h"

int
diamond_difference(const char* DATA_PATH, const char* OUTPUT_PATH)
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

    unsigned TOTAL_NODES = total_nodes(NUM_REGS, NUM_NODES);

    double *MI = malloc(N * sizeof(double));
    double *W = malloc(N * sizeof(double));
    calc_quadrature(N, MI, W);

    double *H = height(NUM_REGS, NUM_NODES, ESP_REGS);

    double *HALF_SIGMA_S0 = half_sigma_s0(NUM_REGS, SIGMA_S0);

    double *FW = foward_weight(N, HALF_N, NUM_REGS, MI, H, SIGMA_T);

    double *BW = backward_weight(N, HALF_N, NUM_REGS, MI, H, SIGMA_T);

    // INITIALIZING VARIABLES
    unsigned iteration = 0;

    double *psi = angular_flux(N, HALF_N, TOTAL_NODES, CCE, CCD);

    double *psim = malloc(TOTAL_NODES * N * sizeof(double));

    double *initial_fi = malloc((TOTAL_NODES + 1) * sizeof(double));

    double *final_fi = malloc((TOTAL_NODES + 1) * sizeof(double));

    double *ss = malloc(TOTAL_NODES * sizeof(double));

    // INITIAL SCALAR FLUXES
    calc_scalar_flux(N, TOTAL_NODES, W, psi, initial_fi);

    // MAIN ROUTINE
    while (1)
    {
        // MEDIUM ANGULAR FLUX
        calc_medium_flux(N, TOTAL_NODES, psi, psim);

        // SCATTERING SOURCE
        calc_scattering_source(
            N,
            TOTAL_NODES,
            NUM_REGS,
            REGS,
            NUM_NODES,
            W,
            HALF_SIGMA_S0,
            psim,
            ss);

        /*
         * SWEEP
         */

        // FOWARD
        calc_foward(
             N,
             HALF_N,
             TOTAL_NODES,
             NUM_REGS,
             NUM_NODES,
             REGS,
             Q,
             FW,
             BW,
             ss,
             psi);

        // BACKWARD
        calc_backward(
             N,
             HALF_N,
             TOTAL_NODES,
             NUM_REGS,
             NUM_NODES,
             REGS,
             Q,
             FW,
             BW,
             ss,
             psi);

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

    // FINAL MEDIUM ANGULAR FLUXES
    calc_medium_flux(N, TOTAL_NODES, psi, psim);

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
    free(FW);
    free(BW);
    free(psi);
    free(psim);
    free(initial_fi);
    free(final_fi);
    free(ss);
    free(AVG_FI);
    free(ABS_RATE);
    free(ESCAPE_RATE);

    return 0;
}
