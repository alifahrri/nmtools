#include "nmtools/utl/static_stack.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

TEST_CASE("static_stack(case1)" * doctest::test_suite("utl"))
{
    using stack_t = utl::static_stack<nm_size_t,5>;

    auto stack = stack_t {};

    CHECK( stack.empty() == true );
    
    stack.push(1);
    stack.push(2);
    stack.push(3);

    CHECK( stack.empty() == false );

    CHECK( stack.size() == 3 );

    CHECK( stack.top() == 3 );

    CHECK( stack.pop() == 3 );
    CHECK( stack.pop() == 2 );

    CHECK( stack.size() == 1 );

    stack.push(4);
    CHECK( stack.top() == 4 );
    CHECK( stack.size() == 2 );

    CHECK( stack.pop() == 4 );
    CHECK( stack.pop() == 1 );

    CHECK( stack.empty() == true );
}