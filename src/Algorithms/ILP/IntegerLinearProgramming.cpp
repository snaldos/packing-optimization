#include "IntegerLinearProgramming.h"
#include "absl/time/time.h"

unsigned int IntegerLinearProgramming::solve_ilp_cpp(
    const std::vector<Pallet> &pallets, const Truck &truck,
    std::vector<Pallet> &used_pallets, std::string &message,
    unsigned int timeout_ms) {
  auto start_time = std::chrono::high_resolution_clock::now();
  unsigned int n = pallets.size();
  unsigned int max_weight = truck.get_capacity();
  unsigned int result = 0;

  operations_research::MPSolver solver(
      "knapsack_ilp",
      operations_research::MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);

  // Set time limit (milliseconds)
  solver.SetTimeLimit(absl::Milliseconds(timeout_ms));

  // variables: x[i] = 1 if pallet i is used, 0 otherwise
  std::vector<operations_research::MPVariable *> x;
  for (unsigned int i = 0; i < n; ++i) {
    x.push_back(solver.MakeBoolVar("x" + std::to_string(i)));
  }

  // constraint: total weight <= max_weight
  operations_research::MPConstraint *weight_constraint =
      solver.MakeRowConstraint(0.0, static_cast<double>(max_weight));
  for (unsigned int i = 0; i < n; ++i) {
    weight_constraint->SetCoefficient(
        x[i], static_cast<double>(pallets[i].get_weight()));
  }

  // objective: maximize total profit
  operations_research::MPObjective *objective = solver.MutableObjective();
  for (unsigned int i = 0; i < n; ++i) {
    objective->SetCoefficient(x[i],
                              static_cast<double>(pallets[i].get_profit()));
  }
  objective->SetMaximization();

  // solve
  const operations_research::MPSolver::ResultStatus status = solver.Solve();

  used_pallets.clear();
  if (status == operations_research::MPSolver::ABNORMAL ||
      status == operations_research::MPSolver::NOT_SOLVED) {
    message =
        "[ILP (CPP)] Timeout after " + std::to_string(timeout_ms) + " ms.";
    return 0;
  }
  if (status != operations_research::MPSolver::OPTIMAL &&
      status != operations_research::MPSolver::FEASIBLE) {
    message = "[ILP CPP] No feasible solution found.";
    return 0;
  }

  for (unsigned int i = 0; i < n; ++i) {
    if (x[i]->solution_value() > 0.5) {
      used_pallets.push_back(pallets[i]);
      result += pallets[i].get_profit();
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  message = "[ILP (CPP)] Execution time: " + std::to_string(duration) + " μs";
  return result;
}
