from numpy import ndarray, float64


def calc_psi(
    N: int,
    H: ndarray,
    SIGMA_T: list,
    Q: list,
    MI: ndarray,
    ss: float64,
    node: int,
    reg: int,
    index_reg: int,
    psi: ndarray,
    psiM: ndarray,
):
    for m in range(N // 2):
        psi[node + 1][m] = (
            (H[index_reg] / abs(MI[m])) * (ss + Q[reg] - (SIGMA_T[reg] * psiM[node][m]))
        ) + psi[node][m]

    for m in range(N // 2, N):
        psi[node][m] = (
            (H[index_reg] / abs(MI[m])) * (ss + Q[reg] - (SIGMA_T[reg] * psiM[node][m]))
        ) + psi[node + 1][m]

    return psi
