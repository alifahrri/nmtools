#ifndef NMTOOLS_RUNTIME_NDARRAY_HPP
#define NMTOOLS_RUNTIME_NDARRAY_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core.hpp"
#include "nmtools/error.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/runtime/def.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/index/cast.hpp"
#include "nmtools/ndarray/base_ndarray.hpp"
#include "nmtools/runtime/computational_graph.hpp"

/*************************************************************************** */

namespace nmtools::runtime
{
    class ndarray
    {
    public:
        // TODO: support runtime Node to get the buffer/operands
        using buffer_type   = runtime::BufferType;
        using index_type    = runtime::IndexType;
        using graph_type    = runtime::Graph;
        using operands_type = nmtools_list<buffer_type>;

        static constexpr auto types = nmtools_tuple{
            uint8,
            uint16,
            uint32,
            uint64,
            int8,
            int16,
            int32,
            int64,
            float32,
            float64,
        };

    private:
        index_type     shape_;
        runtime::DType type_;
        buffer_type    buffer_;
        graph_type     graph_;
        bool           is_scalar_ = false;

    private:
        template <typename T>
        auto resize(const index_type& shape)
        {
            auto size = index::product(shape);

            // auto buffer = ::std::make_shared<T>();
            // buffer->resize(size);
            // buffer_ = buffer;

            using ptr_type = std::shared_ptr<T>;

            buffer_ = std::make_shared<T>();
            auto vptr = buffer_.get_if<ptr_type>();
            nmtools_panic( vptr
                , "invalid type when resize"
            );
            auto ptr = *vptr;
            ptr->resize(size);
        }

        template <typename buffer_t, typename T>
        auto assign(const T& rhs)
        {
            using ptr_type = ::std::shared_ptr<buffer_t>;
            auto flat_rhs  = unwrap(view::flatten(rhs));
            auto vptr = buffer_.template get_if<ptr_type>();
            nmtools_panic( vptr
                , "invalid type when assigning array"
            );
            auto ptr = *vptr;
            for (nm_size_t i=0; i<ptr->size(); i++) {
                at(*ptr,i) = at(flat_rhs,i);
            }
        }
    
    private:
        ndarray(buffer_type new_buffer, const index_type& shape, DType type)
            : shape_(shape)
            , type_(type)
            , buffer_(new_buffer)
        {}

    public:
        template <typename T>
        ndarray(const index_type& shape_, dtype_t<T>)
            : shape_(shape_)
        {
            is_scalar_ = (len(shape_) == 0);
            constexpr auto N = len_v<decltype(types)>;
            template_for<N>([&](auto i){
                auto dtype = at(types,i);
                using type = type_t<decltype(dtype)>;
                if constexpr (is_same_v<T,type>) {
                    type_ = to_value_v<decltype(dtype)>;
                    using buffer_t = nmtools_list<type>;
                    resize<buffer_t>(shape_);
                }
            });
        }

        template <typename shape_t, typename T, enable_if_t<is_index_array_v<shape_t>,int> =0>
        ndarray(const shape_t& shape, dtype_t<T>)
        {
            auto n = len(shape);
            shape_.resize(n);
            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                shape_[i] = shape[i];
            }
            is_scalar_ = (len(shape_) == 0);
            constexpr auto N = len_v<decltype(types)>;
            template_for<N>([&](auto i){
                auto dtype = at(types,i);
                using type = type_t<decltype(dtype)>;
                if constexpr (is_same_v<T,type>) {
                    type_ = to_value_v<decltype(dtype)>;
                    using buffer_t = nmtools_list<type>;
                    resize<buffer_t>(shape_);
                }
            });
        }

        template <typename rhs_t, enable_if_t<is_ndarray_v<rhs_t>,int> =0>
        ndarray(const rhs_t& rhs)
        {
            *this = rhs;
        }

