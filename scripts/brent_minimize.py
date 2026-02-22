import math

def brent_minimize(func, bounds, tol=1e-5, max_iter=500):
    """
    Finds the local minimum of 'func' within 'bounds' using Brent's method.
    Mimics scipy.optimize.minimize_scalar(method='bounded').
    
    Args:
        func: The objective function f(x).
        bounds: A tuple (lower, upper).
        tol: Stop when interval size < tol.
        max_iter: Maximum iterations.
        
    Returns:
        The x value where the minimum occurs.
    """
    
    # 1. Initialization
    a, b = bounds
    # Golden section ratio: (3 - sqrt(5)) / 2
    golden_ratio = 0.3819660
    
    # x is the current best point
    # w is the second best
    # v is the previous w
    v = w = x = a + golden_ratio * (b - a)
    
    # fv, fw, fx are the function values at those points
    fx = func(x)
    fv = fw = fx
    
    d = 0.0 # Step size of the current iteration
    e = 0.0 # Step size of the previous iteration (for parabolic check)

    for _ in range(max_iter):
        mid = 0.5 * (a + b)
        tol1 = tol * abs(x) + 1e-10 # Absolute tolerance
        tol2 = 2.0 * tol1
        
        # 2. Check Convergence
        # If the interval [a,b] is roughly the size of the tolerance, we are done.
        if abs(x - mid) <= (tol2 - 0.5 * (b - a)):
            return x
        
        # 3. Decide: Parabolic Fit vs Golden Section
        para_step_attempted = False
        
        # We only try parabolic fit if 'e' (step before last) was big enough.
        # This prevents using parabolic fits when we are already taking tiny steps.
        if abs(e) > tol1:
            # Construct a parabola through (x, fx), (w, fw), (v, fv)
            # Formula for the minimum of a parabola defined by 3 points:
            r = (x - w) * (fx - fv)
            q = (x - v) * (fx - fw)
            p = (x - v) * q - (x - w) * r
            q = 2.0 * (q - r)
            
            if q > 0.0: 
                p = -p
            q = abs(q)
            
            etemp = e
            e = d
            
            # Check if the parabolic step 'p/q' is acceptable:
            # 1. Must land within [a, b]
            # 2. Must be smaller than half the step before last (etemp) to ensure convergence speed
            if abs(p) < abs(0.5 * q * etemp) and (p > q * (a - x)) and (p < q * (b - x)):
                d = p / q
                u = x + d
                
                # Don't evaluate too close to the edges a or b
                if (u - a) < tol2 or (b - u) < tol2:
                    d = tol1 if x < mid else -tol1
                    
                para_step_attempted = True

        # 4. Fallback: Golden Section Step
        if not para_step_attempted:
            if x >= mid:
                e = a - x
            else:
                e = b - x
            d = golden_ratio * e

        # 5. Evaluate Function at new point 'u'
        # Ensure we don't step closer than 'tol1' to 'x' (avoid numerical underflow)
        if abs(d) >= tol1:
            u = x + d
        else:
            u = x + (tol1 if d > 0 else -tol1)
            
        fu = func(u)

        # 6. Update Bracket [a, b] and Points (x, w, v)
        if fu <= fx:
            # u is the new best point!
            if u >= x:
                a = x  # Shrink the bracket from the left
            else:
                b = x  # Shrink the bracket from the right
            
            # Shift the roles: v -> w, w -> x, x -> u
            v, w, x = w, x, u
            fv, fw, fx = fw, fx, fu
            
        else:
            # u is worse than x, but it might be better than w or v
            # It allows us to shrink the bracket anyway
            if u < x:
                a = u
            else:
                b = u
                
            if fu <= fw or w == x:
                v = w
                w = u
                fv = fw
                fw = fu
            elif fu <= fv or v == x or v == w:
                v = u
                fv = fu
                
    return x

# --- USAGE EXAMPLE ---
if __name__ == "__main__":
    # Example function: f(x) = (x - 2)^2
    # Minimum should be at x = 2.0
    def my_func(x):
        return (x - 2.0)**2

    result = brent_minimize(my_func, bounds=(-5, 10))
    print(f"Minimum found at x = {result}")