module __quadrature__
	export quadrature!

	function quadrature!(N::Int, MI::Vector{Float64}, W::Vector{Float64})
        M = div(N, 2)  # Divisão inteira

        for i in 1:M
            # Estimativa inicial
            u = cospi((i - 0.25) / (N + 0.5))

            # Método de Newton
            dp = 0.0 # Escopo da variável
            while true
                p1, p2 = 1.0, 0.0
                for j in 0:(N-1)
                    p3 = p2
                    p2 = p1
                    p1 = ((2.0 * j + 1.0) * u * p2 - j * p3) / (j + 1.0)
                end

                dp = N * (u * p1 - p2) / (u^2 - 1.0)
                u1 = u
                u = u1 - (p1 / dp)

                abs(u - u1) < 1e-15 && break
            end

            W[i] = 2.0 / ((1.0 - u^2) * dp^2)
            W[i + M] = W[i]

            # Atribuição MI (Ajustado para índice 1)
            MI[M - i + 1] = u
            MI[N - i + 1] = -u
        end
    end
end
