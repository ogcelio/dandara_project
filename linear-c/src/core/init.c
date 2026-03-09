/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

//HEADER
#include "../../include/core/init.h"

#include "../../include/core/common.h"
#include <stdio.h>
#include <stdlib.h>

double
*angular_flux(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const double CCE,
    const double CCD)
{
    double* psi = calloc((TOTAL_NODES + 1) * N, sizeof(double));
    if (!psi)
    {
        printf("Error in the memory allocation of the ANGULAR FLUX.");
        return NULL;
    }

    for (int m = 0; m < HALF_N; m++)
    {
        psi[m * TOTAL_NODES] = CCE;
        psi[(m + HALF_N) * TOTAL_NODES] = CCD;
    }

    return psi;
}

double
*height(
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const double ESP_REGS[SCR NUM_REGS])
{
    double* h = malloc(TOTAL_NODES * sizeof(double));
    if (!h)
    {
        printf("Error in the memory allocation of the HEIGHT.");
        return NULL;
    }

    int node = 0;
    for (int r = 0; r < NUM_REGS; r++)
    {
        int num_nodes = NUM_NODES[r];
        double h_reg = ESP_REGS[r] / NUM_NODES[r];

        for (int j = 0; j < num_nodes; j++, node++)
        {
            h[node] = h_reg;
        }
    }

    return h;
}

double*
aligned_st(
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS])
{
    double* new_st = malloc(TOTAL_NODES * sizeof(double));
    if (!new_st)
    {
        printf("Error in the memory allocation of the ALIGNED SIGMA T.");
        return NULL;
    }

    int node = 0;
    for (int r = 0; r < NUM_REGS; r++)
    {
        int num_nodes = NUM_NODES[r];
        double st = SIGMA_T[r];

        for (int j = 0; j < num_nodes; j++, node++)
        {
            new_st[node] = st;
        }
    }

    return new_st;
}

double*
aligned_s0(
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const double SIGMA_S0[SCR NUM_REGS])
{
    double* new_s0 = malloc(TOTAL_NODES * sizeof(double));
    if (!new_s0)
    {
        printf("Error in the memory allocation of the ALIGNED SIGMA T.");
        return NULL;
    }

    int node = 0;
    for (int r = 0; r < NUM_REGS; r++)
    {
        int num_nodes = NUM_NODES[r];
        double s0 = SIGMA_S0[r];

        for (int j = 0; j < num_nodes; j++, node++)
        {
            new_s0[node] = s0;
        }
    }

    return new_s0;
}

double
*half_sigma_s0(
    const int TOTAL_NODES,
    const double SIGMA_S0[SCR TOTAL_NODES])
{
    double *h_s0 = malloc(TOTAL_NODES * sizeof(double));
    if (!h_s0)
    {
        printf("Error in the memory allocation of the HALF SIGMA S0.");
        return NULL;
    }

    for (int j = 0; j < TOTAL_NODES; j++)
    {
        h_s0[j] = SIGMA_S0[j] * 0.5;
    }

    return h_s0;
}

double*
aligned_q(
    const int TOTAL_NODES,
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const double Q[SCR NUM_REGS])
{
    double* new_q = malloc(TOTAL_NODES * sizeof(double));
    if (!new_q)
    {
        printf("Error in the memory allocation of the ALIGNED SIGMA T.");
        return NULL;
    }

    int node = 0;
    for (int r = 0; r < NUM_REGS; r++)
    {
        int num_nodes = NUM_NODES[r];
        double q = Q[r];

        for (int j = 0; j < num_nodes; j++, node++)
        {
            new_q[node] = q;
        }
    }

    return new_q;
}

double
*foward_weight(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const double MI[SCR N],
    const double H[SCR TOTAL_NODES],
    const double SIGMA_T[SCR TOTAL_NODES])
{
    double *fw = malloc(TOTAL_NODES * N * sizeof(double));
    if (!fw)
    {
        printf("Error in the memory allocation of the FOWARD WEIGHT.");
        return NULL;
    }

    const int jump = (HALF_N + 1) * TOTAL_NODES;

    const double * restrict actual_st = &SIGMA_T[0];
    const double * restrict actual_h = &H[0];
    double * restrict actual_fw = &fw[0];

    for (int m = 0; m < HALF_N; m++)
    {
        double mi = MI[m];

        for (int j = 0; j < TOTAL_NODES; j++)
        {
            const double r = (0.5 * actual_st[j]) - (mi / actual_h[j]);

            actual_fw[j] = r;
            actual_fw[jump - j] = r;
        }

        actual_fw += TOTAL_NODES;
        actual_h += TOTAL_NODES;
        actual_st += TOTAL_NODES;
    }

    return fw;
}

