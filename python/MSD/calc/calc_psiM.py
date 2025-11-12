from numpy import exp, ndarray


def calc_psiM(
    N: int,
    H: ndarray,
    SIGMA_T: list,
    alfa: ndarray,
    part_sol: ndarray,
    eigenvalues: ndarray,
    eigenvectors: ndarray,
    node: int,
    reg: int,
    index_reg: int,
    psiM: ndarray,
):
    for i in range(N):
        soma = 0
        for j in range(N):
            if eigenvalues[j] > 0:
                exponencial = 1 - exp(
                    (-SIGMA_T[reg] * H[index_reg]) / abs(eigenvalues[j])
                )
            else:
                exponencial = (
                    exp((-SIGMA_T[reg] * H[index_reg]) / abs(eigenvalues[j])) - 1
                )

            soma += eigenvalues[j] * alfa[j] * eigenvectors[i][j] * exponencial
        psiM[node][i] = ((1 / (H[index_reg] * SIGMA_T[reg])) * soma) + part_sol[i]

    return psiM
