import struct
import math

class FastExp2:
    def __init__(self):
        # Pre-calculated coefficients for approximating 2^r on [-0.5, 0.5].
        # These are extremely close to the Taylor series of 2^x, but in a real 
        # library they would be fine-tuned by the Remez algorithm.
        self.coeffs = [
            1.0,                        # c0
            0.6931471805599453,         # c1: ln(2)
            0.2402265069591007,         # c2: ln(2)^2 / 2!
            0.05550410866482158,        # c3: ln(2)^3 / 3!
            0.009618129107628477,       # c4: ln(2)^4 / 4!
            0.0013333558146428443,      # c5: ln(2)^5 / 5!
            0.0001540353039338161       # c6: ln(2)^6 / 6!
        ]

    def _poly_eval(self, r):
        """Evaluates P(r) roughly equal to 2^r using Horner's method."""
        res = self.coeffs[-1]
        for i in range(len(self.coeffs) - 2, -1, -1):
            res = res * r + self.coeffs[i]
        return res

    def _bit_hack_2_to_k(self, k):
        """
        Computes 2^k instantly by directly writing the IEEE 754 Exponent bits.
        This completely bypasses standard arithmetic.
        """
        # IEEE 754 Double Precision: 1 sign bit, 11 exponent bits, 52 fraction bits
        # Exponent bias is 1023.
        
        # 1. Calculate the raw exponent integer
        biased_exp = k + 1023
        
        # 2. Shift it 52 bits to the left to align it perfectly in the exponent slot
        raw_bits = biased_exp << 52
        
        # 3. The Python version of a C union: 
        # Pack the integer as an 8-byte unsigned long long ('>Q')
        # Unpack those exact same 8 bytes as a double float ('>d')
        packed_bytes = struct.pack('>Q', raw_bits)
        float_val = struct.unpack('>d', packed_bytes)[0]
        
        return float_val

    def compute(self, x):
        """Computes 2^x"""
        # 1. Range Reduction
        k = round(x)
        r = x - k
        
        # Edge case protection: IEEE 754 standard floats cannot hold 
        # exponents larger than 1023 or smaller than -1022 cleanly.
        if k > 1023:
            return float('inf')
        if k < -1022:
            return 0.0

        # 2. Evaluate the polynomial for the tiny fractional part
        poly_val = self._poly_eval(r)
        
        # 3. Get the exact integer power using the bit hack
        two_to_k = self._bit_hack_2_to_k(k)
        
        # 4. Reconstruct: 2^x = 2^k * 2^r
        return two_to_k * poly_val

# --- COMPARISON SCRIPT ---
if __name__ == "__main__":
    fast_math = FastExp2()
    
    # Test a variety of inputs: integers, small fractions, and large values
    test_points = [0.0, 1.0, -1.0, 0.5, -0.4, 5.3, -7.8, 50.1234]

    print(f"{'Input x':<10} | {'Standard 2.0**x':<22} | {'Bit-Hack Approx':<22} | {'Abs Error':<12}")
    print("-" * 80)

    max_error = 0
    for x in test_points:
        # Standard hardware implementation
        std_val = 2.0 ** x 
        
        # Our software bit-hack implementation
        my_val = fast_math.compute(x)
        
        error = abs(std_val - my_val)
        max_error = max(max_error, error)
        
        print(f"{x:<10} | {std_val:<22.15e} | {my_val:<22.15e} | {error:.2e}")

    print("-" * 80)
    print(f"Maximum Observed Error: {max_error:.2e}")