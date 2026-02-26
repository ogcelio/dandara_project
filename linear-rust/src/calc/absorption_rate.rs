/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn abs_rate(
    reg_nodes: &[i32],
    h: &[f64],
    avg_fi: &[f64],
    sigma_t: &[f64],
    sigma_s0: &[f64],
) -> Vec<f64> {
    let mut avg_fi_iter = avg_fi.iter();

    reg_nodes
        .iter()
        .enumerate()
        .map(|(reg, &n_nodes)| {
            let sigma_a = sigma_t[reg] - sigma_s0[reg];

            let sum: f64 = avg_fi_iter.by_ref().take(n_nodes as usize).sum();

            sum * sigma_a * h[reg]
        })
        .collect()
}
