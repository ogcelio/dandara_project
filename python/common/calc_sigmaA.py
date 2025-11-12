from numpy import zeros


def calc_sigmaA(sigmaT, sigmaS0):
    sigmaA = zeros(len(sigmaT))
    for regiao in range(len(sigmaT)):
        sigmaA[regiao] = sigmaT[regiao] - sigmaS0[regiao]

    return sigmaA
