#include "BatchInputManager.h"

BatchInputManager::BatchInputManager(std::vector<Pallet>& pallets, Truck& truck)
    : pallets(pallets), truck(truck) {
  // Ensure the output directory exists and remove any existing files
  std::string output_dir = Utils::get_absolute_dir("/output");
  Utils::ensure_directory(output_dir);
}

BatchState BatchInputManager::getInputMode() {
  std::string prompt = "Choose an option (empty line to exit): ";
  std::vector<std::string> options = {"Run Algorithms", "Select Dataset",
                                      "Show Dataset"};
  int choice = BatchUtils::get_menu_choice(options, prompt);

  switch (choice) {
    case 1:
      BatchUtils::clear_terminal();
      return BatchState::RunAlgorithms;
    case 2:
      return BatchState::SelectDataset;
    case 3:
      return BatchState::ShowDataset;
    default:
      return BatchState::Exit;  // Fallback
  }
}

void BatchInputManager::generate_output_file(std::string& filename,
                                             std::vector<Pallet>& used_pallets,
                                             unsigned int& max_profit,
                                             std::string& message) {
  if (filename.empty()) {
    std::cerr << "ERROR: Filename is empty." << std::endl;
    return;
  }
  std::string output_dir = Utils::get_absolute_dir("/output");
  std::string output_file = output_dir + "/" + filename;
  std::ofstream file(output_file);
  if (!file.is_open()) {
    std::cerr << "ERROR: Could not open output file: " << output_file
              << std::endl;
    return;
  }

  if (!used_pallets.empty()) {
    unsigned int total_weight = 0;
    file << "id, profit, weight\n";
    for (const auto& pallet : used_pallets) {
      file << pallet.get_id() << ", " << pallet.get_profit() << ", "
           << pallet.get_weight() << "\n";
      total_weight += pallet.get_weight();
    }
    file << "\n" << "Total Weight: " << total_weight << "\n";
  }
  file << "Maximum Profit: " << max_profit << "\n\n";
  file << message << "\n";
  file.close();
}

void BatchInputManager::processInput() {
  BatchUtils::clear_terminal();
  std::string prompt = "Choose algorithm (empty line to exit): ";
  while (true) {
    std::vector<std::string> options = {
        "BF", "BT", "DP-VECTOR", "DP-HASHMAP", "DP-OPTIMIZED", "GREEDY-APPROX",
        "ILP"};
    int choice = BatchUtils::get_menu_choice(options, prompt);

    std::string filename;
    std::vector<Pallet> used_pallets;
    unsigned int max_profit = 0;
    std::string message;

    switch (choice) {
      case 1:
        filename = "bf.txt";
        max_profit =
            BruteForce().bf_solve(pallets, truck, used_pallets, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;
      case 2:
        filename = "bt.txt";
        max_profit =
            BruteForce().bt_solve(pallets, truck, used_pallets, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;
      case 3:
        filename = "dp_vector.txt";
        max_profit = DynamicProgramming().dp_solve(pallets, truck, used_pallets,
                                                   TableType::Vector, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;
      case 4:
        filename = "dp_hashmap.txt";
        max_profit = DynamicProgramming().dp_solve(pallets, truck, used_pallets,
                                                   TableType::HashMap, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;
      case 5:
        filename = "dp_optimized.txt";

        max_profit = DynamicProgramming().dp_solve(pallets, truck, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;

      case 6:
        filename = "greedy_approx.txt";

        max_profit =
            Greedy().approx_solve(pallets, truck, used_pallets, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;
      case 7:
        filename = "ilp.txt";
        max_profit = max_profit =
            ILPBridge().solve_with_ilp(pallets, truck, used_pallets, message);
        generate_output_file(filename, used_pallets, max_profit, message);
        break;
      default:
        std::cout << "Exiting process input...\n";
        return;  // Exit the function and the loop
    }
  }
}
