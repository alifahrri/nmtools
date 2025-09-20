#ifndef NMTOOLS_UTL_HPP
#define NMTOOLS_UTL_HPP

// A dumb, minimalistic, templated, micro utility library;
// the following is not aimed to be full stl-compatible nor highly performant.
// The main objective is to cover some stl-like feature (array, tuple,...) in a way
// they are used in nmtools library.

#include "nmtools/utl/array.hpp"
#include "nmtools/utl/tuple.hpp"
#include "nmtools/utl/either.hpp"
#include "nmtools/utl/maybe.hpp"
#include "nmtools/utl/queue.hpp"
#include "nmtools/utl/stack.hpp"
#include "nmtools/utl/static_map.hpp"
#include "nmtools/utl/static_queue.hpp"
#include "nmtools/utl/static_stack.hpp"
#include "nmtools/utl/static_string.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/vector.hpp"

#ifndef nmtools_list
#define nmtools_list ::nmtools::utl::vector
#endif // nmtools_list

#ifndef nmtools_either
#define nmtools_either ::nmtools::utl::either
#endif // nmtools_either

#ifndef nmtools_tuple
#define nmtools_tuple ::nmtools::utl::tuple
#endif // nmtools_tuple

#ifndef nmtools_maybe
#define nmtools_maybe   ::nmtools::utl::maybe
#define nmtools_nothing ::nmtools::utl::nothing
#endif // nmtools_maybe

#ifndef nmtools_array
#define nmtools_array ::nmtools::utl::array
#endif // nmtools_array

#ifndef nmtools_queue
#define nmtools_queue ::nmtools::utl::queue
#endif // nmtools_queue

#ifndef nmtools_stack
#define nmtools_stack ::nmtools::utl::stack
#endif // nmtools_stack

#ifndef nmtools_static_vector
#define nmtools_static_vector ::nmtools::utl::static_vector
#endif // nmtools_static_vector

#ifndef nmtools_static_queue
#define nmtools_static_queue ::nmtools::utl::static_queue
#endif // nmtools_static_queue

#ifndef nmtools_static_stack
#define nmtools_static_stack ::nmtools::utl::static_stack
#endif // nmtools_static_stack

#endif // NMTOOLS_UTL_HPP