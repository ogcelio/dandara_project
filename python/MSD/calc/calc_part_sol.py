from numpy.linalg import inv
from numpy import zeros, ndarray


def calc_part_sol(
    N: int, Q: list, REGS: list, SIGMA_T: list, SIGMA_S0: list, W: ndarray
) -> dict:

    part_sol_dict = dict()
    p_matrix = zeros((N, N))
    for reg in set(REGS):
        reg_index = reg - 1
        for i in range(N):
            for j in range(N):
                if i == j:
                    p_matrix[i][j] = SIGMA_T[reg_index] - (
                        (SIGMA_S0[reg_index] * W[j]) / 2
                    )

                else:
                    p_matrix[i][j] = -((SIGMA_S0[reg_index] * W[j]) / 2)

        inv_p_matrix = inv(p_matrix)

        source = [Q[reg_index] for _ in range(N)]
        part_sol = inv_p_matrix @ source

        part_sol_dict.update({f"{reg_index}": part_sol})

    return part_sol_dict
