#ifndef BATCH_STATE_H
#define BATCH_STATE_H

enum class BatchState {
  RunAlgorithms,
  SelectDataset,
  ShowDataset,
  SelectTimeout,
  Exit
};

#endif  // BATCH_STATE_H
