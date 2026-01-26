/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

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
    double FFW[NUM_REGS][N],
    double BFW[NUM_REGS][N],
    double SS[TOTAL_NODES],
    double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, num_nodes;
    int node = 1;

    for (i = 0; i < NUM_REGS; i++)
    {
        num_nodes = NUM_NODES[i];
        double q = Q[i];

        for (j = 0; j < num_nodes; j++, node++)
        {
            double ss = SS[node - 1];
            for (m = 0; m < HALF_N; m++)
            {
                psi[node][m] = (ss + q - FFW[i][m] * psi[node - 1][m]) * BFW[i][m];
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
    double FFW[NUM_REGS][N],
    double BFW[NUM_REGS][N],
    double SS[TOTAL_NODES],
    double psi[TOTAL_NODES + 1][N])
{
    int i, j, m, num_nodes;
    int node = TOTAL_NODES - 1;

    for (i = NUM_REGS - 1; i >= 0; i--)
    {
        num_nodes = NUM_NODES[i];
        double q = Q[i];

        for (j = 0; j < num_nodes; j++, node--)
        {
            double ss = SS[node];
            for (m = HALF_N; m < N; m++)
            {
                psi[node][m] = (ss + q - FFW[i][m] * psi[node + 1][m]) * BFW[i][m];
            }
        }
    }
}
