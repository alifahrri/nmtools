import math

def linear_solve_pure_python(A, b):
    """
    Solves Ax = b using Gaussian Elimination with Partial Pivoting.
    """
    n = len(b)
    # Augmented matrix to track row operations
    for i in range(n):
        # 1. Partial Pivoting
        max_row = i
        for k in range(i + 1, n):
            if abs(A[k][i]) > abs(A[max_row][i]):
                max_row = k
        A[i], A[max_row] = A[max_row], A[i]
        b[i], b[max_row] = b[max_row], b[i]

        # 2. Forward Elimination
        pivot = A[i][i]
        if abs(pivot) < 1e-18:
            raise ValueError("Matrix is singular or nearly singular")
            
        for j in range(i + 1, n):
            factor = A[j][i] / pivot
            for k in range(i, n):
                A[j][k] -= factor * A[i][k]
            b[j] -= factor * b[i]

    # 3. Back Substitution
    x = [0] * n
    for i in range(n - 1, -1, -1):
        sum_ax = sum(A[i][j] * x[j] for j in range(i + 1, n))
        x[i] = (b[i] - sum_ax) / A[i][i]
    return x

def solve_linear_system(nodes, f_func):
    """
    Constructs the Remez system matrix and solves for coefficients.
    """
    n = len(nodes) - 2
    system_size = n + 2
    
    # Initialize Matrix A and Constants Vector B
    matrix_a = [[0.0 for _ in range(system_size)] for _ in range(system_size)]
    vector_b = [0.0 for _ in range(system_size)]
    
    for i in range(system_size):
        x = nodes[i]
        
        # Fill polynomial columns: C0 + C1*x + C2*x^2 ... Cn*x^n
        for j in range(n + 1):
            matrix_a[i][j] = math.pow(x, j)
            
        # Fill the error term E column with alternating signs
        # Row 0: +1, Row 1: -1, Row 2: +1, etc.
        matrix_a[i][n + 1] = 1.0 if i % 2 == 0 else -1.0
        
        # Fill target vector with function values
        vector_b[i] = f_func(x)
        
    # Solve the system
    solution = linear_solve_pure_python(matrix_a, vector_b)
    
    # Separate coefficients and E
    coeffs = solution[:n+1]
    E = solution[n+1]
    
    return coeffs, E

# --- Testing with Cosine (Degree 1) ---
if __name__ == "__main__":
    # test_nodes = [0.0, 0.5, 1.0]
    test_nodes = [0.0, 0.5, 1.0, 1.5]
    # We want to approximate cos(x)
    coeffs, error = solve_linear_system(test_nodes, math.cos)
    
    print(f"Polynomial: {coeffs[0]:.8f} + ({coeffs[1]:.8f} * x)")
    print(f"Max Error (E): {error:.8f}")