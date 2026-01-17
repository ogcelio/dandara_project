/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// COMMON ALGORITHMS
#include "alg/calc/absorption_rate.h"
#include "alg/calc/escape_rate.h"
#include "alg/calc/quadrature.h"
#include "alg/calc/relative_deviation.h"
#include "alg/calc/scalar_flux.h"
#include "alg/calc/trival_solution_test.h"

#include "alg/init/variables.h"

// DD ALGORITHMS
#include "DD/medium_flux.h"
#include "DD/scattering_source.h"
#include "DD/sweep.h"

int
diamond_difference(
    int N,
    int NUM_REGS,
    int REGS[NUM_REGS],
    int NUM_NODES[NUM_REGS],
    double CCE,
    double CCD,
    double PREC,
    double Q[NUM_REGS],
    double SIGMA_T[NUM_REGS],
    double SIGMA_S0[NUM_REGS],
    double ESP_REGS[NUM_REGS])
{
    // INITIALIZING CONSTANTS
    double MI[N], W[N];
    calc_quadrature(N, MI, W);

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
    init_psi(N, HALF_N, TOTAL_NODES, CCE, CCD, psi);

    double psim[TOTAL_NODES][N];

    double initial_fi[TOTAL_NODES + 1];
    double final_fi[TOTAL_NODES + 1];

    double ss[TOTAL_NODES];

    // TRIVIAL SOLUTION TEST
    if (!trivial_solution_test(NUM_REGS, REGS, CCE, CCD, Q))
    {
        return 1;
    }

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

    return 0;
}
