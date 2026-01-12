#ifndef SCATTERING_SOURCE_H
#define SCATTERING_SOURCE_H

void calc_ss(
    int N,
    int NUM_REGS,
    int REGS[],
    int NUM_NODES[],
    double W[],
    double HALF_SIGMA_S0[],
    double psim[],
    double ss[]);

#endif
