import numpy as np
import math
from scipy.optimize import minimize_scalar

def cos_taylor(x, num_terms=10):
    """
    Computes cos(x) using a dynamically calculated Taylor series.
    """
    # 1. Basic Range Reduction
    # We must wrap x to be as close to 0 as possible.
    # This maps any x into the domain [-pi, pi]
    x = (x + math.pi) % (2.0 * math.pi) - math.pi
    
    # 2. Taylor Series Initialization
    result = 1.0
    current_term = 1.0
    x_squared = x * x
    
    # 3. Dynamic Loop
    for n in range(1, num_terms):
        # The denominator grows as (2n) * (2n - 1)
        # For n=1: 2 * 1 = 2
        # For n=2: 4 * 3 = 12
        # For n=3: 6 * 5 = 30
        denominator = (2 * n) * (2 * n - 1)
        
        # Multiply the previous term by -x^2 / denominator
        current_term = current_term * (-x_squared) / denominator
        
        # Add to the running total
        result += current_term
        
    return result

def sin_taylor(x, num_terms=10):
    """
    Computes sin(x) using a dynamically calculated Taylor series.
    """
    # 1. Range Reduction
    # Safely wrap any angle into the [-pi, pi] domain using Python's floor modulo
    x = (x + math.pi) % (2.0 * math.pi) - math.pi
    
    # 2. Taylor Series Initialization
    # Sine is an odd function, so we start the running total at x, not 1.0
    result = x
    current_term = x
    x_squared = x * x
    
    # 3. Dynamic Loop
    for n in range(1, num_terms):
        # The denominator grows as (2n) * (2n + 1)
        # For n=1: 2 * 3 = 6
        # For n=2: 4 * 5 = 20
        # For n=3: 6 * 7 = 42
        denominator = (2 * n) * ((2 * n) + 1)
        
        # Multiply the previous term by -x^2 / denominator
        current_term = current_term * (-x_squared) / denominator
        
        # Add to the running total
        result += current_term
        
    return result
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

        return self.coeffs

# --- TRIGONOMETRIC POLYS ---
class RemezCosine(RemezBase):
    def _target_func(self, t):
        # return np.cos(np.sqrt(np.abs(t)))
        return cos_taylor(np.sqrt(np.abs(t)))

    def estimate(self, x):
        return self._poly_eval(self.coeffs, x * x)

class RemezSine(RemezBase):
    def _target_func(self, t):
        t = np.abs(t)
        if t < 1e-15: return 1.0
        # return np.sin(np.sqrt(t)) / np.sqrt(t)
        return sin_taylor(math.sqrt(t)) / math.sqrt(t)

    def estimate(self, x):
        return x * self._poly_eval(self.coeffs, x * x)

# --- EXPONENTIAL POLY ---
class RemezExp2(RemezBase):
    def __init__(self, degree=5):
        super().__init__(degree)
        self.domain = [-0.5, 0.5]

    def _target_func(self, t):
        return 2.0 ** t

    def estimate(self, r):
        return self._poly_eval(self.coeffs, r)

# --- LOGARITHMIC POLY ---
class RemezLog(RemezBase):
    def __init__(self, degree=5):
        super().__init__(degree)
        # Mantissa is [1.0, 2.0]. Max z = (2-1)/(2+1) = 1/3.
        # Since t = z^2, our max t domain is (1/3)^2 = 1/9.
        self.domain = [0.0, 1.0 / 9.0]

    def _target_func(self, t):
        """
        Computes the target function using a pure Maclaurin series.
        f(t) = 1 + t/3 + t^2/5 + t^3/7 + ...
        """
        t = abs(t) # Ensure t is positive
        
        # We need a high-precision ground truth for Remez to calculate errors.
        # 25 terms is overkill for t <= 1/9, ensuring perfect float64 accuracy.
        num_terms = 25 
        
        series_sum = 1.0
        current_t_power = t
        
        # Loop generates: t/3, t^2/5, t^3/7...
        for i in range(1, num_terms):
            denominator = (2 * i) + 1
            series_sum += current_t_power / denominator
            current_t_power *= t
            
        return series_sum

    def estimate(self, z):
        # Reconstruct ln(m) = 2 * z * P(z^2)
        return 2.0 * z * self._poly_eval(self.coeffs, z * z)


