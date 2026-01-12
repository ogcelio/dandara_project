#ifndef ABSORPTION_RATE_H
#define ABSORPTION_RATE_H

void calc_abs_rate(
    int NUM_NODES[],
    int NUM_REGS,
    int REGS[],
    double AVG_FI[],
    double H[],
    double SIGMA_T[],
    double SIGMA_S0[],
    double abs_rate[]);

#endif
