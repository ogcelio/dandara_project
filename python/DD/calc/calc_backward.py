def backward(N, NN, NNT, REGS, psi, H, ss, Q, MI, SIGMA_T):
    """
    Calcula os fluxos angulares do processo iterativo de volta do método numérico Diamond Difference.

    Parâmetros:
    ----------
    N -> int
        Ordem da quadratura do problema.
    NN -> Array (Lista, Tupla ou Array NumPy)
        Contém o número de nodos de cada REGIÃO do domínio.
    NNT -> int
        Quantidade de nodos totais do domínio.
    REGS -> Array (Lista, Tupla ou Array Numpy)
        Contém a zona material de cada REGIÃO do domínio.
    psi -> Array Numpy
        Contém todos os N fluxos angulares do domínio, separados por cada PONTO do mesmo.
    H -> Array (Lista, Tupla ou Array Numpy)
        Contém o tamanho dos nodos de cada REGIÃO do domínio.
    ss -> Array (Lista, Tupla ou Array Numpy)
        Contém o valor da fonte de espalhamento de cada NODO do domínio.
    Q -> Array (Lista, Tupla ou Array Numpy)
        Contém o valor da fonte fixa em cada REGIÃO do domínio.
    MI -> Array (Lista, Tupla ou Array Numpy)
        Contém o valor das N raízes do polinônio de Lagrange, que representam as direções discretas de propagação das particulas neutras.
    SIGMA_T -> Array (Lista, Tupla ou Array Numpy)
        Contém o valor da seção de choque macroscópica total de cada REGIÃO.

    Retorna:
    -------
    psi -> Array Numpy
        Fluxos angulares atualizados.
    """
    node = NNT - 1

    for index_reg, num_nodes in reversed(list(enumerate(NN))):
        reg = REGS[index_reg] - 1
        for j in range(num_nodes):
            for m in range(N // 2, N):
                psi[node][m] = (
                    (
                        ((abs(MI[m]) / H[index_reg]) - (SIGMA_T[reg] / 2))
                        * psi[node + 1][m]
                    )
                    + ss[node]
                    + Q[reg]
                ) / ((abs(MI[m]) / H[index_reg]) + (SIGMA_T[reg] / 2))

            node -= 1

    return psi
