import os
import timeit

# 1. MUST BE DONE BEFORE IMPORTING NUMPY OR TORCH
os.environ["OMP_NUM_THREADS"] = "1"
os.environ["OPENBLAS_NUM_THREADS"] = "1"
os.environ["MKL_NUM_THREADS"] = "1"
os.environ["VECLIB_MAXIMUM_THREADS"] = "1"
os.environ["NUMEXPR_NUM_THREADS"] = "1"

import numpy as np
import torch

# 2. Set PyTorch thread limit
torch.set_num_threads(1)

print(f"Verified PyTorch threads: {torch.get_num_threads()}")

# 3. Setup the data
size = 2048
iterations = 1000

print(f"Setting up {size}x{size} arrays...")
np_array = np.random.rand(size, size).astype(np.float32)
torch_cpu_tensor = torch.from_numpy(np_array)

axes_to_test = [None, 0, 1]

print(f"\nBenchmarking over {iterations} iterations (SINGLE THREADED)...\n")

for axis in axes_to_test:
    print(f"{"="*10} Benchmarking Axis: {axis} {"="*10}")
    
    # --- NumPy ---
    def run_numpy():
        return np.max(np_array, axis=axis)
        
    np_time = timeit.timeit(run_numpy, number=iterations)
    print(f"NumPy (np.max):          {(np_time / iterations) * 1000:.4f} ms")

    # --- PyTorch CPU ---
    def run_torch_cpu():
        if axis is None:
            return torch.max(torch_cpu_tensor)
        else:
            return torch.amax(torch_cpu_tensor, dim=axis)
            
    torch_cpu_time = timeit.timeit(run_torch_cpu, number=iterations)
    print(f"PyTorch CPU (torch.amax): {(torch_cpu_time / iterations) * 1000:.4f} ms")
    print()