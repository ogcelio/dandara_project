def calc_dr(initial_fi, final_fi):
    result = abs(initial_fi - final_fi)

    # Coletando os maiores de cada vetor, em módulo
    final_higher = max(final_fi, key=abs)
    result_higher = max(result)

    dr = result_higher / final_higher

    return dr
