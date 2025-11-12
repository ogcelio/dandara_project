import numpy as np
from time import perf_counter

from python.quadrature.quadrature import quadrature

from python.DD.calc.calc_psiM import calc_psiM
from python.DD.calc.calc_foward import foward
from python.DD.calc.calc_backward import backward
from python.DD.calc.calc_ss import calc_ss

from python.common.calc_fi import calc_fi
from python.common.init_variables import init_psiX, init_hj
from python.common.calc_dr import calc_dr
from python.common.calc_sigmaA import calc_sigmaA
from python.common.calc_abs_rate import calc_abs_rate
from python.common.calc_escape_rate import calc_escape_rate
from python.common.trivial_sol_test import trivial_sol


def diamond_difference(
    SIGMA_T,
    SIGMA_S0,
    SIGMA_S1,
    SIGMA_S2,
    Q,
    NI_SIGMA_F,
    N,
    CCE,
    CCD,
    PREC,
    NN,
    REGS,
    NUM_REGS,
    ESP_REGS,
):
    # Coletando o tempo inicial:
    initial_time = perf_counter()

    # ETAPA INICIALIZACAO DE VARIAVEIS
    MI, W = quadrature(N)
    NNT = sum(NN)

    psi = init_psiX(N, NNT, CCE, CCD)
    H = init_hj(NN, NUM_REGS, ESP_REGS)

    iteration = 0

    if trivial_sol(Q, CCE, CCD, NUM_REGS):
        # Arredondando fi_final
        initial_fi = np.zeros(NNT + 1)

        # Arredondando psi
        abs_rate = np.zeros(NUM_REGS)
        escape_rate = np.zeros(2)

        # Coletando Tempo final
        final_time = perf_counter()

        # Calculando tempo de execução
        execution_time = abs(final_time - initial_time)

        return (
            initial_fi,
            psi,
            iteration,
            abs_rate,
            escape_rate,
            execution_time,
        )  # Caso fontes e condições de contorno sejam nulas, o código retorna os fluxos completamente preenchidos de zero

    while True:
        # ETAPA CALCULO DOS FLUXOS ANGULARES MEDIOS
        psim = calc_psiM(N, NNT, psi)

        # ETAPA CALCULO DO Ss
        ss = calc_ss(N, NN, NNT, REGS, psim, W, SIGMA_S0)

        ###ETAPA CÁLCULO DO FI INICIAL
        initial_fi = calc_fi(N, NNT, W, psi)

        ###ETAPA IDA
        psi = foward(N, NN, REGS, psi, H, ss, Q, MI, SIGMA_T)

        ###ETAPA VOLTA
        psi = backward(N, NN, NNT, REGS, psi, H, ss, Q, MI, SIGMA_T)

        ###ETAPA CÁLCULO DO FI FINAL
        final_fi = calc_fi(N, NNT, W, psi)

        iteration += 1

        ###ETAPA CÁLCULO DO DR
        dr = calc_dr(initial_fi, final_fi)
        if dr < PREC:
            break

    ###ETAPA ATUALIZAÇÃO DOS PSIS MÉDIOS
    psim = calc_psiM(N, NNT, psi)

    ###ETAPA TAXA DE ABSORÇÃO
    # Fi Medio
    average_fi = 2 * calc_fi(N, NNT - 1, W, psim)

    # Gerando Sigma A
    SIGMA_A = calc_sigmaA(SIGMA_T, SIGMA_S0)

    # Taxa de Absorção
    abs_rate = calc_abs_rate(NN, REGS, average_fi, H, SIGMA_A)

    ###ETAPA TAXA DE FUGA
    escape_rate = calc_escape_rate(N, psi, MI, W)

    # Coletando Tempo final
    final_time = perf_counter()

    # Calculando tempo de execução
    execution_time = abs(final_time - initial_time)

    return final_fi, psi, iteration, abs_rate, escape_rate, execution_time
