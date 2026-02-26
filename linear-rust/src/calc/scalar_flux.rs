/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn calc_scalar_flux(w: &[f64], psi: &[f64], fi: &mut [f64]) {
    let n = w.len();

    fi.iter_mut()
        .zip(psi.chunks_exact(n))
        .for_each(|(fi_x, psi_x)| {
            let sum: f64 = w
                .iter()
                .zip(psi_x)
                .map(|(&w_n, &psi_x_n)| w_n * psi_x_n)
                .sum();

            *fi_x = 0.5 * sum;
        });
}
