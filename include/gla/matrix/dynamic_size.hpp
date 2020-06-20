#ifndef GLA_MATRIX_DYNAMIC_SIZE_HPP
#define GLA_MATRIX_DYNAMIC_SIZE_HPP

#include "gla/utils/traits.hpp"

namespace gla
{
    namespace matrix
    {
        template <template<typename> typename MatrixImpl, typename DataType>
        struct dynamic_base : public MatrixImpl<DataType>
        {
            template <typename data_type> using matrix_t = MatrixImpl<data_type>;

            using impl_t = MatrixImpl<DataType>;
            using data_t = typename impl_t::data_t;

            dynamic_base(int rows, int cols) : impl_t(rows, cols) {}

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

            const auto size() const
            {
                return std::make_pair(
                    this->n_rows(), this->n_cols()
                );
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

            dynamic_base<matrix_t,data_t>& operator=(std::initializer_list<data_t> elements)
            {
                /* TODO: allow impl to override this fn, use default otherwise */
                std::vector<data_t> v_elements = elements;
                this->set_elements(v_elements);
                return *this;
            }
        };
        
    } // namespace matrix
    
} // namespace gla


#endif // GLA_MATRIX_DYNAMIC_SIZE_HPP