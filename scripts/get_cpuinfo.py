from cpuinfo import get_cpu_info

# helper script to determine output directory to save benchmark results
# example usage: export NMTOOLS_TESTBENCH_OUTPUT_DIR=`python3 scripts/get_cpuinfo.py`
if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--root', '-r', help='root directory', default='bench_results')
    args = parser.parse_args()

    info = get_cpu_info()
    fmt  = dict(
        root=args.root,
        vendor=info['vendor_id_raw'],
        family=info['family'],
        model=info['model']
    )
    output_dir = "{root}/{vendor}-{family}-{model}".format_map(fmt)
    print(output_dir)
