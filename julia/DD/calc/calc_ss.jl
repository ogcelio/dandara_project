module __calc_ss__
export calc_ss
function calc_ss(
    N::Int,
    NN::Array{Int},
    REGS::Array{Int},
    psim::Matrix{Float64},
    W::Array{Float64},
    SIGMA_S0::Array{Float64},
    ss::Array{Float64},
)
    node = 1
    for (index, num_nodes) in enumerate(NN)
        reg = REGS[index]

        for j = 1:num_nodes
            sum = 0

            for m = 1:N
                sum += W[m] * psim[node][m]
            end

            ss[node] = (SIGMA_S0[reg] / 2) * sum

            node += 1
        end
    end
end
end