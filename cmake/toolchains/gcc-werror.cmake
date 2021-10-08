# some third party libary used for testing add clang pragmas
# need -Wno-error=bool-compare because on gcc 9.3, the following generates warnings hence may trigger error:
# struct fixed_dim< view::decorator_t<view::ufunc_t, op_t,arrays_t...> >
# {
#     static inline constexpr auto value = [](){
#         if constexpr ((is_fixed_dim_ndarray_v<arrays_t> && ...)) {
#             constexpr auto all_same_dim = (fixed_dim_v<arrays_t> == ...);
#             if constexpr (static_cast<bool>(all_same_dim)) {
#                  ...
#                 return ref_dim;
#             }
#             else return detail::Fail;
#         ...
# }; // fixed_dim
# with warning: comparison of constant ‘2’ with boolean expression is always false [-Wbool-compare]
# the code above works fine on clang 10.0
add_compile_options(-W -Wall -Werror -Wextra -Wno-error=unknown-pragmas -Wno-error=bool-compare)