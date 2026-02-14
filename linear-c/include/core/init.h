/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include "common.h"

#ifndef INIT_H
#define INIT_H

double *angular_flux(
    const int N,
    const int HALF_N,
    const int TOTAL_NODES,
    const double CCE,
    const double CCD);

double *height(
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS],
    const double ESP_REGS[SCR NUM_REGS]);

double *foward_weight(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double MI[SCR N],
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS]);

double *backward_weight(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double MI[SCR N],
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS]);

double *half_sigma_s0(
    const int NUM_REGS,
    const double SIGMA_S0[SCR NUM_REGS]);

int total_nodes(
    const int NUM_REGS,
    const int NUM_NODES[SCR NUM_REGS]);

double *sigma_th(
    const int NUM_REGS,
    const double H[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS]);

double *inv_sigma_th(
    const int NUM_REGS,
    const double SIGMA_TH[NUM_REGS]);

double *mi_h(
    const int N,
    const int HALF_N,
    const int NUM_REGS,
    const double MI[SCR N],
    const double H[SCR NUM_REGS]);

double *lambda_to_nu(
    const int N,
    const int NUM_REGS,
    const double LAMBDA[SCR (NUM_REGS * N)]);

double *c0(
    const int NUM_REGS,
    const double SIGMA_S0[SCR NUM_REGS],
    const double SIGMA_T[SCR NUM_REGS]);

#endif
