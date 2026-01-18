#include "sweep.h"

void
calc_foward(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    int NUM_REGS,
    int NUM_NODES[],
    int REGS[NUM_REGS],
    double Q[NUM_REGS],
    double HALF_SIGMA_T[NUM_REGS],
    double MI_H[NUM_REGS][N],
    double SS[TOTAL_NODES],
    double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, num_nodes;
    int node = 1;

    for (i = 0; i < NUM_REGS; i++)
    {
        num_nodes = NUM_NODES[i];
        double q_i = Q[i];
        double st_i = HALF_SIGMA_T[i];

        for (j = 0; j < num_nodes; j++, node++)
        {
            double ss_val = SS[node - 1];
            for (m = 0; m < HALF_N; m++)
            {
                double mi_m = MI_H[i][m];
                psi[node][m] = (ss_val + q_i + (mi_m - st_i) * psi[node - 1][m])
                                /
                                (mi_m + st_i);
            }
        }
    }
}

void
calc_backward(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    int NUM_REGS,
    int NUM_NODES[NUM_REGS],
    int REGS[NUM_REGS],
    double Q[NUM_REGS],
    double HALF_SIGMA_T[NUM_REGS],
    double MI_H[NUM_REGS][N],
    double SS[TOTAL_NODES],
    double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, num_nodes;
    int node = TOTAL_NODES - 1;

    for (i = NUM_REGS - 1; i >= 0; i--)
    {
        num_nodes = NUM_NODES[i];
        double q_i = Q[i];
        double st_i = HALF_SIGMA_T[i];

        for (j = 0; j < num_nodes; j++, node--)
        {
            double ss_val = SS[node];
            for (m = HALF_N; m < N; m++)
            {
                double mi_m = MI_H[i][m];
                psi[node][m] = (ss_val + q_i - (mi_m + st_i) * psi[node + 1][m])
                                /
                                (st_i - mi_m);
            }
        }
    }
}
