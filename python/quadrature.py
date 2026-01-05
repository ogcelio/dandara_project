from numpy import cos, pi


def quadrature(N, MI, W):
    """
    Modifica MI e W in-place.
    N deve ser par.
    """
    M = N // 2

    for i in range(1, M + 1):
        # Estimativa inicial
        u = cos(pi * (i - 0.25) / (N + 0.5))

        # Método de Newton
        while True:
            p1, p2 = 1.0, 0.0
            for j in range(N):
                p3 = p2
                p2 = p1
                p1 = ((2.0 * j + 1.0) * u * p2 - j * p3) / (j + 1.0)

            dp = N * (u * p1 - p2) / (u**2 - 1.0)
            u1 = u
            u = u1 - (p1 / dp)

            if abs(u - u1) < 1e-15:
                break

        W[i - 1] = 2.0 / ((1.0 - u**2) * dp**2)
        W[i - 1 + M] = W[i - 1]

        MI[M - i] = u
        MI[N - i] = -u
