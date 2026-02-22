import math

def evaluate_polynomial(x, coeffs):
    """Evaluates polynomial using Horner's Method."""
    n = len(coeffs) - 1
    result = coeffs[n]
    for i in range(n - 1, -1, -1):
        result = result * x + coeffs[i]
    return result

def find_max_in_neighborhood(error_func, start_x, step):
    """Moves start_x to the highest local absolute error point."""
    x_left = start_x - step
    x_right = start_x + step
    
    y_mid = abs(error_func(start_x))
    y_left = abs(error_func(x_left))
    y_right = abs(error_func(x_right))
    
    if y_left > y_mid and y_left >= y_right:
        return x_left
    elif y_right > y_mid and y_right > y_left:
        return x_right
    return start_x

def refine_peak(error_func, initial_x, initial_step):
    """Refines a rough peak to high precision."""
    curr_x = initial_x
    step = initial_step
    for _ in range(20): # 20 iterations gives high precision
        curr_x = find_max_in_neighborhood(error_func, curr_x, step)
        step *= 0.5
    return curr_x

def find_all_extrema(f_target, coeffs, a, b, degree_n):
    """Finds n+2 points of maximum absolute error."""
    # Define error function E(x) = f(x) - P(x)
    def error_func(x):
        return f_target(x) - evaluate_polynomial(x, coeffs)
    
    num_samples = 1000
    step_size = (b - a) / (num_samples - 1)
    samples = [a + i * step_size for i in range(num_samples)]
    
    extrema = []
    
    # 1. Check endpoints first
    extrema.append(a)
    extrema.append(b)
    
    # 2. Search for internal local peaks/valleys
    for i in range(1, num_samples - 1):
        y_prev = abs(error_func(samples[i-1]))
        y_curr = abs(error_func(samples[i]))
        y_next = abs(error_func(samples[i+1]))
        
        if y_curr > y_prev and y_curr > y_next:
            # Refine the detected rough peak
            refined_x = refine_peak(error_func, samples[i], step_size)
            extrema.append(refined_x)
            
    extrema = sorted(list(set(extrema)))
    
    # Remez requires exactly degree_n + 2 points.
    # If we found more, we take the ones with the largest absolute errors.
    if len(extrema) > (degree_n + 2):
        extrema.sort(key=lambda x: abs(error_func(x)), reverse=True)
        extrema = sorted(extrema[:degree_n + 2])
        
    return extrema

if __name__ == "__main__":
    # We want to approximate cos(x)
    f_target = math.cos
    # coeffs = [1.053716, -0.459698]
    coeffs = [1.010322, -0.112550, -0.347148]
    degree_n = len(coeffs)-1
    extrema = find_all_extrema(f_target,coeffs,0.0,1.0,degree_n)
    
    print(f"{extrema=}")