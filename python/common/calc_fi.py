from numpy import zeros


def calc_fi(N, NNT, w, psiX):
    fi = zeros(NNT + 1)
    for x in range(NNT + 1):
        soma_fi = 0
        for m in range(N):
            soma_fi += w[m] * psiX[x][m]
        fi[x] = (1 / 2) * soma_fi

    return fi
