import math

# --- 1. POLYNOMIAL HELPERS ---

def evaluate_polynomial(x, coeffs):
    """Evaluates P(x) using Horner's Method for stability."""
    n = len(coeffs) - 1
    result = coeffs[n]
    for i in range(n - 1, -1, -1):
        result = result * x + coeffs[i]
    return result

# --- 2. LINEAR SOLVER (Gaussian Elimination with Partial Pivoting) ---

def linear_solve(A, b):
    n = len(b)
    for i in range(n):
        # Search for maximum pivot
        max_el = abs(A[i][i])
        max_row = i
        for k in range(i + 1, n):
            if abs(A[k][i]) > max_el:
                max_el = abs(A[k][i])
                max_row = k

        # Swap maximum row with current row
        A[i], A[max_row] = A[max_row], A[i]
        b[i], b[max_row] = b[max_row], b[i]

        # Eliminate rows below
        for k in range(i + 1, n):
            c = -A[k][i] / A[i][i]
            for j in range(i, n):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]
            b[k] += c * b[i]

    # Back substitution
    x = [0 for i in range(n)]
    for i in range(n - 1, -1, -1):
        x[i] = b[i] / A[i][i]
        for k in range(i - 1, -1, -1):
            b[k] -= A[k][i] * x[i]
    return x

# --- 3. EXTREMA SEARCH (The Exchange) ---

def find_all_extrema(f_target, coeffs, a, b, n):
    def error_func(x):
        return f_target(x) - evaluate_polynomial(x, coeffs)

    samples = 1000
    dx = (b - a) / (samples - 1)
    
    extrema = [a] # Start with boundary
    
    for i in range(1, samples - 1):
        x_prev, x_curr, x_next = a+(i-1)*dx, a+i*dx, a+(i+1)*dx
        y_prev = abs(error_func(x_prev))
        y_curr = abs(error_func(x_curr))
        y_next = abs(error_func(x_next))
        
        # Local peak detection in absolute error
        if y_curr > y_prev and y_curr > y_next:
            # Hill climbing refinement
            curr_x = x_curr
            step = dx
            for _ in range(15):
                xl, xr = curr_x - step, curr_x + step
                if abs(error_func(xl)) > abs(error_func(curr_x)):
                    curr_x = xl
                elif abs(error_func(xr)) > abs(error_func(curr_x)):
                    curr_x = xr
                step *= 0.5
            extrema.append(curr_x)
            
    extrema.append(b) # End with boundary
    
    # Ensure we only keep the best n+2 points
    if len(extrema) > n + 2:
        extrema.sort(key=lambda x: abs(error_func(x)), reverse=True)
        extrema = sorted(extrema[:n+2])
    return extrema

# --- 4. CORE REMEZ LOGIC ---

def solve_remez_system(nodes, f_target, n):
    size = n + 2
    A = [[0.0] * size for _ in range(size)]
    B = [0.0] * size
    print(f"{A=}")
    print(f"{B=}")
    
    for i in range(size):
        x = nodes[i]
        for j in range(n + 1):
            A[i][j] = x**j
        A[i][n+1] = 1.0 if i % 2 == 0 else -1.0
        B[i] = f_target(x)
        
    sol = linear_solve(A, B)
    return sol[:n+1], sol[n+1]

def run_remez(f_target, a, b, degree, tol=1e-12):
    # Initial nodes using Chebyshev
    nodes = []
    for i in range(degree + 2):
        nodes.append(a + (b - a) * (0.5 - 0.5 * math.cos(math.pi * i / (degree + 1))))
    print(f"{a=},{b=},{degree=}")
    print(f"{nodes=}")
    
    for iteration in range(10):
        coeffs, E = solve_remez_system(nodes, f_target, degree)
        new_nodes = find_all_extrema(f_target, coeffs, a, b, degree)
        if iteration < 3:
            print(f"{coeffs=}")
            print(f"{nodes=}")
        
        diff = sum(abs(nodes[i] - new_nodes[i]) for i in range(len(nodes)))
        print(f"Iteration {iteration}: E = {abs(E):.2e}, Node Shift = {diff:.2e}")
        
        if diff < tol:
            break
        nodes = new_nodes
        
    return coeffs, abs(E)

# --- 5. MAIN ENTRY POINT ---

if __name__ == "__main__":
    # Example: Generating a 4th degree Minimax polynomial for cos(x)
    # Range [0, PI/4] is standard for sin/cos range reduction
    coeffs, max_err = run_remez(math.cos, 0, math.pi/4, degree=4)
    
    print("\n--- Optimized Coefficients ---")
    for i, c in enumerate(coeffs):
        print(f"C{i}: {c:.15f}")
    print(f"Max Absolute Error: {max_err:.2e}")