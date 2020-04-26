#ifndef GLA_MATRIX_BACKEND_ARMADILLO_DYNAMIC_SIZE_HPP
#define GLA_MATRIX_BACKEND_ARMADILLO_DYNAMIC_SIZE_HPP

#include <armadillo>

#include "gla/matrix/dynamic_size.hpp"

namespace gla
{
    namespace backend
    {
        namespace armadillo
        {
            namespace matrix
            {
                template <typename DataType>
                struct dynamic_impl : arma::Mat<DataType>
                {
                    using data_t = DataType;
                    using base_t = arma::Mat<DataType>;

                    dynamic_impl(int rows, int cols) : base_t(rows, cols) {}
                    
                    const int n_rows() const
                    {
                        return base_t::n_rows;
                    }

                    const int n_cols() const
                    {
                        return base_t::n_cols;
                    }

                    void resize(int row, int col)
                    {
                        base_t::resize(row,col);
                    }

                    void set_elements(const std::vector<data_t> &elements)
                    {
                        auto n_rows = this->n_rows();
                        auto n_cols = this->n_cols();
                        assert(elements.size()==n_rows*n_cols);
                        /* TODO : find proper way to copy */
                        for (int i=0; i<n_rows; i++)
                            for (int j=0; j<n_cols; j++) {
                                auto element = elements[i*n_cols+j];
                                base_t::operator()(i,j) = element;
                            }
                    }
                };

                template <typename data_type>
                using dynamic = ::gla::matrix::dynamic_base<dynamic_impl,data_type>;

            } // namespace matrix
        } // namespace armadillo
        
    } // namespace backend
    
} // namespace gla

#endif // GLA_MATRIX_BACKEND_ARMADILLO_DYNAMIC_SIZE_HPP