#ifndef NMTOOLS_ARRAY_VIEW_DECORATOR_HPP
#define NMTOOLS_ARRAY_VIEW_DECORATOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/array/index/product.hpp"

// TODO: move to shape.hpp
#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/array/impl/boost.hpp"
#endif

#include "nmtools/assert.hpp"

namespace nmtools::view::detail
{
    using utility::tuple_append, utility::tuple_cat;

    /**
     * @brief Helper shape function that is pointer-aware.
     * 
     * Defined in namespace detail to prevent ADL.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return constexpr auto 
     */
    template <bool force_constant_index=false, typename array_t>
    constexpr auto shape(const array_t& array)
    {
        if constexpr (meta::is_pointer_v<array_t>) {
            return ::nmtools::shape<force_constant_index>(*array);
        } else {
            return ::nmtools::shape<force_constant_index>(array);
        }
    } // shape

    /**
     * @brief Helper dim function that is pointer-aware.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto dim(const array_t& array)
    {
        if constexpr (meta::is_pointer_v<array_t>) {
            return ::nmtools::dim(*array);
        } else {
            return ::nmtools::dim(array);
        }
    } // shape

    /**
     * @brief Helper apply_at function that is pointer-aware.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @param array         input array, checked if pointer.
     * @param indices       indices to be expanded, passed as it is.
     * @return constexpr auto 
     */
    template <typename array_t, typename indices_t>
    constexpr decltype(auto) apply_at(const array_t& array, const indices_t& indices)
    {
        if constexpr (meta::is_pointer_v<array_t>) {
            return ::nmtools::apply_at(*array,indices);
        } else {
            return ::nmtools::apply_at(array,indices);
        }
    } // apply_at

    /**
     * @brief Overloaded version of apply_at that takes mutable array
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @param array         mutable array
     * @param indices       indices pack
     * @return constexpr auto 
     */
    template <typename array_t, typename indices_t>
    constexpr decltype(auto) apply_at(array_t& array, const indices_t& indices)
    {
        if constexpr (meta::is_pointer_v<array_t>) {
            return ::nmtools::apply_at(*array,indices);
        } else {
            return ::nmtools::apply_at(array,indices);
        }
    } // apply_at
} // nmtools::view::detail

#include "nmtools/array/index/pack.hpp"

namespace nmtools::view
{
    using meta::is_fixed_size_ndarray_v;

    using nmtools::index::pack_indices;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    /**
     * @brief provide generic common implementation for view objects. 
     * 
     * @note implemented as decorator/mixin instead of 'interface'
     * @tparam view_t template template parameter
     * @tparam Ts arbitrary number of tparams for view_t
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct decorator_t : view_t<Ts...>
    {
        using view_type = view_t<Ts...>;
        using array_type = typename view_type::array_type;

        /**
         * @todo
         *  - static assert if view_type array exists
         *  - has index member function that transform indices
         */

        /**
         * @brief return the dimensionality of the referred array
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const noexcept
        {
            // @note `this` must be constexpr when constexpr return value is desired
            if constexpr (meta::has_dim_v<meta::remove_cvref_t<view_type>>)
                return view_type::dim();
            // @note may be recursive
            else
                return detail::dim(view_type::array);
        } // dim()

        /**
         * @brief return the shape of this array
         * 
         * @return constexpr auto 
         * @see nmtools::shape
         */
        constexpr decltype(auto) shape() const noexcept
        {
            if constexpr (meta::has_shape_v<view_type>) {
                return view_type::shape();
            }
            else {
                return detail::shape(view_type::array);
            }
        } // shape

        /**
         * @brief Return the number of elements
         * 
         * @return constexpr auto 
         */
        constexpr auto size() const noexcept
        {
            if constexpr (meta::has_size_v<view_type>) {
                return view_type::size();
            } else {
                return index::product(shape());
            }
        }

