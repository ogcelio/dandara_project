from time import perf_counter
from numpy import zeros

from python.quadrature.quadrature import quadrature

from python.common.init_variables import init_psiX, init_hj, init_C0j
from python.common.trivial_sol_test import trivial_sol
from python.common.calc_fi import calc_fi
from python.common.calc_dr import calc_dr
from python.common.calc_sigmaA import calc_sigmaA
from python.common.calc_abs_rate import calc_abs_rate
from python.common.calc_escape_rate import calc_escape_rate

from python.MSD.calc.calc_eigen import calc_eigen
from python.MSD.calc.calc_part_sol import calc_part_sol
from python.MSD.calc.calc_alfa import calc_alfa
from python.MSD.calc.calc_psiM import calc_psiM
from python.MSD.calc.calc_ss import calc_ss
from python.MSD.calc.calc_psi import calc_psi


def msd(
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
    NUM_NODES,
    REGS,
    NUM_REGS,
    ESP_REGS,
):
    # COLETANDO TEMPO INICIAL
    INITIAL_TIME = perf_counter()

    # INICIALIZANDO VARIÁVEIS
    MI, W = quadratura(N)
    TOTAL_NODES = sum(NUM_NODES)
    psi = init_psiX(N, TOTAL_NODES, CCE, CCD)
    H = init_hj(NUM_NODES, NUM_REGS, ESP_REGS)
    C0 = init_C0j(SIGMA_T, SIGMA_S0)
    psiM = zeros((TOTAL_NODES, N))
    iteration = 0

    if trivial_sol(Q, CCE, CCD, NUM_REGS):
        initial_fi = zeros(TOTAL_NODES + 1)

        abs_rate = zeros(NUM_REGS)
        escape_rate = zeros(2)

        # Coletando Tempo final
        FINAL_TIME = perf_counter()

        # Calculando tempo de execução
        execution_time = abs(FINAL_TIME - INITIAL_TIME)
        return (
            initial_fi,
            psi,
            iteration,
            abs_rate,
            escape_rate,
            execution_time,
        )  # Caso fontes e condições de contorno sejam nulas, o código retorna os fluxos completamente preenchidos de zeros

    # CALCULANDO AUTOVALORES E AUTOVETORES
    EIGEN_DICT = calc_eigen(N, REGS, MI, W, C0)

    # CALCULANDO SOLUÇÕES PARTICULARES
    PART_SOL_DICT = calc_part_sol(N, Q, REGS, SIGMA_T, SIGMA_S0, W)

    while True:
        iteration += 1

        # CÁLCULO DO FLUXO ESCALAR INICIAL
        initial_fi = calc_fi(N, TOTAL_NODES, W, psi)

        # INICIANDO PROCESSO ITERATIVO
        node = 0
        for index_reg, num_nodes in enumerate(NUM_NODES):
            reg = REGS[index_reg] - 1

            # COLETANDO AUTOVALORES E AUTOVETORES
            eigenvalues = EIGEN_DICT[f"{reg}"]["eigenvalues"]
            eigenvectors = EIGEN_DICT[f"{reg}"]["eigenvectors"]

            # COLETANDO SOLUÇÃO PARTICULAR
            part_sol = PART_SOL_DICT[f"{reg}"]

            for j in range(num_nodes):
                # CALCULANDO ALFAS
                alfa = calc_alfa(
                    N,
                    H,
                    SIGMA_T,
                    eigenvalues,
                    eigenvectors,
                    reg,
                    index_reg,
                    node,
                    psi,
                    part_sol,
                )

                # ATUALIZANDO FLUXOS ANGULARES MÉDIOS
                psiM = calc_psiM(
                    N,
                    H,
                    SIGMA_T,
                    alfa,
                    part_sol,
                    eigenvalues,
                    eigenvectors,
                    node,
                    reg,
                    index_reg,
                    psiM,
                )

                # CÁLCULO DA FONTE DE ESPALHAMENTO
                ss = calc_ss(N, W, SIGMA_S0, psiM, node, reg)

                # ATUALIZANDO FLUXOS ANGULARES
                psi = calc_psi(
                    N, H, SIGMA_T, Q, MI, ss, node, reg, index_reg, psi, psiM
                )

                node += 1

        # CÁLCULO DO FLUXO ESCALAR FINAL
        final_fi = calc_fi(N, TOTAL_NODES, W, psi)

        # SDM CONVERGE EM UMA ITERAÇÃO NESSAS CONDIÇÕES
        if iteration == 1 and NUM_REGS == 1 and TOTAL_NODES == 1:
            break

        # CÁLCULO DO DR
        dr = calc_dr(initial_fi, final_fi)
        if dr < PREC:
            break

    # TAXA DE ABSORÇÃO

    # FLUXO ESCALAR MÉDIO
    average_fi = 2 * calc_fi(N, TOTAL_NODES - 1, W, psiM)

    # CALCULANDO SIGMA_A
    SIGMA_A = calc_sigmaA(SIGMA_T, SIGMA_S0)

    # CALCULANDO TAXA DE ABSORÇÃO
    abs_rate = calc_abs_rate(NUM_NODES, REGS, average_fi, H, SIGMA_A)

    # TAXA DE FUGA
    escape_rate = calc_escape_rate(N, psi, MI, W)

    # COLETANDO TEMPO FINAL
    FINAL_TIME = perf_counter()

    # CALCULANDO O TEMPO DE EXECUÇÃO
    execution_time = abs(FINAL_TIME - INITIAL_TIME)

    return final_fi, psi, iteration, abs_rate, escape_rate, execution_time
