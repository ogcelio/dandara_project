/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

use std::f64::consts::PI;

fn quadrature(n: i32) -> (Box<[f64]>, Box<[f64]>) {
    let m: i32 = n / 2;
    let n_float: f64 = n as f64;

    let mut w = vec![0.0; n as usize].into_boxed_slice();
    let mut mi = vec![0.0; n as usize].into_boxed_slice();
    let mut dp;

    for i in 1..=m {
        let i_float: f64 = i as f64;
        let mut u: f64 = (PI * (i_float - 0.25) / (n_float + 0.5)).cos();

        loop {
            let mut p1: f64 = 1.0;
            let mut p2: f64 = 0.0;

            for j in 0..n {
                let j_float: f64 = j as f64;
                let p3: f64 = p2;
                p2 = p1;
                p1 = ((2.0 * j_float + 1.0) * u * p2 - j_float * p3) / (j_float + 1.0);
            }

            dp = n as f64 * (u * p1 - p2) / (u * u - 1.0);

            let u1 = u;
            u = u1 - (p1 / dp);

            if (u - u1).abs() < 1e-15 {
                break;
            }
        }

        let weight = 2.0 / ((1.0 - u * u) * (dp * dp));

        let index_pos: usize = (m - i) as usize;
        let index_neg: usize = (n - i) as usize;

        mi[index_pos] = u;
        w[index_pos] = weight;

        mi[index_neg] = -u;
        w[index_neg] = weight;
    }

    (mi, w)
}
