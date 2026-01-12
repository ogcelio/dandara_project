#ifndef SCALAR_FLUX_H
#define SCALAR_FLUX_H

void calc_fi(
    int N,
    int TOTAL_NODES,
    double W[],
    double psi[][N],
    double fi[]);

#endif
