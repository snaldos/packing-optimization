#include "BatchInputManager.h"

#include "../RoutePlanning/RouteProcessor.h"

BatchInputManager::BatchInputManager(
    Graph<std::string> *driving_network, Graph<std::string> *walking_network,
    std::unordered_map<std::string, std::string> *id_code_map,
    std::unordered_map<std::string, Location> *code_location_map)
    : driving_network_(driving_network),
      walking_network_(walking_network),
      id_code_map_(id_code_map),
      code_location_map_(code_location_map) {};
/** @paragraph function that allows the user to choose what type of input they want. If they type 1 they choose
 * terminal input and it is given a template on how to type the input and processInput is called with
 * cin as a parameter. If they type 2 they chose file input and must submit a possible file
 * which is checked by ensureDirectory. When it receives an error it gives a message describing the error.
 * If they type 0 or 3 the function is returned and else it is given an error.
 * @return 0 if case 1 or 2, 1 if case 0 and -1 if case 3.
 * Complexity: O(n + m) (n: input length, m: file size)
*/
int BatchInputManager::getInputMode() {
  clearTerminal();
  std::cout << "Choose input mode:" << std::endl
            << "1: Terminal Input" << std::endl
            << "2: File Input\n"
            << std::endl
            << "0: back" << std::endl
            << "3: exit" << std::endl;
  while (true) {
    int choice_mode;
    std::string input_mode;
    std::getline(std::cin, input_mode);

    try {
      choice_mode = std::stoi(input_mode);
    } catch (const std::invalid_argument &e) {
      std::cerr << "ERROR: Input MUST be a number." << std::endl;
      continue;
    }

    switch (choice_mode) {
      case 1:
        clearTerminal();
        // initial message
        std::cout << "--> TERMINAL INPUT <--\n\n"
                     "INPUT FORMAT\n"
                     "<REQUIRED>\n"
                     "->Mode: driving | driving-walking\n"
                     "->Source:{id}\n"
                     "->Destination:{id}\n"
                     "<OPTIONAL>\n"
                     "->AvoidNodes:{id},{id},{id},...\n"
                     "->IncludeNodes:{id},{id},{id},...\n"
                     "->MaxWalkTime:int\n"
                     "->AvoidSegments:({id},{id}),({id},{id}),...\n\n"
                     "Enter input (end with an empty line):"
                  << std::endl;
        processInput(std::cin, std::cout);
        return 0;
      case 2: {
        clearTerminal();
        // INITIAL MESSAGE
        std::cout << "--> FILE INPUT <--\n\n"
                     "The file MUST be located in the project input folder.\n"
                     "Enter the filename or a space separated sequence of "
                     "filenames to run:"
                  << std::endl;

        // gets files
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::vector<std::string> filenames;
        std::string file;
        while (iss >> file) {
          filenames.push_back(file);
        }

        int openingErrors = 0;
        // input each file
        for (const std::string &filename : filenames) {
          std::string input_filename = "input/" + filename;
          std::ifstream input_file(input_filename);
          if (input_file.is_open()) {
            // Project root directory defined by CMake
            std::string project_root = PROJECT_DIR;

            // Ensure output directory exists
            std::string output_dir = project_root + "/output/";
            if (!ensureDirectory(output_dir)) return -1;

            std::string output_filename = output_dir + filename;
            std::ofstream output_file(output_filename);
            if (output_file.is_open()) {
              processInput(input_file, output_file);
              output_file.close();
            } else {
              std::cerr << "ERROR: Could not open output file: "
                        << output_filename << std::endl;
              processInput(input_file, std::cerr);
            }
            input_file.close();
          } else {
            std::cerr << "ERROR: Could not open input file: " << input_filename
                      << std::endl;
            openingErrors++;
          }
        }
        if (filenames.size() != openingErrors)
          std::cout << "\nThe output was generated and can be found on the "
                       "output folder."
                    << std::endl;

        if (openingErrors != 0) {
          std::cout << "(" << openingErrors
                    << (openingErrors == 1 ? " file was" : " files were")
                    << " ignored)" << std::endl;
        }
        return 0;
      }
      case 3:
        return -1;

      case 0:
        return 1;
      default:
        std::cerr << "ERROR: Invalid input mode." << std::endl;
        break;
    }
  }
}
/**
 * @brief 
 * this function processes the input by using fstreams by dividing the lines using : as a delimeter and
 *  setting the attribute to its according values. If there is an invalid maxWalkTime or an unercognized
 * value a message to the output source is sent.
 * @param input_stream the input source
 * @param output_stream the output source
 * @return void
 * Complexity: O(n + k + m) (n: number of input lines, k: number of list items, m: number of segments)
 */
