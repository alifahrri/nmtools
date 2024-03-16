// LICENSE: GNU General Public License v3.0
// adapted from https://github.com/illuhad/syclinfo/blob/f644f1a25dfd94aa07f7c58f5f6171e5651a966d/syclinfo.cpp:
// - fix for some global_mem_cache_type
// - include in nmtools namespace
// - adapt namespace changes ::sycl instead of cl::sycl
// - no boost dependencies
// - inline for c++17

#ifndef NMTOOLS_ARRAY_EVAL_SYCL_INFO_HPP
#define NMTOOLS_ARRAY_EVAL_SYCL_INFO_HPP

#include <sycl/sycl.hpp>
#include <iostream>
#include <map>

namespace nmtools::array::sycl
{
    inline std::map<::sycl::info::device_type, std::string> device_type_representation {
    {::sycl::info::device_type::cpu, "CPU"},
    {::sycl::info::device_type::gpu, "GPU"},
    {::sycl::info::device_type::accelerator, "Accelerator"},
    {::sycl::info::device_type::custom, "Custom"},
    {::sycl::info::device_type::automatic, "Automatic"},
    {::sycl::info::device_type::host, "Host"},
    {::sycl::info::device_type::all, "All"}
    };

    inline std::map<::sycl::info::global_mem_cache_type, std::string> global_mem_cache_type_representation {
    {::sycl::info::global_mem_cache_type::none, "None"},
    {::sycl::info::global_mem_cache_type::read_only, "Read-only"},
    {::sycl::info::global_mem_cache_type::read_write, "Read-Write"}
    };


    inline std::map<::sycl::info::local_mem_type, std::string> local_mem_type_representation {
    {::sycl::info::local_mem_type::none, "None"},
    {::sycl::info::local_mem_type::local, "Local"},
    {::sycl::info::local_mem_type::global, "Global"}
    };

    inline std::map<::sycl::info::fp_config, std::string> fp_config_representation {
    { ::sycl::info::fp_config::denorm, "denorm"},
    { ::sycl::info::fp_config::inf_nan, "inf_nan"},
    { ::sycl::info::fp_config::round_to_nearest, "round_to_nearest"},
    { ::sycl::info::fp_config::round_to_zero, "round_to_zero"},
    { ::sycl::info::fp_config::round_to_inf, "round_to_inf"},
    { ::sycl::info::fp_config::fma, "fma"},
    { ::sycl::info::fp_config::correctly_rounded_divide_sqrt, "correctly_rounded_divide_sqrt"},
    { ::sycl::info::fp_config::soft_float, "soft_float" }
    };

    inline std::map<::sycl::info::execution_capability, std::string> exec_capability_representation{
    {::sycl::info::execution_capability::exec_kernel, "exec_kernel"},
    {::sycl::info::execution_capability::exec_native_kernel, "exec_native_kernel"}
    };


    inline std::map<::sycl::info::partition_property, std::string> 
                            partition_property_representation {
    {::sycl::info::partition_property::no_partition, "no_partition"},
    {::sycl::info::partition_property::partition_equally, "partition_equally"},
    {::sycl::info::partition_property::partition_by_counts, "partition_by_counts"},
    {::sycl::info::partition_property::partition_by_affinity_domain, "partition_by_affinity_domain"}
    };

    inline std::map<::sycl::info::partition_affinity_domain, std::string> 
                            partition_affinity_domain_representation {
    {::sycl::info::partition_affinity_domain::not_applicable, "not_applicable"},
    {::sycl::info::partition_affinity_domain::numa, "numa"},
    {::sycl::info::partition_affinity_domain::L4_cache, "L4_cache"},
    {::sycl::info::partition_affinity_domain::L3_cache, "L3_cache"},
    {::sycl::info::partition_affinity_domain::L2_cache, "L2_cache"},
    {::sycl::info::partition_affinity_domain::L1_cache, "L1_cache"},
    {::sycl::info::partition_affinity_domain::next_partitionable, "next_partitionable"}
    };
} // namespace nmtools::array::sycl

template<class T>
std::ostream& operator<<(std::ostream& lhs, const std::vector<T>& rhs)
{
  for(std::size_t i = 0; i < rhs.size(); ++i)
  {
    lhs << rhs[i];
    if (i != rhs.size()-1)
      lhs << ", ";
  }
  return lhs;
}

namespace std
{

    using nmtools::array::sycl::device_type_representation;
    using nmtools::array::sycl::local_mem_type_representation;
    using nmtools::array::sycl::local_mem_type_representation;
    using nmtools::array::sycl::fp_config_representation;
    using nmtools::array::sycl::exec_capability_representation;
    using nmtools::array::sycl::partition_property_representation;
    using nmtools::array::sycl::local_mem_type_representation;
    using nmtools::array::sycl::partition_affinity_domain_representation;
    using nmtools::array::sycl::global_mem_cache_type_representation;

    inline std::ostream& operator<<(std::ostream& lhs, const ::sycl::id<3>& idx)
    {
        lhs << idx[0] << " " << idx[1] << " " << idx[2];
        return lhs;
    }


    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::device_type dtype)
    {
        lhs << device_type_representation[dtype];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::range<1> range)
    {
        lhs << range[0];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::range<2> range)
    {
        lhs << range[0] << "," << range[1];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::range<3> range)
    {
        lhs << range[0] << ", " << range[1] << ", " << range[2];
        return lhs;
    }

    template <auto Dimension>
    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::nd_range<Dimension> range)
    {
        lhs << "global:" << range.get_global_range() << ","
            << "local:" << range.get_local_range() << ","
            << "group:" << range.get_group_range()
        ;
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::global_mem_cache_type cache_type)
    {
        lhs << global_mem_cache_type_representation[cache_type];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::local_mem_type local_type)
    {
        lhs << local_mem_type_representation[local_type];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::fp_config fpconfig)
    {
        lhs << fp_config_representation[fpconfig];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::execution_capability ecap)
    {
        lhs << exec_capability_representation[ecap];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::partition_property pprop)
    {
        lhs << partition_property_representation[pprop];
        return lhs;
    }

    inline std::ostream& operator<<(std::ostream& lhs, ::sycl::info::partition_affinity_domain domain)
    {
        lhs << partition_affinity_domain_representation[domain];
        return lhs;
    }
} // namespace std

#endif // NMTOOLS_ARRAY_EVAL_SYCL_INFO_HPP