        /**
         * @brief immutable element acces to the referenced array
         * 
         * @tparam size_types size type(s) to array
         * @param indices 
         * @return constexpr auto
         * @todo make error handling configurable, e.g. throw/assert/optional
         * @note for fixed size, it is necessary to pass Array{} (value initialization) to dim since `this` may not be constant expression
         * @see https://en.cppreference.com/w/cpp/language/value_initialization
         * @see nmtools::at
         */
        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices) const
        {
            // @note either using auto& or decltype(auto) for return type
            // since at(...) return auto&

            // error: pack expansion used as argument for non-pack parameter of alias template :|
            // using common_t = meta::promote_index_t<size_types...>;
            using common_t = meta::type_t<meta::promote_index<size_types...>>;
            using meta::has_funcnd_v;
            if constexpr (has_funcnd_v<view_type,size_types...>)
                return view_type::operator()(indices...);
            else {
                auto transformed_indices = view_type::index(indices...);

                // only perform assert if integral type is passed
                // otherwise assume indices is packed and pass to apply_at
                // to allow access from packed indices
                // TODO: better error handling
                if constexpr (meta::is_integral_v<common_t>) {
                    constexpr auto n = sizeof...(size_types);
                    // TODO: static_assert whenever possible
                    nmtools_cassert ( (common_t)dim()==(common_t)n
                        , "mismatched dimension"
                    ); // tmp assertion
                }

                // call at to referred object, not to this.
                // the array_type from the view may be pointer
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_at(*view_type::array, transformed_indices);
                } else {
                    return apply_at(view_type::array, transformed_indices);
                }
            }
        } // operator()

        /**
         * @brief mutable element acces to the referenced array
         * 
         * @tparam size_types size type(s) to array
         * @param indices 
         * @return constexpr auto
         * @todo make error handling configurable, e.g. throw/assert/optional
         * @note for fixed size, it is necessary to pass Array{} (value initialization) to dim since `this` may not be constant expression
         * @see https://en.cppreference.com/w/cpp/language/value_initialization
         * @see nmtools::at
         */
        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices)
        {
            // @note either using auto& or decltype(auto) for return type
            // since at(...) return auto&

            // error: pack expansion used as argument for non-pack parameter of alias template :|
            // using common_t = meta::promote_index_t<size_types...>;
            using common_t = meta::type_t<meta::promote_index<size_types...>>;
            using meta::has_funcnd_v;
            if constexpr (has_funcnd_v<view_type,size_types...>)
                return view_type::operator()(indices...);
            else {
                auto transformed_indices = view_type::index(indices...);

                [[maybe_unused]] constexpr auto n = sizeof...(size_types);
                // only perform assert if integral type is passed
                // otherwise assume indices is packed and pass to apply_at
                // to allow access from packed indices
                if constexpr (meta::is_integral_v<common_t>)
                    // @todo static_assert whenever possible
                    assert (dim()==n); // tmp assertion

                // @note needs to initialize array_t since view_type::array may not be constant expression
                // @note flatten_t dim invocation differs from other view types @todo fix
                // if constexpr (meta::is_fixed_size_ndarray_v<array_t>)
                //     static_assert (detail::dim(array_t{})==n);
                // else
                //     assert (dim()==n);

                // call at to referred object, not to this
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_at(*view_type::array, transformed_indices);
                } else {
                    return apply_at(view_type::array, transformed_indices);
                }
            }
        } // operator()

        /**
         * @brief Perform assignment if supported by the underlying view
         * 
         * @tparam other_t 
         * @param other 
         * @return constexpr auto 
         */
        template <typename other_t, meta::enable_if_t< meta::is_assignable_v<view_type,other_t>, int> =0 >
        constexpr auto operator=(const other_t& other)
        {
            static_cast<view_type>(*this) = other;
            return *this;
        } // operator=

    }; // decorator_t

    // TODO: remove
    /**
     * @brief make view given parameters arrays
     * 
     * @tparam view_t template template parameter
     * @tparam Ts tparams for view_t, should be deducible from template argument deduction
     * @param arrays array to be viewed
     * @return constexpr auto 
     */
    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto make_view(Ts&&...arrays)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        // @note requires nested brace so that view_t that takes
        // multiple value at instantiation can be instantiated
        return decorator_t<view_t,Ts...>{{arrays...}};
    } // make_view

    /**
     * @brief helper trait to check if type T is view
     * 
     * @tparam T type to check
     * @tparam typename sfinae/customization point
     */
    template <typename T, typename=void>
    struct is_view : meta::false_type {};

    /**
     * @brief true case for helper trait to check if type T is view
     * 
     * @tparam view_t template template param corresponding to actual view
     * @tparam Ts template parameters to actual view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_view<decorator_t<view_t,Ts...>> : meta::true_type {};

    /**
     * @brief helper variable template to check if type T is view
     * 
     * @tparam T type to check
     */
    template <typename T>
    static inline constexpr bool is_view_v = is_view<T>::value;

    namespace error
    {
        template <typename...>
        struct GET_ARRAY_TYPE_UNSUPPORTED : meta::detail::fail_t {};
    }

    // TODO: consider to move to meta, to allow decrete_t to access/specialize
    /**
     * @brief get array_type
     * 
     * @tparam T type to transform
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct get_array_type
    {
        // more generic implementation to allow decorator_t and discrete_t
        static constexpr auto vtype = [](){
            if constexpr (meta::has_array_type_v<T>) {
                using type = typename T::array_type;
                return meta::as_value_v<type>;
            } else {
                using type = error::GET_ARRAY_TYPE_UNSUPPORTED<T>;
                return meta::as_value_v<type>;
            }
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // get_array_type

    /**
     * @brief helper alias template for get_array_type
     * 
     * @tparam T type to transform
     * @see get_array_type
     */
    template <typename T>
    using get_array_type_t = typename get_array_type<T>::type;

    // TODO: consider to move to meta, to allow decrete_t to access/specialize
    /**
     * @brief get array_type of possibly nested view
     *
     * For non view type, default implementations define `type` as `void`.
     * The caller site may check if the returned type is void to perform
     * specific handling/assert.
     * 
     * @tparam T type to transform
     * @tparam typename customization point, e.g. using enable_if_t or void_t
     */
    template <typename T, typename=void>
    struct get_underlying_array_type
    {
        // TODO: use error type
        using type = void;
    }; // get_underlying_array_type

    /**
     * @brief helper alias template for get_underlying_array_type
     * 
     * @tparam T type to transform
     * @see get_underlying_array_type
     */
    template <typename T>
    using get_underlying_array_type_t = typename get_underlying_array_type<T>::type;

    /**
     * @brief specialization of get_underlying_array_type for view type.
     * 
     * @tparam view_t 
     * @tparam Ts 
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_underlying_array_type<decorator_t<view_t,Ts...>>
    {
        static constexpr auto vtype = [](){
            using view_type = decorator_t<view_t,Ts...>;
            using array_type = get_array_type_t<view_type>;
            using nocv_array_t = meta::remove_cvref_pointer_t<array_type>;
            // there some possibility of array_type trait/concept:
            // - the array is view (which also ndarray)
            // - the array is list of array (array type of binary ufuncs, for example)
            // - the array is actual concrete array (ndarray but not view)
            if constexpr (meta::is_tuple_v<nocv_array_t>) {
                // for each element in array_type,
                // recursively call get_underlying_array_type
                constexpr auto N = meta::len_v<nocv_array_t>;
                constexpr auto vtype = meta::template_reduce<N>([](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    using type_i  = meta::type_t<decltype(init)>;
                    using array_i = meta::at_t<array_type,i>;
                    // array_i may be cvref or even a pointer
                    using nocv_array_i = meta::remove_cvref_pointer_t<array_i>;
                    constexpr auto array_vtype = [](){
                        if constexpr (is_view_v<nocv_array_i>) {
                            using type = get_underlying_array_type_t<nocv_array_i>;
                            return meta::as_value_v<type>;
                        } else {
                            return meta::as_value_v<array_i>;
                        }
                    }();
                    using array_t = meta::type_t<decltype(array_vtype)>;
                    // at this point array_t (which may be the result of recursively calling get_underlying_array_type)
                    // may be tuple may be array may be num. must call meta::concat if it is tuple, meta::append otherwise.

                    if constexpr (is_none_v<type_i> && !meta::is_tuple_v<array_t>) {
                        // init typelist, use tuple for now,
                        // TODO: deduce template template of nocv_array_t if possible
                        using type = meta::make_tuple_type_t<array_t>;
                        return meta::as_value_v<type>;
                    } else if constexpr (is_none_v<type_i> && meta::is_tuple_v<array_t>) {
                        return meta::as_value_v<array_t>;
                    } else if constexpr (meta::is_tuple_v<array_t>) {
                        // assume type_i is tuple-like type-list
                        // need to concatenate if array_t is also a tuple/type-list
                        using type = meta::concat_type_t<type_i,array_t>;
                        return meta::as_value_v<type>;
                    } else /* if constexpr (meta::is_ndarray_v<array_t> || meta::is_num_v<array_t>) */ {
                        using type = meta::append_type_t<type_i,array_t>;
                        return meta::as_value_v<type>;
                    }
                }, /*init=*/meta::as_value_v<none_t>);
                return vtype;
            } else if constexpr (is_view_v<nocv_array_t>) {
                using type = get_underlying_array_type_t<nocv_array_t>;
                return meta::as_value_v<type>;
            } else {
                // try to check if the type has array_type (for discrete_t)
                using m_array_type = get_array_type_t<nocv_array_t>;
                if constexpr (!meta::is_fail_v<m_array_type>) {
                    using type = get_underlying_array_type_t<typename nocv_array_t::array_type>;
                    return meta::as_value_v<type>;
                } else /* if constexpr (meta::is_ndarray_v<nocv_array_t>) */ {
                    // assume concrete array already
                    return meta::as_value_v<array_type>;
                }
            }
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // get_underlying_array_type

    // TODO: complete, with noptr, noval, asref, asptr, asval
    template <typename array_t>
    struct noref_t
    {
        const array_t* array;
    }; // noref_t

    template <typename array_t>
    struct is_noref : meta::false_type {};

    template <typename array_t>
    struct is_noref<noref_t<array_t>> : meta::true_type {};

    template <typename array_t>
    inline constexpr auto is_noref_v = is_noref<array_t>::value;

    template <typename array_t>
    constexpr auto noref(const array_t& array)
    {
        return noref_t{&array};
    } // noref

    /**
     * @brief Metafunction to resolve array type for view type constructor.
     * 
     * Return const value type if array_t is a view or a simple number.
     * For bounded array type, return const reference.
     * Otherwise return const pointer to array_t.
     * 
     * Note: for bounded array type, using const reference
     * makes it can't be returned from a function (not copyable and not moveable).
     * TODO: find out how to properly take const pointer to bounded array.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct resolve_array_type
    {
        static constexpr auto vtype = [](){
            if constexpr (is_view_v<array_t>
                || meta::is_num_v<array_t>
                || is_none_v<array_t>
                || meta::is_constant_index_array_v<array_t>
                || meta::is_constant_index_v<array_t>
            ) {
                return meta::as_value_v<const array_t>;
            } else if constexpr (meta::is_bounded_array_v<array_t>) {
                return meta::as_value_v<const array_t&>;
            } else {
                return meta::as_value_v<const array_t*>;
            }
            // TODO: use fail type for unsupported type
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // resolve_array_type

    // TODO: use meta::remove_const
    template <typename array_t>
    struct resolve_mutable_array_type
    {
        static constexpr auto vtype = [](){
            if constexpr (is_view_v<array_t>
                || meta::is_num_v<array_t>
                || is_none_v<array_t>
                || meta::is_constant_index_array_v<array_t>
                || meta::is_constant_index_v<array_t>
            ) {
                return meta::as_value_v<array_t>;
            } else if constexpr (meta::is_bounded_array_v<array_t>) {
                return meta::as_value_v<array_t&>;
            } else {
                return meta::as_value_v<array_t*>;
            }
            // TODO: use fail type for unsupported type
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // resolve_array_type

    template <typename array_t>
    struct resolve_array_type<noref_t<array_t>>
    {
        using type = const array_t;
    }; // resolve_array_type

    template <typename array_t>
    struct resolve_array_type<const array_t> : resolve_array_type<array_t> {};

    template <typename array_t>
    struct resolve_array_type<const array_t&> : resolve_array_type<array_t> {};

    template <typename array_t>
    struct resolve_array_type<const array_t*> : resolve_array_type<array_t> {};

    template <typename array_t>
    using resolve_array_type_t = meta::type_t<resolve_array_type<array_t>>;

    template <typename array_t>
    using resolve_mutable_array_type_t = meta::type_t<resolve_mutable_array_type<array_t>>;

    /**
     * @brief Helper function to initialize array for view constructor.
     * 
     * Simply detect if should return pointer or not.
     * 
     * @tparam array_type 
     * @tparam array_t 
     * @param array 
     * @return constexpr array_type 
     */
    template <typename array_type, typename array_t>
    constexpr array_type initialize(const array_t& array)
    {
        if constexpr (meta::is_pointer_v<array_type> && !meta::is_pointer_v<array_t>) {
            return &array;
        } else {
            return array;
        }
    } // initialize

    template <typename array_type, typename array_t>
    constexpr array_type initialize(array_t& array)
    {
        if constexpr (meta::is_pointer_v<array_type>) {
            return &array;
        } else {
            return array;
        }
    } // initialize

    template <typename array_t, typename array_type>
    constexpr array_type initialize(const array_t& array, meta::as_value<array_type>)
    {
        return initialize<array_type>(array);
    } // initialize

    template <typename operands_type, typename...arrays_t>
    constexpr auto initialize_operands(const arrays_t&...arrays)
    {
        if constexpr (sizeof...(arrays) > 1) {
            // take the original referenced array as const ref,
            // may be transformed to pointer later
            using tuple_t = nmtools_tuple<const arrays_t&...>;
            auto tuple = tuple_t{arrays...};
            // the following may transform to tuple of pointer / tuple of value
            return meta::template_reduce<sizeof...(arrays)>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using arg_t  = meta::at_t<operands_type,i>;
                using init_t = meta::remove_cvref_t<decltype(init)>;
                // for each element in operands,
                // dispatch based on take ref or not
                auto arg = [&]() -> arg_t {
                    if constexpr (meta::is_pointer_v<arg_t>) {
                        return &nmtools::get<i>(tuple);
                    } else {
                        return nmtools::get<i>(tuple);
                    }
                }();
                if constexpr (is_none_v<init_t>) {
                    using tuple = nmtools_tuple<arg_t>;
                    return tuple{arg};
                } else {
                    using tuple = nmtools_tuple<arg_t>;
                    return detail::tuple_cat(init,tuple{arg});
                }
            }, None);
        } else {
            using array_t = meta::at_t<operands_type,0>;
            if constexpr (meta::is_pointer_v<array_t>) {
                return operands_type{&arrays...};
            } else {
                return operands_type{arrays...};
            }
        }
    } // initialize_operands

    namespace error
    {
        // error type for resolve_attribute_type metafunction
        template <typename...>
        struct RESOLVE_ATTRIBUTE_TYPE_UNSUPPORTED : meta::detail::fail_t {};
    }

    /**
     * @brief Metafunction to infer attribute type, prefer value semantics.
     * 
     * @tparam attribute_t 
     */
    template <typename attribute_t>
    struct resolve_attribute_type
    {
        static constexpr auto vtype = [](){
            if constexpr (meta::is_bounded_array_v<attribute_t>) {
                // convert to array type that has value semantics
                constexpr auto N = meta::len_v<attribute_t>;
                using elem_t = meta::get_element_type_t<attribute_t>;
                using type = meta::make_array_type_t<elem_t,N>;
                return meta::as_value_v<const type>;
            } else /* if constexpr (
                   is_none_v<attribute_t>
                || is_dtype_v<attribute_t>
                || meta::is_slice_index_v<attribute_t>
                || meta::is_slice_index_array_v<attribute_t>
                || meta::is_num_v<attribute_t>
                || meta::is_index_array_v<attribute_t>
                || meta::is_integral_constant_v<attribute_t>
                || meta::is_ndarray_v<attribute_t>) */
            {
                // NOTE: simply return as value for presumably copyable type
                // as quick workaround to allow arbitrary type for passing via functor's operator[]
                return meta::as_value_v<const attribute_t>;
            }
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // resolve_attribute_type

    template <typename attribute_t>
    using resolve_attribute_type_t = meta::type_t<resolve_attribute_type<attribute_t>>;

    /**
     * @brief Specialize index::ref
     * 
     * Recurse to referenced array.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct resolve_attribute_type<::nmtools::index::ref<array_t>>
    {
        using type = resolve_attribute_type_t<array_t>;
    }; // resolve_attribute_type

    /**
     * @brief Initialize attribute
     * 
     * @tparam attribute_type   attribute type from resolve_attribute type metafunction
     * @tparam attribute_t      original attribute type (without const ref)
     * @param attribute 
     * @return constexpr auto 
     */
    template <typename attribute_type, typename attribute_t>
    constexpr auto init_attribute(const attribute_t& attribute)
    {
        if constexpr (meta::is_constant_index_array_v<attribute_t>) {
            return static_cast<attribute_type>(attribute);
        } else if constexpr (meta::is_fixed_index_array_v<attribute_t>) {
            using attr_t = meta::remove_cvref_t<attribute_type>;
            auto attr = attr_t{};
            constexpr auto N = meta::len_v<attr_t>;
            meta::template_for<N>([&](auto index){
                at(attr,index) = at(attribute,index);
            });
            return attr;
        } else if constexpr (meta::is_index_array_v<attribute_t>) {
            using attr_t = meta::remove_cvref_t<attribute_type>;
            auto attr = attr_t{};
            if constexpr (meta::is_resizable_v<attr_t>) {
                attr.resize(len(attribute));
            }
            for (size_t i=0; i<(size_t)len(attribute); i++) {
                at(attr,i) = at(attribute,i);
            }
            return attr;
        } else /* if constexpr (meta::is_index_v<attribute_t>) */ {
            return static_cast<attribute_type>(attribute);
        }
    } // init attribute

    template <typename attribute_t, typename attribute_type>
    constexpr auto init_attribute(const attribute_t& attribute, meta::as_value<attribute_type>)
    {
        return init_attribute<attribute_type>(attribute);
    } // init_attribute

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools::meta
{
    // make is_view available from namespace meta
    using view::is_view;
    using view::is_view_v;

    // make get_array_type available from namespace meta
    using view::get_array_type;
    using view::get_array_type_t;

    // make get_underlying_array_type available from namespace meta
    using view::get_underlying_array_type;
    using view::get_underlying_array_type_t;

    // TODO: remove
    /**
     * @brief specialization of is_array1d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @note for specific view that may requires to specialize this, it is possible to do so by specialize "view_t" for the desired view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array1d<view::decorator_t<view_t,Ts...>,void>
        : is_array1d<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
} // namespace nmtools::meta

namespace nmtools
{

    template <template<typename...> typename view_t, typename...Ts>
    struct meta::fixed_ndarray_shape<view::decorator_t<view_t,Ts...>>
    {
        /**
         * @brief helper function to deduce the value of the ndarray
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::is_fixed_size_ndarray_v<view_t<Ts...>>)
                return meta::fixed_ndarray_shape_v<view_t<Ts...>>;
            else return detail::fail_t{};
        } // _get()
    
        static inline constexpr auto value = _get();
        // @note that remove_cvref_t here is necessary since decltype(value) may be const
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // meta::fixed_ndarray_shape

} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @brief specialization of metafunction get_ndarray_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @todo remove
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_ndarray_value_type<view::decorator_t<view_t,Ts...>>
        : get_ndarray_value_type<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of metafunction get_element_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_element_type<view::decorator_t<view_t,Ts...>>
        : get_element_type<meta::remove_cvref_pointer_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};

    template <template<typename...>typename view_t, typename...Args>
    struct fixed_shape<
        view::decorator_t<view_t,Args...>
    >
    {
        using view_type  = view::decorator_t<view_t,Args...>;

        static constexpr auto value = [](){
            using error_type [[maybe_unused]] = error::FIXED_SHAPE_UNSUPPORTED<view::decorator_t<view_t,Args...>>;
            if constexpr (is_ndarray_v<view_type> && has_shape_v<view_type>) {
                using shape_type = decltype(declval<view_type>().shape());
                if constexpr (is_constant_index_array_v<shape_type>) {
                    return shape_type {};
                } else {
                    return error_type {};
                }
            } else {
                return error_type {};
            }
        }();
    }; // fixed_shape

    template <template<typename...>typename view_t, typename...Args>
    struct fixed_dim<
        view::decorator_t<view_t,Args...>
    >
    {
        using view_type  = view::decorator_t<view_t,Args...>;

        static constexpr auto value = [](){
            using error_type [[maybe_unused]] = error::FIXED_DIM_UNSUPPORTED<view::decorator_t<view_t,Args...>>;
            if constexpr (is_ndarray_v<view_type> && has_shape_v<view_type>) {
                using shape_type = decltype(declval<view_type>().shape());
                if constexpr (is_fixed_index_array_v<shape_type>) {
                    return len_v<shape_type>;
                } else {
                    return error_type {};
                }
            } else {
                return error_type {};
            }
        }();
    }; // fixed_dim

    template <template<typename...>typename view_t, typename...Args>
    struct fixed_size<
        view::decorator_t<view_t,Args...>
    >
    {
        // the underlying array type (not from decorator)
        using u_view_type = view_t<Args...>;
        using view_type   = view::decorator_t<view_t,Args...>;
        using array_type  = remove_cvref_pointer_t<typename view_type::array_type>;

        static constexpr auto value = [](){
            [[maybe_unused]] constexpr auto array_size = [](){
                if constexpr (is_tuple_v<array_type>) {
                    // simply use sum, should be overriden from the underlying view type
                    return template_reduce<len_v<array_type>>([](auto init, auto index){
                        using array_t = at_t<array_type, decltype(index)::value>;
                        auto fixed_size = fixed_size_v<remove_cvref_pointer_t<array_t>>;
                        if constexpr (is_fail_v<decltype(fixed_size)> || is_fail_v<decltype(init)>) {
                            return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
                        } else {
                            return init + fixed_size;
                        }
                    }, /*init=*/0);
                } else {
                    return fixed_size_v<array_type>;
                }
            }();
            if constexpr (is_ndarray_v<view_type> && has_size_v<u_view_type>) {
                using size_type = decltype(declval<view_type>().size());
                if constexpr (is_constant_index_v<size_type>) {
                    return size_type::value;
                } else {
                    return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
                }
            } else if constexpr (is_ndarray_v<view_type> && has_shape_v<u_view_type>) {
                using shape_type = decltype(declval<view_type>().shape());
                if constexpr (is_constant_index_array_v<shape_type>) {
                    auto product = index::product(shape_type{});
                    return product;
                } else {
                    return array_size;
                }
            } else if constexpr (is_ndarray_v<view_type>) {
                return array_size;
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <template<typename...>typename view_t, typename...Args>
    struct bounded_dim<
        view::decorator_t<view_t,Args...>
    >
    {
        using view_type  = view::decorator_t<view_t,Args...>;
        using array_type = remove_cvref_pointer_t<typename view_type::array_type>;

        static constexpr auto value = [](){
            [[maybe_unused]] auto array_bounded_dim = bounded_dim_v<array_type>;
            if constexpr (is_ndarray_v<view_type> && has_shape_v<view_type>) {
                using shape_type = decltype(declval<view_type>().shape());
                return bounded_size_v<shape_type>;
            } else if constexpr (is_ndarray_v<view_type>) {
                return array_bounded_dim;
            } else {
                return error::BOUNDED_DIM_UNSUPPORTED<view_type>{};
            }
        }();
    }; // bounded_dim

    template <template<typename...>typename view_t, typename...Args>
    struct bounded_size<
        view::decorator_t<view_t,Args...>
    >
    {
        using view_type  = view::decorator_t<view_t,Args...>;
        using array_type = remove_cvref_pointer_t<typename view_type::array_type>;

        static constexpr auto value = [](){
            [[maybe_unused]] constexpr auto array_bounded_size = [](){
                if constexpr (is_tuple_v<array_type>) {
                    // simply use sum, should be overriden from the underlying view type
                    return template_reduce<len_v<array_type>>([](auto init, auto index){
                        using array_t = at_t<array_type, decltype(index)::value>;
                        auto bounded_size = bounded_size_v<remove_cvref_pointer_t<array_t>>;
                        if constexpr (is_fail_v<decltype(bounded_size)> || is_fail_v<decltype(init)>) {
                            return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
                        } else {
                            return init + bounded_size;
                        }
                    }, /*init=*/0);
                } else {
                    return bounded_size_v<array_type>;
                }
            }();
            constexpr auto fixed_size = fixed_size_v<view_type>;
            if constexpr (!is_fail_v<decltype(fixed_size)>) {
                return fixed_size;
            } else if constexpr (is_ndarray_v<view_type> && has_shape_v<view_type>) {
                using shape_type = decltype(declval<view_type>().shape());
                if constexpr (is_constant_index_array_v<shape_type>) {
                    return index::product(shape_type{});
                } else {
                    return array_bounded_size;
                }
            } else if constexpr (is_ndarray_v<view_type>) {
                return array_bounded_size;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // bounded_size
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_DECORATOR_HPP