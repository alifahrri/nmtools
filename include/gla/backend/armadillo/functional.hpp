#ifndef GLA_FUNCTIONAL_BACKEND_ARMADILLO_HPP

#include <armadillo>
#include <tuple>

#include "gla/functional/functional.hpp"

namespace gla
{
    namespace backend
    {
        namespace armadillo
        {
            struct functional_impl
            {
                template <typename Matrix>
                static auto lu_decomposition(const Matrix& matrix)
                {
                    arma::mat L, U, P;
                    arma::lu(L, U, P, matrix);
                    return std::make_tuple(L,U);
                }

                template <typename Matrix>
                static auto inverse(const Matrix& matrix)
                {
                    auto inv = arma::inv(matrix);
                    return inv;
                }

                template <typename Matrix>
                static auto transpose(const Matrix& matrix)
                {
                    auto trans = matrix.t();
                    return trans;
                }
            };

            using functional = functional_base<functional_impl>;
            
        } // namespace armadillo
    } // namespace backend
} // namespace gla


#endif // GLA_FUNCTIONAL_BACKEND_ARMADILLO_HPP