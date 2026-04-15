import sys


def ft_sqrt(n):
    if n < 0:
        return -1
    if n == 0:
        return 0
    low = 0
    high = n
    if n < 1:
        high = 1
    mid = (low + high) / 2
    while 1e-10 < abs(mid * mid - n):
        if mid * mid < n:
            low = mid
        else:
            high = mid
        mid = (low + high) / 2
    return mid


def solve_degree2(terms):
    a = terms.get(2, 0.0)
    b = terms.get(1, 0.0)
    c = terms.get(0, 0.0)
    discriminant = b * b - 4 * a * c
    if 0 < discriminant:
        sqrt_d = ft_sqrt(discriminant)
        x1 = (-b + sqrt_d) / (2 * a)
        x2 = (-b - sqrt_d) / (2 * a)
        print("Discriminant is strictly positive, the two solutions are:")
        print(max(x1, x2))
        print(min(x1, x2))
    elif discriminant == 0:
        print("Discriminant is zero, the solution is:")
        print(-b / (2 * a))
    else:
        sqrt_d = ft_sqrt(-discriminant)
        real_part = -b / (2 * a)
        imag_part = abs(sqrt_d / (2 * a))
        if real_part == 0:
            real_part = 0
        print("Discriminant is strictly negative, the two complex solutions are:")
        print(f"{real_part} + {imag_part}i")
        print(f"{real_part} - {imag_part}i")


def solve_degree1(terms):
    b = terms.get(1, 0.0)
    c = terms.get(0, 0.0)
    print("The solution is:")
    print(-c / b)


def solve_degree0(terms):
    c = terms.get(0, 0.0)
    if c == 0:
        print("All real numbers are solutions.")
    else:
        print("No solution.")


def get_degree(terms):
    degree = 0
    for exp, coef in terms.items():
        if 1e-10 < abs(coef) and degree < exp:
            degree = exp
    return degree


def format_coef(coef):
    if coef == int(coef):
        return int(coef)
    return coef


def to_reduced_form(terms):
    parts = []
    for exp in sorted(terms.keys()):
        coef = terms[exp]
        if abs(coef) < 1e-10:
            coef = 0
        c = format_coef(coef)
        if not parts:
            parts.append(f"{c} * X^{exp}")
        elif coef >= 0:
            parts.append(f" + {c} * X^{exp}")
        else:
            parts.append(f" - {format_coef(-coef)} * X^{exp}")
    return ("".join(parts) or "0") + " = 0"


def solve(terms):
    print(f"Reduced form: {to_reduced_form(terms)}")
    degree = get_degree(terms)
    print(f"Polynomial degree: {degree}")
    if 2 < degree:
        print("The polynomial degree is strictly greater than 2, I can't solve.")
        return
    if degree == 0:
        solve_degree0(terms)
    elif degree == 1:
        solve_degree1(terms)
    elif degree == 2:
        solve_degree2(terms)


def parse_term(term):
    coef_str, var_str = term.split("*", 1)
    coefficient = float(coef_str)
    exponent = int(var_str.split("^", 1)[1])
    return exponent, coefficient


def parse_side(side):
    terms = {}
    s = side.strip().replace(" ", "").replace("\t", "")
    s = s.replace("+", " + ").replace("-", " - ")
    tokens = s.split()
    sign = 1
    for token in tokens:
        if token == '+':
            sign = 1
        elif token == '-':
            sign = -1
        else:
            exp, coef = parse_term(token)
            terms[exp] = coef * sign
    return terms


def parse(input_str):
    left, right = input_str.split("=", 1)
    left_terms = parse_side(left)
    right_terms = parse_side(right)
    result = dict(left_terms)
    for exp, coef in right_terms.items():
        result[exp] = result.get(exp, 0.0) - coef
    return result


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 computor.py \"equation\"", file=sys.stderr)
        sys.exit(1)
    terms = parse(sys.argv[1])
    solve(terms)
