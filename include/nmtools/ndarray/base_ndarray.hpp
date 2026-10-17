#ifndef NMTOOLS_ARRAY_NDARRAY_BASE_NDARRAY_HPP
#define NMTOOLS_ARRAY_NDARRAY_BASE_NDARRAY_HPP

#include "nmtools/index/product.hpp"
#include "nmtools/index/pack.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/reverse.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/get.hpp"

namespace nmtools
{

    template <typename T>
    struct base_ndarray_t
    {
        template <typename shape_type, typename buffer_type>
        static constexpr auto initialize_shape(const buffer_type& buffer)
        {
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else /* if constexpr (is_fixed_index_array_v<shape_type>) */ {
                auto shape = shape_type {};
                if constexpr (is_resizable_v<shape_type>) {
                    shape.resize(1);
                }
                constexpr auto dim = len_v<shape_type>;
                if constexpr (dim > 0) {
                    // to accommodate clipped shape
                    template_for<dim>([&](auto index){
                        // only assign to non-constant elements
                        if constexpr (!is_constant_index_v<decltype(at(shape,index))>) {
                            at(shape,index) = 1;
                        }
                    });
                } else {
                    for (size_t i=0; i<len(shape)-1; i++) {
                        // only assign to non-constant elements
                        if constexpr (!is_constant_index_v<decltype(at(shape,i))>) {
                            at(shape,i) = 1;
                        }
                    }
                }
                // only assign to non-constant last element
                if constexpr (!is_constant_index_v<decltype(at(shape,ct_v<-1>))>) {
                    at(shape,ct_v<-1>) = len(buffer);
                }
                return shape;
            }
        }

        template <typename buffer_type>
        static constexpr auto initialize_data()
        {
            auto buffer = buffer_type {};
            if constexpr (is_resizable_v<buffer_type>) {
                buffer.resize(1);
            }
            at(buffer,len(buffer)-1) = 0;
            return buffer;
        }

        template <typename strides_type, typename shape_type>
        static constexpr auto compute_strides(const shape_type& shape)
        {
            auto result  = index::compute_strides(shape);
            if constexpr (is_same_v<strides_type,decltype(result)>) {
                return result;
            } else {
                auto strides = strides_type{};
                [[maybe_unused]] auto dim = len(result);
                if constexpr (is_resizable_v<strides_type>) {
                    strides.resize(dim);
                }
                if constexpr (is_tuple_v<strides_type>) {
                    // tuples only support compile-time indices
                    constexpr auto N = len_v<strides_type>;
                    template_for<N>([&](auto I){
                        at(strides,I) = at(result,I);
                    });
                } else if constexpr (!is_constant_index_array_v<strides_type>) {
                    for (size_t i=0; i<dim; i++) {
                        at(strides,i) = at(result,i);
                    }
                }
                return strides;
            }
        }

        // column-major counterpart of compute_strides
        template <typename strides_type, typename shape_type>
        static constexpr auto compute_col_strides(const shape_type& shape)
        {
            auto result  = index::compute_col_major_strides(shape);
            if constexpr (is_same_v<strides_type,decltype(result)>) {
                return result;
            } else {
                auto strides = strides_type{};
                [[maybe_unused]] auto dim = len(result);
                if constexpr (is_resizable_v<strides_type>) {
                    strides.resize(dim);
                }
                if constexpr (is_tuple_v<strides_type>) {
                    // tuples only support compile-time indices; needed e.g.
                    // for clipped strides whose maxima differ per mode, so
                    // the col-major result is a different type than the
                    // row-major one and cannot take the is_same_v shortcut
                    constexpr auto N = len_v<strides_type>;
                    template_for<N>([&](auto I){
                        at(strides,I) = at(result,I);
                    });
                } else if constexpr (!is_constant_index_array_v<strides_type>) {
                    for (size_t i=0; i<dim; i++) {
                        at(strides,i) = at(result,i);
                    }
                }
                return strides;
            }
        }

        constexpr T* self()
        {
            return static_cast<T*>(this);
        }

        constexpr const T* self() const
        {
            return static_cast<const T*>(this);
        }

        constexpr auto& shape() const
        {
            return self()->shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        constexpr auto& strides() const
        {
            return self()->strides_;
        }

        constexpr decltype(auto) data() const
        {
            return &self()->data_[0];
        } // data()

        constexpr decltype(auto) data()
        {
            return &self()->data_[0];
        } // data()

        constexpr auto size() const
        {
            using buffer_type = remove_cvref_t<decltype(self()->data_)>;
            if constexpr (is_fixed_size_v<buffer_type>) {
                constexpr auto size_ = fixed_size_v<buffer_type>;
                return ct_v<size_>;
            } else {
                // assume flat
                // return len(self()->data_);
                return index::product(shape());
            }
        }

        template <typename...size_types>
        constexpr decltype(auto) operator()(const size_types&...indices)
        {
            return nmtools::at(self()->data_,self()->offset(index::pack_indices(indices...)));
        } // operator()

        template <typename...size_types>
        constexpr decltype(auto) operator()(const size_types&...indices) const
        {
            return nmtools::at(self()->data_,self()->offset(index::pack_indices(indices...)));
        } // operator()
    }; // base_ndarray_t

    template <typename shape_type>
    using resolve_stride_type_t = resolve_optype_t<index::compute_strides_t,shape_type>;
} // namespace nmtools

#endif // NMTOOLS_ARRAY_NDARRAY_BASE_NDARRAY_HPP