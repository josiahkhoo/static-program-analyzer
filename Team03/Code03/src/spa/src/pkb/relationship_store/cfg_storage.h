#ifndef SPA_CFG_STORAGE_H
#define SPA_CFG_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "sp/extractor/cfg.h"

class CFGStorage {
 public:
  void AddCFG(CFG cfg);

  std::unordered_set<int> GetForwardNeighbours(int stmt) const;

  std::unordered_set<int> GetBackwardNeighbours(int stmt) const;

  void Clear();

 private:
  std::unordered_map<int, std::shared_ptr<CFG>> stmt_to_cfg_map_;
};

#endif  // SPA_CFG_STORAGE_H
