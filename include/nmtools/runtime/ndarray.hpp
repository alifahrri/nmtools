#ifndef NMTOOLS_RUNTIME_NDARRAY_HPP
#define NMTOOLS_RUNTIME_NDARRAY_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core.hpp"
#include "nmtools/error.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/runtime/def.hpp"
#include "nmtools/array/ref.hpp"
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

    public:
        template <typename T>
        ndarray(const index_type& shape_, dtype_t<T>)
            : shape_(shape_)
        {
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

        template <typename element_t>
        auto view(dtype_t<element_t> = dtype_t<element_t>{}) const
        {
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
            return unwrap(view::reshape(ptr,shape_));
        }

        template <typename element_t>
        auto mutable_view(dtype_t<element_t> = dtype_t<element_t>{})
        {
            using buffer_t = nmtools_list<element_t>;
            using ptr_type = ::std::shared_ptr<buffer_t>;
            auto vptr = buffer_.template get_if<ptr_type>();
            nmtools_panic( vptr
                , "invalid type when getting mutable view"
            );
            auto ptr = *vptr;

            // TODO: read use count, if > 1, then copy
            return unwrap(nmtools::view::mutable_reshape(ptr,shape_));
        }

        template <typename rhs_t, enable_if_t<is_ndarray_v<rhs_t>,int> =0>
        ndarray& operator=(const rhs_t& rhs)
        {
            auto rhs_shape = nmtools::shape(rhs);
            auto dim = len(rhs_shape);
            if (shape_.size() < dim) {
                shape_.resize(dim);
            }
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

// TODO: move out to nmtools namespace
namespace nmtools::runtime
{
    auto add(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
    auto multiply(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
    auto subtract(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
    auto divide(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray;
}

namespace nmtools
{
    auto broadcast_to(const runtime::ndarray& array, const runtime::IndexType& dst_shape) -> runtime::ndarray;
}

/*************************************************************************** */

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
    }

    auto ndarray::shape() const noexcept -> ndarray::index_type
    {
        return shape_;
    }

    auto ndarray::size() const noexcept -> nm_size_t
    {
        return index::product(shape_);
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

namespace nmtools::runtime
{
    auto add(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;

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

namespace nmtools::runtime
{
    auto multiply(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;

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

namespace nmtools::runtime
{
    auto subtract(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;

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

namespace nmtools::runtime
{
    auto divide(const runtime::ndarray& lhs, const runtime::ndarray& rhs) -> runtime::ndarray
    {
        namespace fn = functional;
        namespace rt = runtime;

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

#endif // NMTOOLS_RUNTIME_NDARRAY_HPP