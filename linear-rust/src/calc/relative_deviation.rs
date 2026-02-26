/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

fn relative_deviation(initial_fi: &[f64], final_fi: &[f64]) -> f64 {
    let (max_diff, max_final) = initial_fi
        .iter()
        .zip(final_fi)
        .map(|(&init, &fin)| ((init - fin).abs(), fin.abs()))
        .fold((0.0f64, 0.0f64), |(temp_diff, temp_final), (diff, val)| {
            (temp_diff.max(diff), temp_final.max(val))
        });

    max_diff / max_final
}
