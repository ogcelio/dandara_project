from numpy import zeros


def calc_ss(N, NN, NNT, REGS, psim, W, SIGMA_S0):
    node = 0
    ss = zeros(NNT)

    for index_reg, num_nodes in enumerate(NN):
        reg = REGS[index_reg] - 1
        for j in range(num_nodes):
            soma = 0

            for m in range(N):
                soma += W[m] * psim[node][m]

            ss[node] = (SIGMA_S0[reg] / 2) * soma

            node += 1

    return ss
