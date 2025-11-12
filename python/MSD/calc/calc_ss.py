from numpy import ndarray


def calc_ss(N: int, W: ndarray, SIGMA_S0: list, psiM: ndarray, node: int, reg: int):
    soma = 0
    for m in range(N):
        soma += W[m] * psiM[node][m]

    ss = (SIGMA_S0[reg] / 2) * soma

    return ss
