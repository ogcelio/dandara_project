/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "variables.h"

void
init_psi(
    int N,
    int HALF_N,
    int TOTAL_NODES,
    double CCE,
    double CCD,
    double psi[TOTAL_NODES + 1][N])
{
    for (int m = 0; m < HALF_N; m++)
    {
        psi[0][m] = CCE;
        psi[TOTAL_NODES][HALF_N + m] = CCD;
    }
}

void
init_h(
    int NUM_REGS,
    int NUM_NODES[NUM_REGS],
    double ESP_REGS[NUM_REGS],
    double h[NUM_REGS])
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        h[i] = ESP_REGS[i] / NUM_NODES[i];
    }
}

void
init_foward_flux_weight(
    int N,
    int HALF_N,
    int NUM_REGS,
    double MI[N],
    double H[NUM_REGS],
    double SIGMA_T[NUM_REGS],
    double ffw[NUM_REGS][N])
{
    int r, m;
    double h_st, inv_h;

    for (r = 0; r < NUM_REGS; r++)
    {
        h_st = 0.5 * SIGMA_T[r];
        inv_h = 1 / H[r];

        for (m = 0; m < HALF_N; m++)
        {
            ffw[r][m] = h_st - MI[m] * inv_h;

            ffw[r][m + HALF_N] = h_st + MI[m + HALF_N] * inv_h;
        }
    }
}

void
init_backward_flux_weight(
    int N,
    int HALF_N,
    int NUM_REGS,
    double MI[N],
    double H[NUM_REGS],
    double SIGMA_T[NUM_REGS],
    double bfw[NUM_REGS][N])
{
    int r, m;
    double h_st, inv_h;

    for (r = 0; r < NUM_REGS; r++)
    {
        h_st = 0.5 * SIGMA_T[r];
        inv_h = 1 / H[r];

        for (m = 0; m < HALF_N; m++)
        {
            bfw[r][m] = 1 / (h_st + MI[m] * inv_h);

            bfw[r][m + HALF_N] = 1 / (h_st - MI[m + HALF_N] * inv_h);
        }
    }
}

void
init_half_sigma_s0(
    int NUM_REGS,
    double SIGMA_S0[NUM_REGS],
    double half_sigma_s0[NUM_REGS])
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        half_sigma_s0[i] = SIGMA_S0[i] * 0.5;
    }
}

void
init_C0(
    int NUM_REGS,
    double SIGMA_T[NUM_REGS],
    double SIGMA_S0[NUM_REGS],
    double c0[NUM_REGS])
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        c0[i] = SIGMA_S0[i] / SIGMA_T[i];
    }
}

int
init_total_nodes(
    int NUM_REGS,
    int NUM_NODES[NUM_REGS])
{
    int sum = 0;
    for (int i = 0; i < NUM_REGS; i++)
    {
        sum += NUM_NODES[i];
    }

    return sum;
}
