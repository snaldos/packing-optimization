#include "ILPBridge.h"

using json = nlohmann::json;

unsigned int ILPBridge::solve_with_ilp(const std::vector<Pallet>& pallets,
                                       const Truck& truck,
                                       std::vector<Pallet>& used_pallets,
                                       std::string& message) {
  auto start_time = std::chrono::high_resolution_clock::now();

  // Construct paths using PROJECT_DIR
  std::string tmp_dir = Utils::get_absolute_dir("/src/Algorithms/ILP/tmp");
  std::string input_path = tmp_dir + "/ilp_input.json";
  std::string output_path = tmp_dir + "/ilp_output.json";
  std::string error_log_path = tmp_dir + "/ilp_error.log";
  std::string script_path = "/src/Algorithms/ILP/ilp_solver.py";
  script_path = Utils::get_absolute_dir(script_path);

  Utils::ensure_directory(tmp_dir);

  // Serialize input
  json input_json;
  input_json["truck_capacity"] = truck.get_capacity();
  for (const auto& p : pallets) {
    input_json["pallets"].push_back({{"id", p.get_id()},
                                     {"weight", p.get_weight()},
                                     {"profit", p.get_profit()}});
  }

  std::ofstream(input_path) << input_json.dump(4);

  // Call Python
  std::string command = "python3 " + script_path + " " + input_path + " " +
                        output_path + " 2> " + error_log_path;
  int ret = std::system(command.c_str());
  if (ret != 0) {
    std::ifstream error_log(error_log_path);
    std::string error_message((std::istreambuf_iterator<char>(error_log)),
                              std::istreambuf_iterator<char>());
    message = "[ILP] Python execution failed: " + error_message;
    return 0;
  }

  // Read output
  std::ifstream in(output_path);
  json output_json;
  in >> output_json;

  used_pallets.clear();
  unsigned int total_profit = output_json["total_profit"];
  for (const auto& p : output_json["used_pallets"]) {
    auto it = std::find_if(
        pallets.begin(), pallets.end(),
        [&](const Pallet& pal) { return pal.get_id() == p["id"]; });
    if (it != pallets.end()) used_pallets.push_back(*it);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  message = "[ILP] Execution time: " + std::to_string(duration) + " μs";
  return total_profit;
}