# --- MAIN MATH LIBRARY ---
class FastMathLibrary:
    def __init__(self, remez_cos, remez_sin, remez_exp2, remez_log):
        self.cos_poly = remez_cos
        self.sin_poly = remez_sin
        self.exp2_poly = remez_exp2
        self.log_poly = remez_log
        
        # Precomputed mathematical constants
        self.PI_OVER_2 = np.pi / 2.0
        self.LOG2_E = 1.4426950408889634
        self.LN2 = 0.6931471805599453
        self.INV_LN2 = 1.4426950408889634
        self.INV_LN10 = 0.4342944819032518

    # --- TRIG FUNCTIONS ---
    def _reduce_range_trig(self, x):
        k = round(x / self.PI_OVER_2)
        r = x - k * self.PI_OVER_2 
        return int(k % 4), r

    def cos(self, x):
        k, r = self._reduce_range_trig(x)
        if k == 0:   return self.cos_poly.estimate(r)
        elif k == 1: return -self.sin_poly.estimate(r)
        elif k == 2: return -self.cos_poly.estimate(r)
        elif k == 3: return self.sin_poly.estimate(r)

    def sin(self, x):
        k, r = self._reduce_range_trig(x)
        if k == 0:   return self.sin_poly.estimate(r)
        elif k == 1: return self.cos_poly.estimate(r)
        elif k == 2: return -self.sin_poly.estimate(r)
        elif k == 3: return -self.cos_poly.estimate(r)

    # --- EXP FUNCTIONS ---
    def exp(self, x):
        y = x * self.LOG2_E
        k = round(y)
        r = y - k
        return math.ldexp(self.exp2_poly.estimate(r), int(k))
        
    def exp2(self, x):
        k = round(x)
        r = x - k
        return math.ldexp(self.exp2_poly.estimate(r), int(k))

    # --- LOG FUNCTIONS ---
    def _compute_base_ln(self, x):
        """Helper to compute ln(x) and the exponent, shared by all logs."""
        if x <= 0: raise ValueError("math domain error")
        
        # Hardware extraction: m in [0.5, 1.0)
        m, e = math.frexp(x)
        
        # Shift to [1.0, 2.0)
        m = m * 2.0
        e = e - 1
        
        # Substitution trick
        z = (m - 1.0) / (m + 1.0)
        ln_m = self.log_poly.estimate(z)
        
        return ln_m, e

    def log(self, x):
        """Natural logarithm (base e)"""
        ln_m, e = self._compute_base_ln(x)
        return ln_m + (e * self.LN2)

    def log2(self, x):
        """Binary logarithm (base 2)"""
        ln_m, e = self._compute_base_ln(x)
        return (ln_m * self.INV_LN2) + e
        
    def log10(self, x):
        """Common logarithm (base 10)"""
        # Uses the standard change of base formula on our natural log output
        return self.log(x) * self.INV_LN10


