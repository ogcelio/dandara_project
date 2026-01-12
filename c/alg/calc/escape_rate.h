#ifndef ESCAPE_RATE_H
#define ESCAPE_RATE_H

void calc_escape_rate(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    double MI[],
    double W[],
    double PSI[][N],
    double escape_rate[]);

#endif