        template <typename value_t, typename element_t, enable_if_t<is_num_v<value_t> && is_num_v<element_t>,int> =0>
        ndarray(value_t value, dtype_t<element_t>)
            : shape_()
            , type_(to_value_v<dtype_t<element_t>>)
            , buffer_(std::make_shared<nmtools_list<element_t>>())
            , graph_(graph_type{
                AdjacencyList{nmtools_list<nm_index_t>{}},
                NodeIDs{0},
                NodeAttributes{Node<>::buffer(none_t{}, type_)}
            })
            , is_scalar_(true)
        {
            using ptr_type = std::shared_ptr<nmtools_list<element_t>>;
            auto vptr = buffer_.template get_if<ptr_type>();
            nmtools_panic( vptr
                , "invalid scalar buffer"
            );
            (*vptr)->push_back(static_cast<element_t>(value));
        }

        auto is_scalar() const noexcept -> bool
        {
            return is_scalar_;
        }

        template <typename T, enable_if_t<is_num_v<T>,int> =0>
        T item() const
        {
            using buffer_t = nmtools_list<T>;
            using ptr_type = std::shared_ptr<buffer_t>;
            auto vptr = buffer_.template get_if<ptr_type>();
            nmtools_panic( vptr && (*vptr)->size() == 1
                , "ndarray: item<T>() requires an evaluated one-element buffer"
            );
            return at(*(*vptr),0);
        }

        template <typename T>
        auto data() const
        {
            using buffer_t = nmtools_list<T>;
            using ptr_type = ::std::shared_ptr<buffer_t>;
            auto vptr = buffer_.template get_if<ptr_type>();
            // nmtools_panic( vptr
            //     , "invalid type for data"
            // );
            return vptr;
        }

        template <typename T>
        auto buffer() const
        {
            // TODO: fix
            return buffer_;
        }

        template <typename shape_t>
        auto reshape(const shape_t& dst_shape) const
        {
            return this->reshape(index::cast<index_type>(dst_shape));
        }

        template <typename element_t, typename shape_t=none_t>
        auto view(dtype_t<element_t> = dtype_t<element_t>{}, const shape_t& shape=shape_t{}) const
        {
            nmtools_panic( !is_scalar_
                , "ndarray: view is not supported for scalar ndarray"
            );
            using buffer_t = nmtools_list<element_t>;
            using ptr_type = ::std::shared_ptr<buffer_t>;
            auto vptr = buffer_.template get_if<ptr_type>();
            nmtools_panic( vptr
                , "invalid type when getting view"
            );
            auto ptr = *vptr;

            // TODO: mark as unaliasable?
            // TODO: do not need ref
            // return unwrap(view::reshape(view::ref(ptr),shape_));
            if constexpr (is_none_v<shape_t>) {
                return unwrap(view::reshape(ptr,shape_));
            } else {
                nmtools_panic( utils::isequal(shape,shape_)
                    , "invalid shape when getting view"
                );
                return unwrap(view::reshape(ptr,shape));
            }
        }

        template <typename element_t, typename shape_t=none_t>
        auto mutable_view(dtype_t<element_t> = dtype_t<element_t>{}, const shape_t& shape=shape_t{})
        {
            nmtools_panic( !is_scalar_
                , "ndarray: mutable_view is not supported for scalar ndarray"
            );
            using buffer_t = nmtools_list<element_t>;
            using ptr_type = ::std::shared_ptr<buffer_t>;
            auto vptr = buffer_.template get_if<ptr_type>();
            nmtools_panic( vptr
                , "invalid type when getting mutable view"
            );
            auto ptr = *vptr;

            // TODO: read use count, if > 1, then copy
            if constexpr (is_none_v<shape_t>) {
                return unwrap(nmtools::view::mutable_reshape(ptr,shape_));
            } else {
                nmtools_panic( utils::isequal(shape,shape_)
                    , "invalid shape when getting mutable view"
                );
                return unwrap(nmtools::view::mutable_reshape(ptr,shape));
            }
        }

