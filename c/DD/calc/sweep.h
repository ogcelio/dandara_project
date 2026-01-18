#ifndef SWEEP_H
#define SWEEP_H

void calc_foward(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    int NUM_REGS,
    int NUM_NODES[],
    int REGS[],
    double Q[],
    double HALF_SIGMA_T[],
    double MI_H[][N],
    double SS[],
    double psi[][N]);

void calc_backward(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    int NUM_REGS,
    int NUM_NODES[],
    int REGS[],
    double Q[],
    double HALF_SIGMA_T[],
    double MI_H[][N],
    double SS[],
    double psi[][N]);

#endif
