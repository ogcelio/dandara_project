/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn medium_flux(n: usize, psi: &[f64], psim: &mut [f64]) {
    psim.iter_mut()
        .zip(psi)
        .zip(&psi[n..])
        .for_each(|((dest, &minus_half), &plus_half)| *dest = 0.5 * (minus_half + plus_half));
}
