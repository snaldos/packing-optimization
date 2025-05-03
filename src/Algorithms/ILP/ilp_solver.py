import json
import sys

import pulp


def solve_knapsack(data):
    capacity = data["truck_capacity"]
    pallets = data["pallets"]

    prob = pulp.LpProblem("Knapsack", pulp.LpMaximize)
    x = {p["id"]: pulp.LpVariable(f"x_{p['id']}", cat="Binary") for p in pallets}

    prob += pulp.lpSum(p["profit"] * x[p["id"]] for p in pallets)
    prob += pulp.lpSum(p["weight"] * x[p["id"]] for p in pallets) <= capacity

    prob.solve()

    used_pallets = [p for p in pallets if x[p["id"]].value() == 1.0]
    total_profit = sum(p["profit"] for p in used_pallets)

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
