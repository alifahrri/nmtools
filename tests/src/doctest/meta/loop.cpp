#include "nmtools/meta/loop.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("template_reduce" * doctest::test_suite("meta"))
{
    constexpr auto args = std::tuple{0,1,2,3};
    auto f = [&](auto init, auto /*a*/, auto i){
        using init_t = decltype(init);
        constexpr auto I = decltype(i)::value;
        auto ai = std::get<I>(args);
        if constexpr (std::is_integral_v<init_t>)
            return std::tuple{init,ai};
        else
            return std::tuple_cat(init,std::tuple{ai});
    };
    [[maybe_unused]] auto res = meta::template_reduce(f,args);
}