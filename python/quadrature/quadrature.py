import numpy as np


def quadrature(N: int):
    M = int(0.5 * (N + 1))  # As raízes são simétricas
    mi = np.zeros(N)
    w = np.zeros(N)

    for i in range(1, M + 1):
        u = np.cos(
            np.pi * (i - 0.25) / (N + 0.5)
        )  # Aproximação inicial da i-ésima raiz não negativa

        while True:
            P1, P2 = 1, 0
            for j in range(N):
                P3 = P2
                P2 = P1
                P1 = ((2 * j + 1) * u * P2 - j * P3) / (
                    j + 1
                )  # Polinômio de Legendre por recorrência

            DP = N * (u * P1 - P2) / (u**2 - 1)  # Derivada do polinômio de Legendre

            # Método de Newton para calcular as raízes
            u1 = u
            u = u1 - (P1 / DP)
            if abs(u - u1) < 10e-15:  # Critério de parada
                break

        mi[i - 1] = u  # Raiz não negativa
        mi[N - i] = -u  # Raiz negativa
        w[N - i] = 2 / ((1 - u**2) * DP**2)  # Cálculo dos pesos
        w[i - 1] = w[N - i]

    Mi = np.sort(mi)
    for i in range(N // 2):
        mi[i] = Mi[i + N // 2]

    for i in range(N // 2):
        w[i] = w[i + N // 2]

    return mi, w
