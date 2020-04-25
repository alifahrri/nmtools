#ifndef GLA_MATRIX_DYNAMIC_SIZE_HPP
#define GLA_MATRIX_DYNAMIC_SIZE_HPP

#include "gla/utils/traits.hpp"

namespace gla
{
    namespace matrix
    {
        template <template<typename> typename MatrixImpl, typename DataType>
        struct dynamic : public MatrixImpl<DataType>
        {
            using impl_t = MatrixImpl<DataType>;
            using data_t = typename impl_t::data_t;

            dynamic(int rows, int cols) : impl_t(rows, cols) {}

            const auto n_rows() const 
            {
                static_assert(
                    utils::traits::has_n_rows_v<impl_t>, 
                    "dev notes : n_rows() not implemented"
                );
                return impl_t::n_rows();
            }

            const auto n_cols() const 
            {
                static_assert(
                    utils::traits::has_n_cols_v<impl_t>, 
                    "dev notes : n_cols() not implemented"
                );
                return impl_t::n_cols();
            }

            void resize(int row, int col)
            {
                static_assert(
                    utils::traits::has_resize_v<impl_t>, 
                    "dev notes : resize() not implemented"
                );
                return impl_t::resize(row, col);
            }

            template <template<typename> typename Container>
            void set_elements(const Container<data_t> &elements)
            {
                static_assert(
                    utils::traits::has_set_elements_v<impl_t,Container<data_t>>,
                    "dev notes : set_elements() not implemented"
                );
                return impl_t::set_elements(elements);
            }
        };
        
    } // namespace matrix
    
} // namespace gla


#endif // GLA_MATRIX_DYNAMIC_SIZE_HPP