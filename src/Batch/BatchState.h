#ifndef BATCH_STATE_H
#define BATCH_STATE_H

enum class BatchState {
  TerminalInput,
  FileInput,
  SelectDataset,
  ShowDataset,
  Exit
};

#endif  // BATCH_STATE_H
