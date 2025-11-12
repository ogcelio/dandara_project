from numpy.linalg import eig
from numpy import zeros, ndarray


def calc_eigen(N: int, REGS: list, MI: ndarray, W: ndarray, C0: ndarray) -> dict:
    eigen = dict()
    A_matrix = zeros((N, N))
    for reg in set(REGS):
        reg_index = reg - 1
        for i in range(N):
            for j in range(N):
                if i == j:
                    A_matrix[i][j] = (1 / MI[i]) - (
                        (C0[reg_index] * W[j]) / (2 * MI[i])
                    )

                else:
                    A_matrix[i][j] = -((C0[reg_index] * W[j]) / (2 * MI[i]))

        # ENCONTRANDO AUTOVALORES E AUTOVETORES
        eigenvalue_lambda, eigenvectors = eig(A_matrix)
        eigenvalues = eigenvalue_lambda

        # TRANSFORMANDO LAMBDA EM NI
        for i, eigenvalue in enumerate(eigenvalues):
            eigenvalues[i] = 1 / eigenvalue

        eigen.update(
            {f"{reg_index}": {"eigenvalues": eigenvalues, "eigenvectors": eigenvectors}}
        )
    return eigen