double
*backward_weight(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const double MI[SCR N],
    const double H[SCR TOTAL_NODES],
    const double SIGMA_T[SCR TOTAL_NODES])
{
    double *bw = malloc(TOTAL_NODES * N * sizeof(double));
    if (!bw)
    {
        printf("Error in the memory allocation of the FOWARD WEIGHT.");
        return NULL;
    }

    const int jump = (HALF_N + 1) * TOTAL_NODES;

    const double * restrict actual_st = &SIGMA_T[0];
    const double * restrict actual_h = &H[0];
    double * restrict actual_bw = &bw[0];

    for (int m = 0; m < HALF_N; m++)
    {
        double mi = MI[m];

        for (int j = 0; j < TOTAL_NODES; j++)
        {
            const double r = 1 / ((0.5 * actual_st[j]) + (mi / actual_h[j]));

            actual_bw[j] = r;
            actual_bw[jump - j] = r;
        }

        actual_bw += TOTAL_NODES;
        actual_h += TOTAL_NODES;
        actual_st += TOTAL_NODES;
    }

    return bw;
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

double
*sigma_th(
    const int NUM_REGS,
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS])
{
    double *sigma_th = malloc(NUM_REGS * sizeof(double));
    if (!sigma_th)
    {
        printf("Error in the memory allocation of the SIGMA TH.");
        return NULL;
    }

    for (int r = 0; r < NUM_REGS; r++)
    {
        sigma_th[r] = SIGMA_T[r] * H[r];
    }

    return sigma_th;
}

double
*inv_sigma_th(
    const int NUM_REGS,
    const double SIGMA_TH[NUM_REGS])
{
    double *inv_sigma_th = malloc(NUM_REGS * sizeof(double));
    if (!inv_sigma_th)
    {
        printf("Error in the memory allocation of the INVERSE OF SIGMA TH.");
        return NULL;
    }

    for (int r = 0; r < NUM_REGS; r++)
    {
        inv_sigma_th[r] = 1 / SIGMA_TH[r];
    }

    return inv_sigma_th;
}

double
*mi_h(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double MI[SCR N],
    const double H[SCR NUM_REGS])
{
    double *mi_h = malloc(NUM_REGS * N * sizeof(double));
    if (!mi_h)
    {
        printf("Error in the memory allocation of the MI H.");
        return NULL;
    }

    double *inv_mi = malloc(HALF_N * sizeof(double));
    if (!inv_mi)
    {
        printf("Error in the memory allocation of the INVERSE OF MI.");
        free(mi_h);
        return NULL;
    }

    for (int m = 0; m < HALF_N; m++)
    {
        inv_mi[m] = 1 / MI[m];
    }

    double * restrict curr_mih = &mi_h[0];

    for (int r = 0; r < NUM_REGS; r++)
    {
        double h = H[r];
        for (int m = 0; m < HALF_N; m++)
        {
            curr_mih[m] = h * inv_mi[m];

            curr_mih[m + HALF_N] = curr_mih[m];
        }

        curr_mih += N;
    }

    free(inv_mi);

    return mi_h;
}

double
*lambda_to_nu(
    const int N,
    const int NUM_REGS,
    const double LAMBDA[SCR (NUM_REGS * N)])
{
    const int TOTAL = NUM_REGS * N;

    double *nu = malloc(TOTAL * sizeof(double));
    if (!nu)
    {
        printf("Error in the memory allocation of NU");
        return NULL;
    }

    for (int i = 0; i < TOTAL; i++)
    {
        nu[i] = 1 / LAMBDA[i];
    }

    return nu;
}

double
*c0(
    const int NUM_REGS,
    const double SIGMA_S0[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS])
{
    double *c0 = malloc(NUM_REGS * sizeof(double));

    for (int r = 0; r < NUM_REGS; r++)
    {
        c0[r] = SIGMA_S0[r] / SIGMA_T[r];
    }

    return c0;
}