        template <typename rhs_t, enable_if_t<is_ndarray_v<rhs_t>,int> =0>
        ndarray& operator=(const rhs_t& rhs)
        {
            auto rhs_shape = nmtools::shape(rhs);
            auto dim = len(rhs_shape);
            shape_.resize(dim);
            is_scalar_ = (dim == 0);
            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                at(shape_,i) = at(rhs_shape,i);
            }
            using T = get_element_type_t<rhs_t>;
            constexpr auto N = len_v<decltype(types)>;
            template_for<N>([&](auto i){
                auto dtype = at(types,i);
                using type = type_t<decltype(dtype)>;
                if constexpr (is_same_v<T,type>) {
                    type_ = to_value_v<decltype(dtype)>;
                    using buffer_t = nmtools_list<type>;
                    resize<buffer_t>(shape_);
                    assign<buffer_t>(rhs);
                }
            });
            return *this;
        }

    public:
        ndarray(const index_type& shape_, runtime::DType type_);
        ndarray(const graph_type& graph_);
        auto shape() const noexcept -> index_type;
        auto size() const noexcept -> nm_size_t;
        auto dim() const noexcept -> nm_size_t;
        auto dtype() const noexcept -> DType;
        auto graph() const noexcept -> graph_type;
        void resize(const index_type& shape) noexcept;
        auto is_evaluated() const noexcept -> bool;
        auto reshape(const index_type& dst_shape) const -> ndarray;
        auto operator+(const ndarray& rhs) const -> ndarray;
        auto operator*(const ndarray& rhs) const -> ndarray;
        auto operator-(const ndarray& rhs) const -> ndarray;
        auto operator/(const ndarray& rhs) const -> ndarray;
    }; // ndarray

    template <typename array_t>
    auto array(const array_t& array)
    {
        return ndarray(array);
    }
}

/*************************************************************************** */

