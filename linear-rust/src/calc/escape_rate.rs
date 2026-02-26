/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn escape_rate(
    n: usize,
    half_n: usize,
    total_nodes: usize,
    mi: &[f64],
    w: &[f64],
    psi: &[f64],
) -> [f64; 2] {
    let total_nums: usize = total_nodes * n;

    // ESCAPE IN THE START OF THE DOMAIN
    let mi_start = &mi[half_n..n];
    let w_start = &w[half_n..n];
    let psi_start = &psi[half_n..n];

    let esc_start: f64 = mi_start
        .iter()
        .zip(w_start)
        .zip(psi_start)
        .map(|((&mi_m, &w_m), &psi_m)| (mi_m * w_m * psi_m).abs())
        .sum::<f64>();

    // ESCAPE IN THE END OF THE DOMAIN
    let mi_end = &mi[..half_n];
    let w_end = &w[..half_n];
    let psi_end = &psi[total_nums..(total_nums + half_n)];

    let esc_end: f64 = mi_end
        .iter()
        .zip(w_end)
        .zip(psi_end)
        .map(|((&mi_m, &w_m), &psi_m)| (mi_m * w_m * psi_m).abs())
        .sum::<f64>();

    [esc_start, esc_end]
}
