#ifndef SPA_CFG_NODE_H
#define SPA_CFG_NODE_H

#include <vector>

class CFGNode {
 public:
  explicit CFGNode(std::vector<int> statement_numbers);

  [[nodiscard]] std::vector<int> GetStatementNumbers() const;

  bool operator==(const CFGNode &rhs) const;

  bool operator!=(const CFGNode &rhs) const;

 private:
  std::vector<int> statement_numbers_;
};

#endif  // SPA_CFG_NODE_H