void BatchInputManager::processInput(std::istream &input_stream,
                                     std::ostream &output_stream) {
  std::string line;
  InputParameters params;

  // Read input parameters
  while (std::getline(input_stream, line)) {
    if (line.empty()) {
      break;
    }
    std::stringstream ss(line);
    std::string type;
    std::string value;

    if (std::getline(ss, type, ':') && std::getline(ss, value)) {
      type = trim(type);
      value = trim(value);

      if (type == "Mode") {
        params.mode = value;
      } else if (type == "Source") {
        params.source_id = value;
      } else if (type == "Destination") {
        params.destination_id = value;
      } else if (type == "AvoidNodes") {
        params.restricted_route_requested = true;
        parseList(value, params.avoid_location_ids);
      } else if (type == "AvoidSegments") {
        params.restricted_route_requested = true;
        parseSegments(value, params.avoid_edge_ids);
      } else if (type == "IncludeNode") {
        params.restricted_route_requested = true;
        parseList(value, params.include_location_id);
      } else if (type == "MaxWalkTime") {
        try {
          params.max_walk_time = std::stod(value);
        } catch (const std::invalid_argument &e) {
          output_stream << "ERROR: Invalid MaxWalkTime value: " << value
                        << std::endl;
        }
      } else {
        output_stream << "WARNING: Unrecognized input type: " << type
                      << std::endl;
      }
    }
  }

  // Convert IDs to codes or keeps it if already is a code
  std::string source_code = (*id_code_map_)[params.source_id];
  std::string destination_code = (*id_code_map_)[params.destination_id];
  try {
    stoi(params.source_id);
  } catch (std::invalid_argument &e) {
    source_code = params.source_id;
  }
  try {
    stoi(params.destination_id);
  } catch (std::invalid_argument &e) {
    destination_code = params.destination_id;
  }

  std::vector<std::string> avoid_location_codes;
  for (const std::string &id : params.avoid_location_ids) {
    avoid_location_codes.push_back((*id_code_map_)[id]);
  }

  std::vector<std::pair<std::string, std::string> > avoid_edge_codes;
  for (const auto &edge : params.avoid_edge_ids) {
    avoid_edge_codes.push_back(
        {(*id_code_map_)[edge.first], (*id_code_map_)[edge.second]});
  }

  std::vector<std::string> include_location_code;
  for (const std::string &id : params.include_location_id) {
    include_location_code.push_back((*id_code_map_)[id]);
  }

  bool isError = false;  // avoid unnecessary calls for algorithms

  // Output source and destination
  if (code_location_map_->find(source_code) != code_location_map_->end()) {
    output_stream << "Source:" << params.source_id << std::endl;
  } else {
    output_stream << "ERROR: Invalid Source: " << params.source_id << std::endl;
    isError = true;
  }
  if (code_location_map_->find(destination_code) != code_location_map_->end()) {
    output_stream << "Destination:" << params.destination_id << std::endl;

  } else {
    output_stream << "ERROR: Invalid Destination: " << params.destination_id
                  << std::endl;
    isError = true;
  }

  // Perform actions based on mode
  RouteProcessor routeProcessor(driving_network_, walking_network_,
                                code_location_map_);
  if (params.mode == "driving" and !isError) {
    routeProcessor.processDrivingMode(
        source_code, destination_code, avoid_location_codes, avoid_edge_codes,
        include_location_code, params.restricted_route_requested,
        output_stream);
  } else if (params.mode == "driving-walking" and !isError) {
    routeProcessor.processDrivingWalkingMode(
        source_code, destination_code, params.max_walk_time,
        avoid_location_codes, avoid_edge_codes, output_stream);
  } else {
    output_stream << (params.mode == "driving" or
                              params.mode == "driving-walking"
                          ? "Mode: "
                          : "ERROR: Invalid mode: ")
                  << params.mode << std::endl;
    output_stream << "\nSource, Destination and Mode MUST be initialized and "
                     "valid to run."
                  << std::endl;
  }
}
/**
 * @brief Helper method to parse a string and adding the necessary characters to a list.
 * 
 * @param value the string we want to parse
 * @param list  the list where we want to add the elements. 
 * @return void
 * Complexity: O(n)
 */
