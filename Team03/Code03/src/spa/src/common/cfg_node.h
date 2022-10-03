#ifndef SPA_CFG_NODE_H
#define SPA_CFG_NODE_H

#include <vector>

class CFGNode {
 public:
  CFGNode(std::vector<int> statement_numbers);

  std::vector<int> GetStatementNumbers() const;
 private:
  std::vector<int> statement_numbers_;
};
#endif  // SPA_CFG_NODE_H
