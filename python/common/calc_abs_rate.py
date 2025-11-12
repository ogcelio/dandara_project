from numpy import zeros


def calc_abs_rate(NN, regs, average_fi, hj, sigmaA):
    abs_rate = zeros(len(regs))
    node_init = 0
    soma = 0
    NNT = 0
    for i, reg in enumerate(regs):
        NNT += NN[i]
        for node in range(node_init, NNT):
            soma += sigmaA[reg - 1] * average_fi[node] * hj[i]
        abs_rate[i] = soma
        soma = 0
        node_init = NNT

    return abs_rate
