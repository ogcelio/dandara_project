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

void init_mi_h(
    int N,
    int NUM_REGS,
    double MI[],
    double H[],
    double mi_h[][N]);

void init_half_sigma_t(
    int NUM_REGS,
    double SIGMA_T[],
    double half_sigma_t[]);

void init_half_sigma_s0(
    int NUM_REGS,
    double SIGMA_S0[],
    double half_sigma_s0[]);

int init_total_nodes(
    int NUM_REGS,
    int NUM_NODES[]);

#endif
