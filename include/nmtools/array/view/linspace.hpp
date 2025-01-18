#ifndef NMTOOLS_ARRAY_VIEW_LINSPACE_HPP
#define NMTOOLS_ARRAY_VIEW_LINSPACE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/array/core/decorator.hpp"

namespace nmtools::index
{
    struct linspace_step_t {};

    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t>
    constexpr auto linspace_step(const start_t& start, const stop_t& stop, num_t num, endpoint_t endpoint)
    {
        using result_t = meta::resolve_optype_t<linspace_step_t,start_t,stop_t,num_t,endpoint_t>;
        
        auto result = result_t {};

        result = ((float)stop - (float)start) / (endpoint ? num - 1 : num);

        return result;
    }

    struct linspace_shape_t {};

    template <typename start_t, typename stop_t, typename num_t>
    constexpr auto linspace_shape(const start_t&, const stop_t&, [[maybe_unused]] num_t num)
    {
        using result_t = meta::resolve_optype_t<linspace_shape_t,start_t,stop_t,num_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(1);
            }
            at(result,meta::ct_v<0>) = num;
        }

        return result;
    }
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct LINSPACE_STEP_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct LINSPACE_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t>
    struct resolve_optype<
        void, index::linspace_step_t, start_t, stop_t, num_t, endpoint_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_num_v<start_t>
                || !is_num_v<stop_t>
                || !is_num_v<num_t>
            ) {
                using type = error::LINSPACE_STEP_UNSUPPORTED<start_t,stop_t,num_t,endpoint_t>;
                return as_value_v<type>;
            } else {
                using type = conditional_t<is_floating_point_v<start_t>,start_t,float>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // linspace_step_t

    template <typename start_t, typename stop_t, typename num_t>
    struct resolve_optype<
        void, index::linspace_shape_t, start_t, stop_t, num_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_num_v<start_t>
                || !is_num_v<stop_t>
                || !is_num_v<num_t>
            ) {
                using type = error::LINSPACE_SHAPE_UNSUPPORTED<start_t,stop_t,num_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<num_t>
                || is_clipped_integer_v<num_t>
            ) {
                using type = nmtools_tuple<num_t>;
                return as_value_v<type>;
            } else {
                // TODO: support small vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // nmtools::meta

namespace nmtools::view
{
    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t, typename T>
    struct linspace_t
    {
        using start_type = meta::fwd_attribute_t<start_t>;
        using stop_type  = meta::fwd_attribute_t<stop_t>;
        using num_type   = num_t;
        using endpoint_type = endpoint_t;
        using step_type     = meta::resolve_optype_t<index::linspace_step_t,start_type,stop_type,num_type,endpoint_t>;
        using element_type  = T;
        // TODO: rename array_type to operand_type
        using array_type = nmtools_tuple<>;
        using shape_type = meta::resolve_optype_t<index::linspace_shape_t,start_type,stop_type,num_type>;

        const start_type    start;
        const stop_type     stop;
        const num_type      num;
        const endpoint_type endpoint;
        const step_type     step;
        const shape_type    shape_;

        constexpr linspace_t(const start_t& start, const stop_t& stop, num_t num, endpoint_t endpoint)
            : start(fwd_attribute(start))
            , stop(fwd_attribute(stop))
            , num(num)
            , endpoint(endpoint)
            , step(index::linspace_step(start,stop,num,endpoint))
            , shape_(index::linspace_shape(start,stop,num))
        {}

        constexpr auto operands() const
        {
            return array_type{};
        }

        constexpr auto attributes() const
        {
            return nmtools_tuple{start,stop,num,endpoint};
        }

        constexpr auto shape() const
        {
            return shape_;
        }

        constexpr auto dim() const
        {
            return len(shape_);
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            auto i = at(indices_,meta::ct_v<0>);
            return static_cast<element_type>(start) + (i * step);
        }
    }; // linspace_t

    template <typename start_t, typename stop_t, typename num_t=nm_size_t, typename endpoint_t=meta::true_type, typename retstep_t=meta::false_type, typename dtype_t=none_t>
    constexpr auto linspace(const start_t& start, const stop_t& stop, num_t num=num_t{50}, endpoint_t endpoint=endpoint_t{}, retstep_t=retstep_t{}, dtype_t=dtype_t{})
    {
        using T = meta::conditional_t<
            is_none_v<dtype_t>
            , meta::conditional_t<
                meta::is_floating_point_v<start_t>
                , start_t
                , float>
            , get_dtype_t<dtype_t>
        >;
        using result_t = decorator_t<linspace_t,start_t,stop_t,num_t,endpoint_t,T>;

        constexpr auto retstep = meta::to_value_v<retstep_t>;
        if constexpr (retstep) {
            auto step = index::linspace_step(start,stop,num,endpoint);
            using step_t   = decltype(step);
            using return_t = nmtools_tuple<result_t,step_t>;
            return return_t{
                result_t{{start,stop,num,endpoint}}
                , step
            };
        } else {
            return result_t{{start,stop,num,endpoint}};
        }
    } // linspace
} // nmtools::view

namespace nmtools::meta
{
    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t, typename T>
    struct is_ndarray<
        view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >
    > : true_type {};

    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t, typename T>
    struct get_element_type<
        view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >
    > {
        using type = T;
    };

    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t, typename T>
    struct fixed_size<
        view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >
    > {
        using view_type  = view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                constexpr auto shape = to_value_v<shape_type>;
                return index::product(shape);
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t, typename T>
    struct fixed_shape<
        view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >
    > {
        using view_type  = view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                constexpr auto shape = to_value_v<shape_type>;
                return shape;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename start_t, typename stop_t, typename num_t, typename endpoint_t, typename T>
    struct bounded_size<
        view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >
    > : fixed_size<
        view::decorator_t< view::linspace_t, start_t, stop_t, num_t, endpoint_t, T >
    > {};
}

#endif // NMTOOLS_ARRAY_VIEW_LINSPACE_HPP