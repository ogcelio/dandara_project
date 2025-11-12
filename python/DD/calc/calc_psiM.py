from numpy import zeros


def calc_psiM(N, NNT, psi):
    psim = zeros((NNT, N))
    for j in range(NNT):
        for m in range(N):
            psim[j][m] = (1 / 2) * (psi[j + 1][m] + psi[j][m])

    return psim
