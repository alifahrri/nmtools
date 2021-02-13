# Benchmarking
## Requirements
- [nanobench](https://nanobench.ankerl.com/index.html)
## Build Tests with Benchmarking Enabled
To enable testing benchmarks, pass `-DENABLE_TEST_BENCHMARKS=ON` when configuring cmake. When benchmarking it may be useful to build both `Debug` and `Release`, to do so using [cmany](https://pypi.org/project/cmany/), from project dir:
```
cmany b -t Debug,Release -c g++,clang++ -V ENABLE_TEST_BENCHMARKS=ON
```
This will build testing with benchmark enabled (for those tests that supports), for each compiler (gcc & clang) and for each compiler with both Debug and Release build type.
## Environment Variables
With benchmarks enabled, the tests now listen to the following environment variables:
- `NMTOOLS_TESTBENCH_QUIET` : Do not print to cout.
- `NMTOOLS_TESTBENCH_EPOCHS` : Controls number of epochs, the number of measurements to perform, expects integer.
- `NMTOOLS_TESTBENCH_WARMUP` : Sets a number of iterations that are initially performed without any measurements, expects integer.
- `NMTOOLS_TESTBENCH_OUTPUT_DIR` : Output directory.
- `NMTOOLS_TESTBENCH_OUTPUT_CSV` : Save results to csv format.
- `NMTOOLS_TESTBENCH_OUTPUT_JSON` : Save results to json format.
- `NMTOOLS_TESTBENCH_OUTPUT_BOXPLOT` : Save results to boxplot html format.
- `NMTOOLS_TESTBENCH_OUTPUT_ALL` : Enable all outputs format.

Specific test case/suite can still be selected via doctest's arguments, hence only run benchmarks for those case/suite only.

To determine output directory based on hardware, a scripts to read cpu information is provided. Then environment variable `NMTOOLS_TESTBENCH_OUTPUT_DIR` can be set based on those value. From project root:
```
export NMTOOLS_TESTBENCH_OUTPUT_DIR=`python3 scripts/get_cpuinfo.py`
```
example output:
```
» echo $NMTOOLS_TESTBENCH_OUTPUT_DIR
bench_results/GenuineIntel-6-158
```
where `GenuineIntel` is vendor ID, `6` is CPU Family, `158` is Model. More information about the numbers can be checked at [wikichip's intel cpuid](https://en.wikichip.org/wiki/intel/cpuid).

Note that the benchmarks do not create directory if nonexists.