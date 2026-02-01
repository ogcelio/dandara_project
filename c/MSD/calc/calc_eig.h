#ifndef CALC_EIG_H
#define CALC_EIG_H

void calc_eig(
    int N,
    int NUM_REGS,
    double W[],
    double MI[],
    double C0[],
    double eigenvalues[][N],
    double eigenvectors[][N][N]);

#endif
