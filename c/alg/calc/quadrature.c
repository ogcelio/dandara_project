#define _USE_MATH_DEFINES
#include "quadrature.h"
#include <math.h>

void
calc_quadrature(int N, double MI[], double W[])
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

            // Derivada do polinômio de Legendre
            DP = N * (u * P1 - P2) / (u * u - 1.0);
            u1 = u;
            u = u1 - (P1 / DP);

            if (fabs(u - u1) < 1e-15) break;
        }

        double peso = 2.0 / ((1.0 - u * u) * (DP * DP));

        // Atribui o peso e a raiz no mesmo índice
        MI[M - i] = u;       // Raiz positiva
        W[M - i]  = peso;    // Peso correspondente

        MI[N - i] = -u;      // Raiz negativa
        W[N - i]  = peso;    // Peso correspondente
    }
}
