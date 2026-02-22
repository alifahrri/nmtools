import numpy as np
import math
from scipy.optimize import minimize_scalar
import matplotlib.pyplot as plt

class RemezBase:
    """Base class handling the core Remez algorithm loop."""
    def __init__(self, degree=4):
        self.degree = degree
        self.domain = [0, (np.pi/4)**2]
        self.coeffs = None

    def _target_func(self, t):
        raise NotImplementedError("Must be implemented by subclass")

    def _poly_eval(self, coeffs, t):
        """Evaluates polynomial using Horner's Method"""
        res = coeffs[-1]
        for i in range(len(coeffs) - 2, -1, -1):
            res = res * t + coeffs[i]
        return res

    def _get_chebyshev_nodes(self, n):
        """Generates initial reference points (nodes)"""
        nodes = []
        for i in range(n):
            k = np.cos((2 * i + 1) * np.pi / (2 * n))
            mapped = 0.5 * (self.domain[0] + self.domain[1]) + \
                     0.5 * (self.domain[1] - self.domain[0]) * k
            nodes.append(mapped)
        return np.sort(nodes)

    def solve(self, iterations=10):
        N = self.degree
        nodes = self._get_chebyshev_nodes(N + 2)

        print(f"Starting Remez algorithm (Degree {N})...")
        
        for it in range(iterations):
            size = N + 2
            matrix = np.zeros((size, size))
            rhs = np.zeros(size)

            for i in range(size):
                t = nodes[i]
                for j in range(N + 1):
                    matrix[i, j] = t**j
                
                matrix[i, N + 1] = (-1)**i
                rhs[i] = self._target_func(t)

            try:
                solution = np.linalg.solve(matrix, rhs)
            except np.linalg.LinAlgError:
                print("Matrix singular. Stopping early.")
                break
                
            self.coeffs = solution[:-1]
            E = solution[-1]

            def neg_abs_error(t):
                return -np.abs(self._target_func(t) - self._poly_eval(self.coeffs, t))

            new_nodes = []
            search_intervals = [self.domain[0]] + list(nodes) + [self.domain[1]]
            search_intervals = sorted(list(set(search_intervals)))

            for i in range(len(search_intervals) - 1):
                res = minimize_scalar(
                    neg_abs_error, 
                    bounds=(search_intervals[i], search_intervals[i+1]), 
                    method='bounded'
                )
                new_nodes.append(res.x)

            new_nodes = sorted(new_nodes, key=lambda t: neg_abs_error(t))[:N+2]
            nodes = np.sort(new_nodes)
            
            print(f"  Iter {it+1}: Theoretical Max Error (E) = {abs(E):.2e}")

        print("Done.\n")
        return self.coeffs


class RemezCosine(RemezBase):
    def _target_func(self, t):
        """The function we want to approximate: cos(sqrt(t))"""
        return np.cos(np.sqrt(np.abs(t)))

    def estimate(self, x):
        """Computes cos(x) using the fitted polynomial."""
        t = x * x
        return self._poly_eval(self.coeffs, t)


class RemezSine(RemezBase):
    def _target_func(self, t):
        """The function we want to approximate: sin(sqrt(t)) / sqrt(t)"""
        t = np.abs(t)
        # Handle the divide-by-zero case. Limit as t -> 0 is 1.0
        if t < 1e-15:
            return 1.0
        return np.sin(np.sqrt(t)) / np.sqrt(t)

    def estimate(self, x):
        """Computes sin(x) using the fitted polynomial: x * P(x^2)."""
        t = x * x
        # Evaluate P(t) and multiply by the factored-out x
        return x * self._poly_eval(self.coeffs, t)


class FastMathLibrary:
    def __init__(self, remez_cos, remez_sin):
        self.cos_poly = remez_cos
        self.sin_poly = remez_sin
        self.PI_OVER_2 = np.pi / 2.0

    def _reduce_range(self, x):
        """Reduces x to a remainder r in [-pi/4, pi/4] and a quadrant k."""
        # Find nearest integer number of pi/2 segments
        k = round(x / self.PI_OVER_2)
        
        # Find the remainder. 
        # r will always be in the range [-pi/4, pi/4]
        r = x - k * self.PI_OVER_2 
        
        # We only need the modulo 4 of k to know our quadrant
        return int(k % 4), r

    def cos(self, x):
        k, r = self._reduce_range(x)
        
        # Map back based on quadrant
        if k == 0:
            return self.cos_poly.estimate(r)
        elif k == 1:
            return -self.sin_poly.estimate(r)
        elif k == 2:
            return -self.cos_poly.estimate(r)
        elif k == 3:
            return self.sin_poly.estimate(r)

    def sin(self, x):
        k, r = self._reduce_range(x)
        
        # Map back based on quadrant
        if k == 0:
            return self.sin_poly.estimate(r)
        elif k == 1:
            return self.cos_poly.estimate(r)
        elif k == 2:
            return -self.sin_poly.estimate(r)
        elif k == 3:
            return -self.cos_poly.estimate(r)

# --- Testing the Wrapper ---
if __name__ == "__main__":
    # 1. Train the polynomials (using Degree 5 like before)
    remez_cos = RemezCosine(degree=5)
    remez_cos.solve(iterations=5)
    
    remez_sin = RemezSine(degree=5)
    remez_sin.solve(iterations=5)

    print(f"{remez_cos.coeffs=}")
    print(f"{remez_sin.coeffs=}")

    # 2. Instantiate our "Standard Library"
    my_math = FastMathLibrary(remez_cos, remez_sin)

    # 3. Test on your extended range (up to pi, and even beyond)
    # Let's test all the way to 10 radians!
    test_points = np.linspace(0.0, 1.0, 9)
    
    print("\n--- Accuracy with Range Reduction ---")
    print(f"{'x (rad)':<10} | {'Type':<4} | {'Standard Math':<20} | {'FastMath Wrapper':<20} | {'Abs Error':<12}")
    print("-" * 75)

    for x in test_points:
        # Cosine Test
        std_cos = math.cos(x)
        my_cos = my_math.cos(x)
        err_cos = abs(std_cos - my_cos)
        print(f"{x:.6f}   | COS  | {std_cos:+.15f}     | {my_cos:+.15f}     | {err_cos:.2e}")
        
        # Sine Test
        std_sin = math.sin(x)
        my_sin = my_math.sin(x)
        err_sin = abs(std_sin - my_sin)
        print(f"{x:.6f}   | SIN  | {std_sin:+.15f}     | {my_sin:+.15f}     | {err_sin:.2e}")
        print("-" * 75)
    # print(f"{my_math.sin(0.785398)=}")