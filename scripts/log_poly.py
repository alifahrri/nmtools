import math

class FastLogLibrary:
    def __init__(self):
        self.LN2 = 0.6931471805599453
        
        # Minimax coefficients for the odd polynomial of ln((1+z)/(1-z))
        # We factor out 'z' just like we did with sine: 2 * z * (1 + c1*z^2 + c2*z^4...)
        self.coeffs = [
            1.0,                    # c0 (multiplied by 2z later)
            0.3333333333333333,     # c1 (~ 1/3)
            0.2000000000000000,     # c2 (~ 1/5)
            0.1428571428571428,     # c3 (~ 1/7)
            0.1111111111111111      # c4 (~ 1/9)
        ]

    def _poly_eval_odd(self, z):
        """Evaluates the odd polynomial using t = z^2"""
        t = z * z
        
        # Horner's method on the squared terms
        res = self.coeffs[-1]
        for i in range(len(self.coeffs) - 2, 0, -1):
            res = res * t + self.coeffs[i]
            
        # Add the constant term and multiply by z at the end
        res = res * t + self.coeffs[0]
        return 2.0 * z * res

    def compute_ln(self, x):
        """Computes ln(x) using IEEE 754 bit extraction and polynomial approx."""
        if x <= 0.0:
            raise ValueError("Math domain error: ln(x) undefined for x <= 0")
        if x == float('inf'):
            return float('inf')

        # 1. Hardware Bit Extraction
        # math.frexp returns m in [0.5, 1.0) and e.
        m, e = math.frexp(x)
        
        # Standard math libraries usually shift this so m is in [1.0, 2.0)
        m = m * 2.0
        e = e - 1
        
        # 2. The substitution trick: z = (m - 1) / (m + 1)
        z = (m - 1.0) / (m + 1.0)
        
        # 3. Evaluate the odd polynomial for ln(m)
        ln_m = self._poly_eval_odd(z)
        
        # 4. Reconstruct: ln(x) = ln(m) + e * ln(2)
        return ln_m + (e * self.LN2)

# --- COMPARISON SCRIPT ---
if __name__ == "__main__":
    my_math = FastLogLibrary()
    
    test_points = [0.001, 0.5, 1.0, 2.718281828, 10.0, 1000000.0]

    print(f"{'Input x':<12} | {'Standard math.log':<20} | {'Our ln(x)':<20} | {'Abs Error':<12}")
    print("-" * 80)

    for x in test_points:
        std_val = math.log(x)
        my_val = my_math.compute_ln(x)
        error = abs(std_val - my_val)
        print(f"{x:<12} | {std_val:<20.15f} | {my_val:<20.15f} | {error:.2e}")
