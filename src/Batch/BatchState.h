#ifndef BATCH_STATE_H
#define BATCH_STATE_H

/**
 * @enum BatchState
 * @brief Represents the possible states in the batch mode user interface.
 *
 * Used to control the main loop and user interaction flow in batch mode.
 */
enum class BatchState {
  RunAlgorithms, ///< State for running algorithms
  SelectDataset, ///< State for selecting a dataset
  ShowDataset,   ///< State for displaying the current dataset
  SelectTimeout, ///< State for changing the timeout value
  Exit           ///< State for exiting the batch mode
};

#endif  // BATCH_STATE_H
