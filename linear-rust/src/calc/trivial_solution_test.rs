/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn trivial_solution_test(cce: f64, ccd: f64, q: &[f64]) -> bool {
    cce == 0.0 && ccd == 0.0 && q.iter().all(|&q_val| q_val == 0.0)
}
