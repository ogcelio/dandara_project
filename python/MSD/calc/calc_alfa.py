from numpy import exp, ndarray, zeros
from numpy.linalg import inv


def calc_alfa(
    N: int,
    H: ndarray,
    SIGMA_T: list,
    eigenvalues: ndarray,
    eigenvectors: ndarray,
    reg: int,
    index_reg: int,
    node: int,
    psi: ndarray,
    part_sol: ndarray,
):
    solution_difference = zeros(N)
    for i in range(N // 2):
        solution_difference[i] = psi[node][i] - part_sol[i]
        solution_difference[N // 2 + i] = (
            psi[node + 1][N // 2 + i] - part_sol[N // 2 + i]
        )

    # CÁLCULO DA MATRIZ GERADORA DOS ALFAS
    alfa_matrix = zeros((N, N))

    for i in range(N // 2):
        # PARTE DE CIMA DA MATRIZ
        for j in range(N):
            if eigenvalues[j] > 0:
                exponential = 1
            else:
                exponential = exp((-SIGMA_T[reg] * H[index_reg]) / abs(eigenvalues[j]))

            alfa_matrix[i][j] = eigenvectors[i][j] * exponential

    # PARTE DE BAIXO DA MATRIZ
    for i in range(N // 2, N):
        for j in range(N):
            if eigenvalues[j] < 0:
                exponential = 1
            else:
                exponential = exp((-SIGMA_T[reg] * H[index_reg]) / abs(eigenvalues[j]))

            alfa_matrix[i][j] = eigenvectors[i][j] * exponential

    inv_alfa_matrix = inv(alfa_matrix)

    # CÁLCULO DOS ALFAS
    alfa = inv_alfa_matrix @ solution_difference

    return alfa
