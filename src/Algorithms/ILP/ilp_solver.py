import json
import sys

import pulp


def solve_knapsack(data):
    capacity = data["truck_capacity"]
    pallets = data["pallets"]

    # Problem definition with maximization goal
    prob = pulp.LpProblem(name="Knapsack", sense=pulp.LpMaximize)

    # Create binary variables for each pallet
    x = {p["id"]: pulp.LpVariable(name=f"x_{p['id']}", cat="Binary") for p in pallets}

    # Objective function: Maximize the total profit of selected pallets
    prob += pulp.lpSum(p["profit"] * x[p["id"]] for p in pallets)

    # Constraint: Total weight of selected pallets should not exceed the truck's capacity
    prob += pulp.lpSum(p["weight"] * x[p["id"]] for p in pallets) <= capacity

    # Solve the problem using CBC solver (or default solver)
    prob.solve(pulp.PULP_CBC_CMD(msg=False))

    # Collect the pallets selected in the optimal solution
    used_pallets = [p for p in pallets if x[p["id"]].value() == 1.0]

    # Calculate total profit from the selected pallets
    total_profit = sum(p["profit"] for p in used_pallets)

    # Return the result as a dictionary
    return {"total_profit": total_profit, "used_pallets": used_pallets}


if __name__ == "__main__":
    input_path = sys.argv[1]
    with open(input_path, "r") as f:
        data = json.load(f)

    result = solve_knapsack(data)

    # Write the JSON result to stdout
    output_path = sys.argv[2]
    with open(output_path, "w") as f:
        json.dump(result, f, indent=4)
