/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn calc_scattering_source(n: usize, w: &[f64], h_sigma_s0: &[f64], psim: &[f64], ss: &mut [f64]) {
    ss.iter_mut()
        .zip(psim.chunks_exact(n))
        .zip(h_sigma_s0.iter())
        .for_each(|((ss_j, psim_j), &h_s0_j)| {
            let sum: f64 = w
                .iter()
                .zip(psim_j)
                .map(|(&w_n, &psim_j_n)| w_n * psim_j_n)
                .sum();

            *ss_j = h_s0_j * sum;
        });
}
