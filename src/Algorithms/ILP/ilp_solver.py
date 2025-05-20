import json
import sys
import time

import pulp


def solve_knapsack(data, timeout_s=None):
    capacity = data["truck_capacity"]
    pallets = data["pallets"]

    # Problem definition with maximization goal
    prob = pulp.LpProblem(name="knapsack_ilp", sense=pulp.LpMaximize)

    # Create binary variables for each pallet
    x = {p["id"]: pulp.LpVariable(name=f"x_{p['id']}", cat="Binary") for p in pallets}

    # Objective function: Maximize the total profit of selected pallets
    prob += pulp.lpSum(p["profit"] * x[p["id"]] for p in pallets)

    # Constraint: Total weight of selected pallets should not exceed the truck's capacity
    prob += pulp.lpSum(p["weight"] * x[p["id"]] for p in pallets) <= capacity

    # Solve the problem using CBC solver (or default solver)
    solver = pulp.PULP_CBC_CMD(msg=False)
    if timeout_s is not None:
        solver.timeLimit = timeout_s
    status = prob.solve(solver)

    # Check for timeout (CBC returns status 0 if stopped by time limit)
    if status == pulp.LpStatusNotSolved:
        return {"timeout": True, "total_profit": 0, "used_pallets": []}

    # Collect the pallets selected in the optimal solution
    used_pallets = [p for p in pallets if x[p["id"]].value() == 1.0]

    # Calculate total profit from the selected pallets
    total_profit = sum(p["profit"] for p in used_pallets)

    # Return the result as a dictionary
    return {"timeout": False, "total_profit": total_profit, "used_pallets": used_pallets}


if __name__ == "__main__":
    input_path = sys.argv[1]
    with open(input_path, "r") as f:
        data = json.load(f)

    timeout_s = None
    if len(sys.argv) > 3:
        try:
            timeout_s = float(sys.argv[3]) / 1000.0
        except Exception:
            timeout_s = None

    result = solve_knapsack(data, timeout_s)

    # Write the JSON result to stdout
    output_path = sys.argv[2]
    with open(output_path, "w") as f:
        json.dump(result, f, indent=4)
