/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

//HEADER
#include "../../include/core/init.h"

#include "../../include/core/common.h"
#include <stdlib.h>

double
*angular_flux(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const double CCE,
    const double CCD)
{
    const long TOTAL_NUMS = TOTAL_NODES * N;

    double *psi = calloc(TOTAL_NUMS + N, sizeof(double));

    if (psi == NULL) return NULL;

    for (int m = 0; m < HALF_N; m++)
    {
        psi[m] = CCE;
        psi[TOTAL_NUMS + m + HALF_N] = CCD;
    }

    return psi;
}

double
*height(
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const double ESP_REGS[SCR NUM_REGS])
{
    double *h = malloc(NUM_REGS * sizeof(double));

    for (int r = 0; r < NUM_REGS; r++)
    {
        h[r] = ESP_REGS[r] / NUM_NODES[r];
    }

    return h;
}

double
*foward_weight(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double MI[SCR N],
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS])
{
    double *fw = malloc(NUM_REGS * N * sizeof(double));

    double * restrict actual_fw = &fw[0];

    for (int r = 0; r < NUM_REGS; r++)
    {
        double h_st = 0.5 * SIGMA_T[r];
        double inv_h = 1 / H[r];

        for (int m = 0; m < HALF_N; m++)
        {
            actual_fw[m] = h_st - MI[m] * inv_h;

            actual_fw[m + HALF_N] = h_st + MI[m + HALF_N] * inv_h;
        }

        actual_fw += N;
    }

    return fw;
}

double
*backward_weight(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double MI[SCR N],
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS])
{
    double *bw = malloc(NUM_REGS * N * sizeof(double));

    double * restrict actual_bw = &bw[0];

    for (int r = 0; r < NUM_REGS; r++)
    {
        double h_st = 0.5 * SIGMA_T[r];
        double inv_h = 1 / H[r];

        for (int m = 0; m < HALF_N; m++)
        {
            actual_bw[m] = 1 / (h_st + MI[m] * inv_h);

            actual_bw[m + HALF_N] = 1 / (h_st - MI[m + HALF_N] * inv_h);
        }

        actual_bw += N;
    }

    return bw;
}

double
*half_sigma_s0(
    const int NUM_REGS,
    const double SIGMA_S0[SCR NUM_REGS])
{
    double *h_s0 = malloc(NUM_REGS * sizeof(double));
    for (int r = 0; r < NUM_REGS; r++)
    {
        h_s0[r] = SIGMA_S0[r] * 0.5;
    }

    return h_s0;
}

int
total_nodes(
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS])
{
    int sum = 0;
    for (int i = 0; i < NUM_REGS; i++)
    {
        sum += NUM_NODES[i];
    }

    return sum;
}
