/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "msd_main.h"

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
#include "calc/calc_eig.h"

int
modified_spectral_deterministic(char *DATA_PATH, char *OUTPUT_PATH)
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

    unsigned TOTAL_NODES = init_total_nodes(NUM_REGS, NUM_NODES);

    unsigned HALF_N = N / 2;

    double H[NUM_REGS];
    init_h(NUM_REGS, NUM_NODES, ESP_REGS, H);

    double C0[NUM_REGS];
    init_C0(NUM_REGS, SIGMA_T, SIGMA_S0, C0);

    double HALF_SIGMA_S0[N];
    init_half_sigma_s0(NUM_REGS, SIGMA_S0, HALF_SIGMA_S0);

    double FFW[NUM_REGS][N];
    init_foward_flux_weight(N, HALF_N, NUM_REGS, MI, H, SIGMA_T, FFW);

    double BFW[NUM_REGS][N];
    init_backward_flux_weight(N, HALF_N, NUM_REGS, MI, H, SIGMA_T, BFW);

    double EIGENVALUES[NUM_REGS][N];
    double EIGENVECTORS[NUM_REGS][N][N];

    calc_eig(N, NUM_REGS, W, MI, C0, EIGENVALUES, EIGENVECTORS);

    // INITIALIZING VARIABLES
    int iteration = 0;

    double psi[TOTAL_NODES + 1][N];
    memset(psi, 0, sizeof(psi));
    init_psi(N, HALF_N, TOTAL_NODES, CCE, CCD, psi);

    double psim[TOTAL_NODES][N];

    double initial_fi[TOTAL_NODES + 1];
    double final_fi[TOTAL_NODES + 1];

    for (int i = 0; i < N; i++)
    {
        printf("%f \n", EIGENVALUES[0][i]);
    }

    return 0;
}
