/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#include <cblas.h>

void
calc_alpha(
    int N,
    double ALPHA_MATRIX[N][N],
    double SOL_DIF[N],
    double alpha[N])
{
    cblas_dgemv(
        CblasRowMajor, // Ordem da matriz (C é Row Major)
        CblasNoTrans,  // Não transpor a ALPHA_MATRIX
        N,             // Número de linhas
        N,             // Número de colunas
        1.0,           // Escalar multiplicador (alpha da fórmula BLAS)
        (double *)ALPHA_MATRIX, // Ponteiro para os dados da matriz
        N,             // Numero de colunas
        SOL_DIF,       // Vetor X
        1,             // Passo entre elementos de X
        0.0,           // Escalar para o vetor de destino (beta da fórmula BLAS)
        alpha,         // Vetor de destino Y
        1              // Passo entre elementos de Y
    );
}
