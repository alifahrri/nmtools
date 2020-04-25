#ifndef GLA_FUNCTIONAL_BACKEND_EIGEN_HPP
#define GLA_FUNCTIONAL_BACKEND_EIGEN_HPP

#include <Eigen/Dense>
#include <tuple>

#include "gla/utils/traits.hpp"
#include "gla/functional/functional.hpp"

namespace gla
{
    namespace functional
    {
        namespace backend
        {
            namespace eigen
            {
                struct functional_impl
                {
                    template <typename Matrix>
                    static auto lu_decomposition(const Matrix &matrix)
                    {
                        static_assert(utils::traits::has_n_cols_v<Matrix>);
                        static_assert(utils::traits::has_n_rows_v<Matrix>);
                        int n_rows = matrix.n_rows();
                        int n_cols = matrix.n_cols();
                        Eigen::FullPivLU<Eigen::MatrixXd> lu_mat = matrix.fullPivLu();
                        Eigen::MatrixXd l = Eigen::MatrixXd::Identity(n_rows,n_rows);
                        l.block(0,0,n_rows,n_cols).triangularView<Eigen::StrictlyLower>() = lu_mat.matrixLU();
                        Eigen::MatrixXd u = lu_mat.matrixLU().triangularView<Eigen::Upper>();
                        return std::make_tuple(l,u);
                    }
                };

                using functional = functional_base<functional_impl>;
                
            } // namespace eigen
            
        } // namespace backend
                
    } // namespace functional
    
} // namespace gla

#endif  // GLA_FUNCTIONAL_BACKEND_EIGEN_HPP