void BatchInputManager::parseList(const std::string &value,
                                  std::vector<std::string> &list) {
  std::stringstream ss(value);
  std::string item;
  while (std::getline(ss, item, ',')) {
    item = trim(item);
    if (!item.empty()) {
      list.push_back(item);
    }
  }
}
/**
 * @brief Helper method to make sure we have a valid directory
 * 
 * @param dir the  directory
 * @return true if directory is valid else false
 * Complexity: O(1)
 */
bool BatchInputManager::ensureDirectory(const std::string &dir) {
  struct stat info;
  if (stat(dir.c_str(), &info) != 0) {
    if (mkdir(dir.c_str(), 0755) != 0) {
      std::cerr << "Could not create directory: " << dir << std::endl;
      return false;
    }
  } else if (!(info.st_mode & S_IFDIR)) {
    std::cerr << "Path exists but is not a directory: " << dir << std::endl;
    return false;
  }
  return true;
}

/**
 * @brief Helper method to parse a string and adding the necessary characters to a vector
 * of pairs of number id. It makes sure we only add the elements inside parenthesis using
 * a boolean value.
 * 
 * @param value the string we want to parse
 * @param segments the vector where the pairs will be added
 * @return void
 * Complexity: O(n)
 */
void BatchInputManager::parseSegments(
    const std::string &value,
    std::vector<std::pair<std::string, std::string> > &segments) {
  std::stringstream segment_ss(value);
  std::string segment;
  bool inParentheses = false;
  std::string currentSegment;

  // Now parse the segments inside parentheses
  for (char ch : value) {
    if (ch == '(') {
      inParentheses = true;    // Start collecting the segment
      currentSegment.clear();  // Clear current segment buffer
      currentSegment += ch;    // Add '('
    } else if (ch == ')') {
      inParentheses = false;  // End collecting the segment
      currentSegment += ch;   // Add ')'
      // Process the segment once parentheses are closed
      currentSegment =
          trim(currentSegment);  // Trim leading/trailing whitespace
      if (!currentSegment.empty()) {
        // Remove parentheses from the segment
        currentSegment = currentSegment.substr(1, currentSegment.length() - 2);

        size_t commaPos = currentSegment.find(',');
        if (commaPos != std::string::npos) {
          std::string node1 = currentSegment.substr(0, commaPos);
          std::string node2 = currentSegment.substr(commaPos + 1);

          node1 = trim(node1);
          node2 = trim(node2);

          // Push the pair of nodes to avoid_edge_ids
          segments.push_back({node1, node2});
        } else {
          std::cout
              << "ERROR: Invalid AvoidSegments format inside parentheses: "
              << currentSegment << std::endl;
        }
      }
    } else if (inParentheses) {
      // Add characters inside parentheses to the current segment
      currentSegment += ch;
    }
  }
}
/** @brief trims a string
 *  Complexity: O(1)
*/
std::string BatchInputManager::trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t");
  size_t last = str.find_last_not_of(" \t");
  return (first == std::string::npos || last == std::string::npos)
             ? ""
             : str.substr(first, last - first + 1);
}
/** @brief Clear terminal screen and displays header
 *  Complexity: O(1)
 */
void BatchInputManager::clearTerminal() {
  std::cout << "\033[2J\033[H" << std::flush;
  std::cout << "----- ROUTE PLANNING -----\n\n";
}