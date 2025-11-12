from numpy import zeros


def init_psiX(N, NNT, cce, ccd):
    psiX = zeros((NNT + 1, N))
    for i in range(N // 2):
        psiX[0][i] = cce
        psiX[NNT][N // 2 + i] = ccd

    return psiX


def init_hj(NN, n_regs, esp_R):
    hj = zeros(n_regs)
    for regiao in range(n_regs):
        hj[regiao] = esp_R[regiao] / NN[regiao]  # Espessura do nodo

    return hj


def init_C0j(sigmaT, sigmaS0):
    C0j = zeros(len(sigmaT))
    for i in range(len(sigmaT)):
        C0j[i] = sigmaS0[i] / sigmaT[i]

    return C0j
