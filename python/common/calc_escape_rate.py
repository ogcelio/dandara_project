from numpy import zeros


def calc_escape_rate(N, psiX, mi, w):
    # FUGA EM 0
    escape_rate = zeros(2)
    soma = 0
    for m in range(N // 2, N):
        soma += abs(mi[m] * w[m] * psiX[0][m])
    escape_rate[0] = soma

    # FUGA NO MÁXIMO DA ÚLTIMA REGIÃO
    soma = 0
    for m in range(N // 2):
        soma += abs(mi[m] * w[m] * psiX[len(psiX) - 1][m])
    escape_rate[1] = soma

    return escape_rate