namespace nmtools
{
    auto add(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
    auto multiply(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
    auto subtract(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
    auto divide(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;

    // reductions
    auto sum(const runtime::ndarray& array, runtime::Axis axis=None, runtime::DTypeOrNone dtype=None, runtime::Initial initial=None, bool keepdims=false) -> runtime::ndarray;
    auto prod(const runtime::ndarray& array, runtime::Axis axis=None, runtime::DTypeOrNone dtype=None, runtime::Initial initial=None, bool keepdims=false) -> runtime::ndarray;

    // unary ufuncs
    auto cos(const runtime::ndarray& array) -> runtime::ndarray;
    auto cosh(const runtime::ndarray& array) -> runtime::ndarray;
    auto sin(const runtime::ndarray& array) -> runtime::ndarray;
    auto sinh(const runtime::ndarray& array) -> runtime::ndarray;
    auto exp(const runtime::ndarray& array) -> runtime::ndarray;
    auto exp2(const runtime::ndarray& array) -> runtime::ndarray;
    auto expm1(const runtime::ndarray& array) -> runtime::ndarray;
    auto fabs(const runtime::ndarray& array) -> runtime::ndarray;
    auto floor(const runtime::ndarray& array) -> runtime::ndarray;
    auto invert(const runtime::ndarray& array) -> runtime::ndarray;
    auto isfinite(const runtime::ndarray& array) -> runtime::ndarray;
    auto isinf(const runtime::ndarray& array) -> runtime::ndarray;
    auto isnan(const runtime::ndarray& array) -> runtime::ndarray;
    auto log(const runtime::ndarray& array) -> runtime::ndarray;
    auto log1p(const runtime::ndarray& array) -> runtime::ndarray;
    auto log2(const runtime::ndarray& array) -> runtime::ndarray;
    auto log10(const runtime::ndarray& array) -> runtime::ndarray;
    auto negative(const runtime::ndarray& array) -> runtime::ndarray;
    auto reciprocal(const runtime::ndarray& array) -> runtime::ndarray;
    auto rint(const runtime::ndarray& array) -> runtime::ndarray;
    auto signbit(const runtime::ndarray& array) -> runtime::ndarray;
    auto sqrt(const runtime::ndarray& array) -> runtime::ndarray;
    auto square(const runtime::ndarray& array) -> runtime::ndarray;
    auto tan(const runtime::ndarray& array) -> runtime::ndarray;
    auto tanh(const runtime::ndarray& array) -> runtime::ndarray;
    auto trunc(const runtime::ndarray& array) -> runtime::ndarray;
    auto arccos(const runtime::ndarray& array) -> runtime::ndarray;
    auto arccosh(const runtime::ndarray& array) -> runtime::ndarray;
    auto arcsin(const runtime::ndarray& array) -> runtime::ndarray;
    auto arcsinh(const runtime::ndarray& array) -> runtime::ndarray;
    auto arctan(const runtime::ndarray& array) -> runtime::ndarray;
    auto arctanh(const runtime::ndarray& array) -> runtime::ndarray;
    auto cbrt(const runtime::ndarray& array) -> runtime::ndarray;
    auto ceil(const runtime::ndarray& array) -> runtime::ndarray;
}

namespace nmtools
{
    auto broadcast_to(const runtime::ndarray& array, const runtime::IndexType& dst_shape) -> runtime::ndarray;
}

/*************************************************************************** */

// core implementation
#ifdef NMTOOLS_RUNTIME_NDARRAY_IMPLEMENTATION
namespace nmtools::runtime
{
    ndarray::ndarray(const IndexType& shape_, runtime::DType type_)
        : shape_(shape_)
        , type_(type_)
        , graph_{}
    {
        this->resize(shape_);
    }

    ndarray::ndarray(const graph_type& graph_)
    {
        this->graph_ = graph_;
        shape_ = nmtools::shape(graph_);
        type_  = nmtools::type(graph_);
        is_scalar_ = nmtools::is_scalar(graph_);
    }

    auto ndarray::shape() const noexcept -> ndarray::index_type
    {
        return shape_;
    }

    auto ndarray::size() const noexcept -> nm_size_t
    {
        return is_scalar_ ? 1 : index::product(shape_);
    }

    auto ndarray::dim() const noexcept -> nm_size_t
    {
        return len(shape_);
    }

    auto ndarray::dtype() const noexcept -> runtime::DType
    {
        return type_;
    }

    auto ndarray::graph() const noexcept -> ndarray::graph_type
    {
        return graph_;
    }

    auto ndarray::is_evaluated() const noexcept -> bool
    {
        // TODO: any buffer in graph should represent only itself, also the input of the graph should exactly 1
        return !static_cast<bool>(buffer_.get_if<none_t>());
    }

    inline
    void ndarray::resize(const IndexType& shape) noexcept
    {
        shape_ = shape;
        is_scalar_ = (len(shape_) == 0);
        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            auto dtype = at(types,i);
            using type = type_t<decltype(dtype)>;
            if (type_ == to_value_v<decltype(dtype)>) {
                using buffer_t = nmtools_list<type>;
                resize<buffer_t>(shape_);
            }
        });
    }

    auto ndarray::reshape(const IndexType& dst_shape) const -> ndarray
    {
        return ndarray(this->buffer_,dst_shape,this->type_);
    }

    auto ndarray::operator+(const ndarray& rhs) const -> ndarray
    {
        return add(*this,rhs);
    }

    auto ndarray::operator*(const ndarray& rhs) const -> ndarray
    {
        return multiply(*this,rhs);
    }

    auto ndarray::operator-(const ndarray& rhs) const -> ndarray
    {
        return subtract(*this,rhs);
    }
    
    auto ndarray::operator/(const ndarray& rhs) const -> ndarray
    {
        return divide(*this,rhs);
    }
}
#endif // NMTOOLS_RUNTIME_NDARRAY_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ADD_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto add(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(lhs.shape(),lhs.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (lhs.dtype() == rt) {
                auto lhs_view = lhs.view(ct);
                template_for<N>([&](auto j){
                    const auto ct = at(ndarray::types,j);
                    const auto rt = to_value_v<decltype(ct)>;
                    if (rhs.dtype() == rt) {
                        auto rhs_view = rhs.view(ct);

                        auto ctree = unwrap(fn::get_computational_tree(view::add(lhs_view,rhs_view)));
                        auto rtree = rt::to_value(ctree);
                        auto graph = fn::cse(rtree);
                        result = graph;
                    }
                });
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_ADD_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_MULTIPLY_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto multiply(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(lhs.shape(),lhs.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (lhs.dtype() == rt) {
                auto lhs_view = lhs.view(ct);
                template_for<N>([&](auto j){
                    const auto ct = at(ndarray::types,j);
                    const auto rt = to_value_v<decltype(ct)>;
                    if (rhs.dtype() == rt) {
                        auto rhs_view = rhs.view(ct);

                        auto ctree = unwrap(fn::get_computational_tree(view::multiply(lhs_view,rhs_view)));
                        auto rtree = rt::to_value(ctree);
                        auto graph = fn::cse(rtree);
                        result = graph;
                    }
                });
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_MULTIPLY_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SUBTRACT_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto subtract(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(lhs.shape(),lhs.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (lhs.dtype() == rt) {
                auto lhs_view = lhs.view(ct);
                template_for<N>([&](auto j){
                    const auto ct = at(ndarray::types,j);
                    const auto rt = to_value_v<decltype(ct)>;
                    if (rhs.dtype() == rt) {
                        auto rhs_view = rhs.view(ct);

                        auto ctree = unwrap(fn::get_computational_tree(view::subtract(lhs_view,rhs_view)));
                        auto rtree = rt::to_value(ctree);
                        auto graph = fn::cse(rtree);
                        result = graph;
                    }
                });
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_SUBTRACT_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_DIVIDE_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto divide(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(lhs.shape(),lhs.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (lhs.dtype() == rt) {
                auto lhs_view = lhs.view(ct);
                template_for<N>([&](auto j){
                    const auto ct = at(ndarray::types,j);
                    const auto rt = to_value_v<decltype(ct)>;
                    if (rhs.dtype() == rt) {
                        auto rhs_view = rhs.view(ct);

                        auto ctree = unwrap(fn::get_computational_tree(view::divide(lhs_view,rhs_view)));
                        auto rtree = rt::to_value(ctree);
                        auto graph = fn::cse(rtree);
                        result = graph;
                    }
                });
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_DIVIDE_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_BROADCAST_TO_GRAPH_IMPLEMENTATION
#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto broadcast_to(const runtime::ndarray& array, const runtime::IndexType& dst_shape) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(runtime::ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(runtime::ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (array.dtype() == rt) {
                auto input = array.view(ct);
                // TODO: better error handling
                auto ctree = unwrap(fn::get_computational_tree(view::broadcast_to(input,dst_shape)));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_BROADCAST_TO_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SUM_GRAPH_IMPLEMENTATION
#include "nmtools/array/sum.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto sum(const runtime::ndarray& array, runtime::Axis axis, runtime::DTypeOrNone dtype, runtime::Initial initial, bool keepdims) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (array.dtype() == rt) {
                auto input = array.view(ct);
                // TODO: handle type
                auto m_axis    = *axis.get_if<nm_index_t>();
                auto m_dtype   = *dtype.get_if<none_t>();
                auto m_initial = *initial.get_if<none_t>();

                // TODO: fix
                // auto ctree = unwrap(fn::get_computational_tree(view::sum(input,m_axis,m_dtype,m_initial,keepdims)));
                // auto rtree = rt::to_value(ctree);
                // auto graph = fn::cse(rtree);
                // result = graph;

                if (keepdims) {
                    auto ctree = unwrap(fn::get_computational_tree(view::sum(input,m_axis,m_dtype,m_initial,True)));
                    auto rtree = rt::to_value(ctree);
                    auto graph = fn::cse(rtree);
                    result = graph;
                } else {
                    auto ctree = unwrap(fn::get_computational_tree(view::sum(input,m_axis,m_dtype,m_initial,False)));
                    auto rtree = rt::to_value(ctree);
                    auto graph = fn::cse(rtree);
                    result = graph;
                }
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_SUM_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_PROD_GRAPH_IMPLEMENTATION
#include "nmtools/array/prod.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto prod(const runtime::ndarray& array, runtime::Axis axis, runtime::DTypeOrNone dtype, runtime::Initial initial, bool keepdims) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            const auto rt = to_value_v<decltype(ct)>;
            if (array.dtype() == rt) {
                auto input = array.view(ct);
                // TODO: handle type
                auto m_axis    = *axis.get_if<nm_index_t>();
                auto m_dtype   = *dtype.get_if<none_t>();
                auto m_initial = *initial.get_if<none_t>();

                // TODO: fix
                // auto ctree = unwrap(fn::get_computational_tree(view::prod(input,m_axis,m_dtype,m_initial,keepdims)));
                // auto rtree = rt::to_value(ctree);
                // auto graph = fn::cse(rtree);
                // result = graph;

                if (keepdims) {
                    auto ctree = unwrap(fn::get_computational_tree(view::prod(input,m_axis,m_dtype,m_initial,True)));
                    auto rtree = rt::to_value(ctree);
                    auto graph = fn::cse(rtree);
                    result = graph;
                } else {
                    auto ctree = unwrap(fn::get_computational_tree(view::prod(input,m_axis,m_dtype,m_initial,False)));
                    auto rtree = rt::to_value(ctree);
                    auto graph = fn::cse(rtree);
                    result = graph;
                }
            }
        });
        return result;
    }
}
#endif // NMTOOLS_RUNTIME_PROD_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_COS_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto cos(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::cos(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_COS_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_COSH_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/cosh.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto cosh(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::cosh(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_COSH_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SIN_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto sin(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::sin(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_SIN_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SINH_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/sinh.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto sinh(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::sinh(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_SINH_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_EXP_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto exp(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::exp(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_EXP_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_EXP2_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/exp2.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto exp2(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::exp2(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_EXP2_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_EXPM1_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/expm1.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto expm1(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::expm1(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_EXPM1_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_FABS_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto fabs(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::fabs(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_FABS_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_FLOOR_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto floor(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::floor(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_FLOOR_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_INVERT_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/invert.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto invert(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        static constexpr auto invert_types = nmtools_tuple{
            uint8,
            uint16,
            uint32,
            uint64,
            int8,
            int16,
            int32,
            int64
        };

        constexpr auto N = len_v<decltype(invert_types)>;
        template_for<N>([&](auto i){
            const auto ct = at(invert_types,i);
            if (ct == array.dtype()) {
                auto v = view::invert(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_INVERT_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ISFINITE_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/isfinite.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto isfinite(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::isfinite_int8(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ISFINITE_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ISINF_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/isinf.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto isinf(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::isinf_int8(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ISINF_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ISNAN_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/isnan.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto isnan(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::isnan_int8(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ISNAN_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_LOG_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/log.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto log(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::log(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_LOG_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_LOG1P_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/log1p.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto log1p(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::log1p(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_LOG1P_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_LOG2_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/log2.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto log2(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::log2(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_LOG2_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_LOG10_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/log10.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto log10(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::log10(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_LOG10_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_NEGATIVE_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/negative.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto negative(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::negative(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_NEGATIVE_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_RECIPROCAL_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/reciprocal.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto reciprocal(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::reciprocal(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_RECIPROCAL_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_RINT_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/rint.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto rint(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::rint(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_RINT_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SIGNBIT_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/signbit.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto signbit(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::signbit_int8(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_SIGNBIT_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SQRT_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto sqrt(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::sqrt(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_SQRT_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_SQUARE_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto square(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::square(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_SQUARE_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_TAN_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto tan(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::tan(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_TAN_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_TANH_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto tanh(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::tanh(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_TANH_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_TRUNC_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/trunc.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto trunc(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::trunc(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_TRUNC_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ARCCOS_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/arccos.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto arccos(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::arccos(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ARCCOS_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ARCCOSH_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/arccosh.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto arccosh(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::arccosh(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ARCCOSH_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ARCSIN_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto arcsin(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::arcsin(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ARCSIN_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ARCSINH_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/arcsinh.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto arcsinh(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::arcsinh(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ARCSINH_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ARCTAN_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/arctan.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto arctan(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::arctan(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ARCTAN_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_ARCTANH_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/arctanh.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto arctanh(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::arctanh(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_ARCTANH_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_CBRT_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto cbrt(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::cbrt(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_CBRT_GRAPH_IMPLEMENTATION

#ifdef NMTOOLS_RUNTIME_CEIL_GRAPH_IMPLEMENTATION
#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"

namespace nmtools
{
    auto ceil(const runtime::ndarray& array) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;
        using runtime::ndarray;

        // TODO: support default constructor for ndarray
        // auto result = rt::ndarray();
        auto result = rt::ndarray(array.shape(),array.dtype());

        constexpr auto N = len_v<decltype(ndarray::types)>;
        template_for<N>([&](auto i){
            const auto ct = at(ndarray::types,i);
            if (ct == array.dtype()) {
                auto v = view::ceil(array.view(ct));

                auto ctree = unwrap(fn::get_computational_tree(v));
                auto rtree = rt::to_value(ctree);
                auto graph = fn::cse(rtree);
                result = graph;
            }
        });

        return result;
    }
}

#endif // NMTOOLS_RUNTIME_CEIL_GRAPH_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_NDARRAY_HPP