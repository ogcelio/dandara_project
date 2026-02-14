/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

// HEADER
#include "../../../include/methods/msd/alpha.h"

#include <cblas.h>

void
calc_alpha(
    const int N,
    const double ALPHA_MATRIX[SCR (N * N)],
    const double SOL_DIF[SCR N],
    double alpha[SCR N])
{
    cblas_dgemv(
        CblasRowMajor, // Ordem da matriz (C é Row Major)
        CblasNoTrans,  // Não transpor a ALPHA_MATRIX
        N,             // Número de linhas
        N,             // Número de colunas
        1.0,           // Escalar multiplicador (alpha da fórmula BLAS)
        ALPHA_MATRIX, // Ponteiro para os dados da matriz
        N,             // Numero de colunas
        SOL_DIF,       // Vetor X
        1,             // Passo entre elementos de X
        0.0,           // Escalar para o vetor de destino (beta da fórmula BLAS)
        alpha,         // Vetor de destino Y
        1              // Passo entre elementos de Y
    );
}
