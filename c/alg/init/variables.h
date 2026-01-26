/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#ifndef VARIABLES_H
#define VARIABLES_H

void init_psi(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    double CCE,
    double CCD,
    double psi[][N]);

void init_h(
    int NUM_REGS,
    int NUM_NODES[],
    double ESP_REGS[],
    double h[]);

void
init_foward_flux_weight(
    int N,
    int HALF_N,
    int NUM_REGS,
    double MI[],
    double H[],
    double SIGMA_T[],
    double ffw[][N]);

void init_backward_flux_weight(
    int N,
    int HALF_N,
    int NUM_REGS,
    double MI[],
    double H[],
    double SIGMA_T[],
    double bfw[][N]);

void init_half_sigma_s0(
    int NUM_REGS,
    double SIGMA_S0[],
    double half_sigma_s0[]);

void init_C0(
    int NUM_REGS,
    double SIGMA_T[],
    double SIGMA_S0[],
    double c0[]);

int init_total_nodes(
    int NUM_REGS,
    int NUM_NODES[]);

#endif
