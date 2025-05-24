#include "BatchInputManager.h"

BatchInputManager::BatchInputManager(std::vector<Pallet> &pallets, Truck &truck)
    : pallets(pallets), truck(truck) {}

BatchState BatchInputManager::getInputMode() {
  std::string prompt = "Choose an option (empty line to exit): ";
  std::vector<std::string> options = {"Run Algorithms", "Select Dataset",
                                      "Show Dataset", "Change Timeout"};
  int choice = BatchUtils::get_menu_choice(options, prompt);

  switch (choice) {
  case 1:
    BatchUtils::clear_terminal();
    return BatchState::RunAlgorithms;
  case 2:
    return BatchState::SelectDataset;
  case 3:
    return BatchState::ShowDataset;
  case 4:
    return BatchState::SelectTimeout;
  default:
    return BatchState::Exit; // Fallback
  }
}

void BatchInputManager::select_timeout() {
  BatchUtils::clear_terminal();
  while (true) {
    std::cout << "Current timeout: " << timeout_ms << " ms ("
              << (timeout_ms / 1000.0) << " seconds)\n";
    std::cout << "Enter new timeout in milliseconds (empty line to exit): ";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
      return;
    }
    // Check if input is all digits (optionally allow leading +)
    std::string trimmed = ParserUtils::trim(input);
    if (trimmed.empty() || (trimmed[0] == '+' && trimmed.size() == 1)) {
      BatchUtils::clear_terminal();
      std::cerr
          << "ERROR: Invalid input. Please enter a non-negative integer.\n";
      continue;
    }
    size_t idx = 0;
    if (trimmed[0] == '+')
      idx = 1;
    bool all_digits = true;
    for (; idx < trimmed.size(); ++idx) {
      if (!isdigit(trimmed[idx])) {
        all_digits = false;
        break;
      }
    }
    if (!all_digits) {
      BatchUtils::clear_terminal();
      std::cerr
          << "ERROR: Invalid input. Please enter a non-negative integer.\n";
      continue;
    }
    try {
      unsigned int new_timeout = std::stoul(trimmed);
      timeout_ms = new_timeout;
      BatchUtils::clear_terminal();
      std::cout << "Timeout updated to " << timeout_ms << " ms ("
                << (timeout_ms / 1000.0) << " seconds).\n";
      std::cout << "Press Enter to continue...";
      std::getline(std::cin, input);
      return;
    } catch (...) {
      BatchUtils::clear_terminal();
      std::cerr
          << "ERROR: Invalid input. Please enter a non-negative integer.\n";
      continue;
    }
  }
}

void BatchInputManager::generate_output_file(std::string &filename,
                                             std::vector<Pallet> &used_pallets,
                                             unsigned int &max_profit,
                                             std::string &message) {
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
    for (const auto &pallet : used_pallets) {
      file << pallet.get_id() << ", " << pallet.get_profit() << ", "
           << pallet.get_weight() << "\n";
      total_weight += pallet.get_weight();
    }
    file << "\n"
         << "Total Weight: " << total_weight << "\n";
  }
  if (max_profit > 0) {
    file << "Maximum Profit: " << max_profit << "\n\n";
  }
  file << message << "\n";
  file.close();
}

void BatchInputManager::processInput() {
  BatchUtils::clear_terminal();
  std::string prompt = "Choose algorithm (empty line to exit): ";
  while (true) {
    std::vector<std::string> options = {"BF",
                                        "BT",
                                        "BB",
                                        "DP-VECTOR",
                                        "DP-HASHMAP",
                                        "DP-OPTIMIZED",
                                        "GREEDY-APPROX",
                                        "ILP-CPP",
                                        "ILP-PY"};
    int choice = BatchUtils::get_menu_choice(options, prompt);

    std::string filename;
    std::vector<Pallet> used_pallets;
    unsigned int max_profit = 0;
    std::string message;

    // TODO: For statistics, could add a function that based on message would
    // put it in csv format and append it to a csv file to then run a python
    // script to graph it

    switch (choice) {
    case 1:
      filename = "bf.txt";
      max_profit = BruteForce().bf_solve(pallets, truck, used_pallets, message,
                                         timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    case 2:
      filename = "bt.txt";
      max_profit = BruteForce().bt_solve(pallets, truck, used_pallets, message,
                                         timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    case 3:
      filename = "bb.txt";
      max_profit = BranchAndBound().bb_solve(pallets, truck, used_pallets,
                                             message, timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    case 4: {
      // DP-VECTOR
      char lex_choice = 'n';
      std::cout << "Enable lexicographical tie-breaking for DP-VECTOR? (y/N): ";
      std::string input;
      std::getline(std::cin, input);
      if (!input.empty()) lex_choice = std::tolower(input[0]);
      bool lex = (lex_choice == 'y');
      filename = "dp_vector.txt";
      max_profit = DynamicProgramming(lex).dp_solve(
          pallets, truck, used_pallets, TableType::Vector, message, timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    }
    case 5: {
      // DP-HASHMAP
      char lex_choice = 'n';
      std::cout << "Enable lexicographical tie-breaking for DP-HASHMAP? (y/N): ";
      std::string input;
      std::getline(std::cin, input);
      if (!input.empty()) lex_choice = std::tolower(input[0]);
      bool lex = (lex_choice == 'y');
      filename = "dp_hashmap.txt";
      max_profit = DynamicProgramming(lex).dp_solve(
          pallets, truck, used_pallets, TableType::HashMap, message, timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    }
    case 6:
      filename = "dp_optimized.txt";
      max_profit =
          DynamicProgramming().dp_solve(pallets, truck, message, timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    case 7:
      filename = "greedy_approx.txt";
      max_profit = Greedy().approx_solve(pallets, truck, used_pallets, message,
                                         timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    case 8:
      filename = "ilp_cpp.txt";
      max_profit = IntegerLinearProgramming().solve_ilp_cpp(
          pallets, truck, used_pallets, message, timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    case 9:
      filename = "ilp_py.txt";
      max_profit = ILPBridgePy().solve_ilp_py(pallets, truck, used_pallets,
                                              message, timeout_ms);
      generate_output_file(filename, used_pallets, max_profit, message);
      break;
    default:
      std::cout << "Exiting process input...\n";
      return; // Exit the function and the loop
    }
  }
}
