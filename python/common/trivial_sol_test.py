def trivial_sol(Qj, cce, ccd, n_regs):
    is_all_0 = True
    for i in range(0, n_regs):
        if Qj[i] != 0.0:
            is_all_0 = False  # Teste para saber se todas as fontes são 0
            break

    if ccd == 0.0 and cce == 0.0 and is_all_0 == True:
        return True
    return False
