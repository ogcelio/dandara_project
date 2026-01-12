#define _USER_MATH_DEFINES
#include <math.h>

void
quadrature(int N, double MI[], double W[])
{
    int M = N / 2; // Metade do vetor
    int i, j;
    double P1, P2, P3, DP, u, u1;

    for (i = 1; i <= M; i++)
    {
        // Estimativa inicial de Newton (da maior raiz para a menor positiva)
        u = cos(M_PI * (i - 0.25) / (N + 0.5));

        // Refinamento por Método de Newton
        while (1)
        {
            P1 = 1.0; P2 = 0.0;
            for (j = 0; j < N; j++)
            {
                P3 = P2;
                P2 = P1;
                P1 = ((2.0 * j + 1.0) * u * P2 - j * P3) / (j + 1.0);
            }

            DP = N * (u * P1 - P2) / (u * u - 1.0);
            u1 = u;
            u = u1 - (P1 / DP);

            if (fabs(u - u1) < 1e-15) break;
        }

        // Cálculo do peso associado a esta raiz
        W[i - 1] = 2.0 / ((1.0 - u * u) * (DP * DP));
        W[i - 1 + M] = W[i-1];

        MI[M - i] = u;
        MI[N - i] = -u;
    }
}