# --- ISOLATED TESTING BLOCKS ---
if __name__ == "__main__":
    print("Training polynomials (Degree 3)...")
    remez_cos = RemezCosine(degree=3); remez_cos.solve(iterations=5)
    remez_sin = RemezSine(degree=3); remez_sin.solve(iterations=5)
    remez_exp2 = RemezExp2(degree=3); remez_exp2.solve(iterations=5)
    remez_log = RemezLog(degree=3); remez_log.solve(iterations=5)

    print(f"{remez_cos.coeffs.tolist()=}")
    print(f"{remez_sin.coeffs.tolist()=}")
    print(f"{remez_exp2.coeffs.tolist()=}")
    print(f"{remez_log.coeffs.tolist()=}")

    print("Training polynomials (Degree 7)...")
    remez_cos = RemezCosine(degree=7); remez_cos.solve(iterations=5)
    remez_sin = RemezSine(degree=7); remez_sin.solve(iterations=5)
    remez_exp2 = RemezExp2(degree=7); remez_exp2.solve(iterations=5)
    remez_log = RemezLog(degree=7); remez_log.solve(iterations=5)

    print(f"{remez_cos.coeffs.tolist()=}")
    print(f"{remez_sin.coeffs.tolist()=}")
    print(f"{remez_exp2.coeffs.tolist()=}")
    print(f"{remez_log.coeffs.tolist()=}")

    print("Training polynomials (Degree 5)...")
    remez_cos = RemezCosine(degree=5); remez_cos.solve(iterations=5)
    remez_sin = RemezSine(degree=5); remez_sin.solve(iterations=5)
    remez_exp2 = RemezExp2(degree=5); remez_exp2.solve(iterations=5)
    remez_log = RemezLog(degree=5); remez_log.solve(iterations=5)

    print(f"{remez_cos.coeffs.tolist()=}")
    print(f"{remez_sin.coeffs.tolist()=}")
    print(f"{remez_exp2.coeffs.tolist()=}")
    print(f"{remez_log.coeffs.tolist()=}")

    my_math = FastMathLibrary(remez_cos, remez_sin, remez_exp2, remez_log)

    # --- 1. COSINE TESTS ---
    print("\n" + "="*70)
    print(" COSINE TEST: Quadrant Mapping & Huge Range Reduction")
    print("="*70)
    cos_points = [0.0, np.pi / 6, np.pi / 2, np.pi, 3 * np.pi / 2, 2 * np.pi, 10.5 * np.pi, -np.pi / 3]
    
    print(f"{'Input (rad)':<15} | {'math.cos':<20} | {'my_math.cos':<20} | {'Abs Error':<10}")
    print("-" * 70)
    for x in cos_points:
        std_val, my_val = math.cos(x), my_math.cos(x)
        print(f"{x:<15.6f} | {std_val:+.15f} | {my_val:+.15f} | {abs(std_val - my_val):.2e}")


    # --- 2. SINE TESTS ---
    print("\n" + "="*70)
    print(" SINE TEST: Exact Zeros & Extreme Wrapping")
    print("="*70)
    sin_points = [0.0, np.pi / 4, np.pi, -np.pi / 2, 5 * np.pi, 100.0 * np.pi, 1.234567]
    
    print(f"{'Input (rad)':<15} | {'math.sin':<20} | {'my_math.sin':<20} | {'Abs Error':<10}")
    print("-" * 70)
    for x in sin_points:
        std_val, my_val = math.sin(x), my_math.sin(x)
        print(f"{x:<15.6f} | {std_val:+.15f} | {my_val:+.15f} | {abs(std_val - my_val):.2e}")


    # --- 3. EXPONENTIAL (Base e) TESTS ---
    print("\n" + "="*70)
    print(" EXPONENTIAL (e^x) TEST: Base Conversion & Bit Shifting")
    print("="*70)
    exp_points = [0.0, 0.5, -0.5, 1.0, -2.5, 10.0, 50.0, -10.5]
    
    print(f"{'Input x':<15} | {'math.exp':<20} | {'my_math.exp':<20} | {'Abs Error':<10}")
    print("-" * 70)
    for x in exp_points:
        std_val, my_val = math.exp(x), my_math.exp(x)
        print(f"{x:<15.6f} | {std_val:<20.10g} | {my_val:<20.10g} | {abs(std_val - my_val):.2e}")


    # --- 4. EXPONENTIAL (Base 2) TESTS ---
    print("\n" + "="*70)
    print(" EXPONENTIAL (2^x) TEST: Direct Hardware-Style Exponentiation")
    print("="*70)
    exp2_points = [
        0.0,             # 2^0
        0.5,             # Square root of 2
        -0.5,            # 1 / sqrt(2)
        1.0,             # Exact integer math
        3.321928,        # Approximately 10
        10.0,            # Exact base-2 shift (should be exactly 1024)
        -4.25            # Combined negative integer shift and fraction
    ]
    
    print(f"{'Input x':<15} | {'math.exp2':<20} | {'my_math.exp2':<20} | {'Abs Error':<10}")
    print("-" * 70)
    for x in exp2_points:
        # Standard math doesn't have math.exp2, so we use 2.0 ** x 
        # (Though some numpy/math libraries map 2.0**x to the C exp2 function under the hood)
        std_val, my_val = 2.0 ** x, my_math.exp2(x)
        print(f"{x:<15.6f} | {std_val:<20.10g} | {my_val:<20.10g} | {abs(std_val - my_val):.2e}")

    # --- 1. NATURAL LOG (ln) TESTS ---
    print("\n" + "="*75)
    print(" NATURAL LOG (log) TEST: Hardware Extraction")
    print("="*75)
    # Using 1.0 (exact zero), math.e (exact one), small fractions, and huge numbers
    log_points = [0.001, 0.5, 1.0, math.e, 10.0, 100.0, 1024.0, 1000000.0]
    
    print(f"{'Input x':<12} | {'math.log':<22} | {'my_math.log':<22} | {'Abs Error':<10}")
    print("-" * 75)
    for x in log_points:
        std_val, my_val = math.log(x), my_math.log(x)
        print(f"{x:<12.6g} | {std_val:<22.15f} | {my_val:<22.15f} | {abs(std_val - my_val):.2e}")

    # --- 2. BASE-2 LOG (log2) TESTS ---
    print("\n" + "="*75)
    print(" BINARY LOG (log2) TEST: Exact Integer Powers")
    print("="*75)
    # log2 should be perfectly accurate for pure powers of 2 because of exponent math
    log2_points = [0.125, 0.5, 1.0, 2.0, 3.14159, 10.0, 1024.0, 65536.0]
    
    print(f"{'Input x':<12} | {'math.log2':<22} | {'my_math.log2':<22} | {'Abs Error':<10}")
    print("-" * 75)
    for x in log2_points:
        std_val, my_val = math.log2(x), my_math.log2(x)
        print(f"{x:<12.6g} | {std_val:<22.15f} | {my_val:<22.15f} | {abs(std_val - my_val):.2e}")

    # --- 3. BASE-10 LOG (log10) TESTS ---
    print("\n" + "="*75)
    print(" COMMON LOG (log10) TEST: Change of Base")
    print("="*75)
    log10_points = [0.01, 0.1, 1.0, 5.0, 10.0, 100.0, 1000.0, 12345.6]
    
    print(f"{'Input x':<12} | {'math.log10':<22} | {'my_math.log10':<22} | {'Abs Error':<10}")
    print("-" * 75)
    for x in log10_points:
        std_val, my_val = math.log10(x), my_math.log10(x)
        print(f"{x:<12.6g} | {std_val:<22.15f} | {my_val:<22.15f} | {abs(std_val - my_val):.2e}")
