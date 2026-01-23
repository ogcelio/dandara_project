/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

//HEADER
#include "diamond_difference.h"

// COMMON ALGORITHMS
#include <string.h>

#include "../alg/calc/absorption_rate.h"
#include "../alg/calc/escape_rate.h"
#include "../alg/calc/quadrature.h"
#include "../alg/calc/relative_deviation.h"
#include "../alg/calc/scalar_flux.h"
#include "../alg/calc/trival_solution_test.h"

#include "../alg/init/variables.h"

#include "../alg/json/file_ops.h"

// DD ALGORITHMS
#include "calc/medium_flux.h"
#include "calc/scattering_source.h"
#include "calc/sweep.h"

int
diamond_difference(char* DATA_PATH, char* OUTPUT_PATH)
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
        unsigned TOTAL_NODES = init_total_nodes(NUM_REGS, NUM_NODES);

        double ESCAPE_RATE[2] = {0};

        double ABS_RATE[NUM_REGS];
        memset(ABS_RATE, 0, sizeof(ABS_RATE));

        double PSI[TOTAL_NODES][N];
        memset(PSI, 0, sizeof(PSI));
        init_psi(N, N / 2, TOTAL_NODES, CCE, CCD, PSI);

        double FINAL_FI[TOTAL_NODES + 1];
        memset(FINAL_FI, 0, sizeof(FINAL_FI));

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

        return 1;
    }

    // INITIALIZING CONSTANTS
    double MI[N], W[N];
    calc_quadrature(N, MI, W);

    for (int i = 0; i < N; i++)
    {
        printf("%f\n", MI[i]);
    }
    printf("\n\n\n");
    for (int i = 0; i < N; i++)
    {
        printf("%f\n", W[i]);
    }

    unsigned TOTAL_NODES = init_total_nodes(NUM_REGS, NUM_NODES);

    unsigned HALF_N = N / 2;

    double H[NUM_REGS];
    init_h(NUM_REGS, NUM_NODES, ESP_REGS, H);

    double MI_H[NUM_REGS][N];
    init_mi_h(N, NUM_REGS, MI, H, MI_H);

    double HALF_SIGMA_T[NUM_REGS];
    init_half_sigma_t(NUM_REGS, SIGMA_T, HALF_SIGMA_T);

    double HALF_SIGMA_S0[N];
    init_half_sigma_s0(NUM_REGS, SIGMA_S0, HALF_SIGMA_S0);

    // INITIALIZING VARIABLES
    int iteration = 0;

    double psi[TOTAL_NODES + 1][N];
    memset(psi, 0, sizeof(psi));
    init_psi(N, HALF_N, TOTAL_NODES, CCE, CCD, psi);

    double psim[TOTAL_NODES][N];

    double initial_fi[TOTAL_NODES + 1];
    double final_fi[TOTAL_NODES + 1];

    double ss[TOTAL_NODES];

    // MAIN ROUTINE
    while (1)
    {
        // AVERAGE ANGULAR FLUXES
        calc_psim(N, TOTAL_NODES, psi, psim);

        // SCATTERING SOURCE
        calc_ss(
            N,
            TOTAL_NODES,
            NUM_REGS,
            REGS,
            NUM_NODES,
            W,
            HALF_SIGMA_S0,
            psim,
            ss);

        // INITIAL SCALAR FLUXES
        calc_fi(N, TOTAL_NODES, W, psi, initial_fi);

        // SWEEP

        // FOWARD
        calc_foward(
            N,
            HALF_N,
            TOTAL_NODES,
            NUM_REGS,
            NUM_NODES,
            REGS,
            Q,
            HALF_SIGMA_T,
            MI_H,
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
            HALF_SIGMA_T,
            MI_H,
            ss,
            psi);

        // FINAL SCALAR FLUXES
        calc_fi(N, TOTAL_NODES, W, psi, final_fi);

        iteration += 1;

        // RELATIVE DEVIATION
        if (relative_deviation(TOTAL_NODES, initial_fi, final_fi) < PREC)
            break;
    }

    // FINAL AVERAGE ANGULAR FLUXES
    calc_psim(N, TOTAL_NODES, psi, psim);

    // AVERAGE SCALAR FLUXES
    double AVG_FI[TOTAL_NODES];
    calc_fi(N, TOTAL_NODES - 1, W, psim, AVG_FI);

    // ABSORPTION RATE
    double ABS_RATE[NUM_REGS];
    calc_abs_rate(
        NUM_NODES,
        NUM_REGS,
        REGS,
        AVG_FI,
        H,
        SIGMA_T,
        SIGMA_S0,
        ABS_RATE);

    // ESCAPE RATE
    double ESCAPE_RATE[2];
    calc_escape_rate(N, HALF_N, TOTAL_NODES, MI, W, psi, ESCAPE_RATE);

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

    return 0;
}
