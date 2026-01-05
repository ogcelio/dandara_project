module __calc_psim__

export calc_psim
    function
    calc_psim(N::Int, NNT::Int, psi::Matrix, psim::Matrix{Float64})
        for j = 1:NNT
            for m = 1:N
                psim[j][m] = 0.5 * (psi[j + 1][m] + psi[j][m])
            end
        end
    end
end