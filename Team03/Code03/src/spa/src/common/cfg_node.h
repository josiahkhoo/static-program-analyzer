#ifndef SPA_CFG_NODE_H
#define SPA_CFG_NODE_H

#include <vector>

class CFGNode {
 public:
  explicit CFGNode(int statement_number);

  [[nodiscard]] int GetStatementNumber() const;

  bool operator==(const CFGNode &rhs) const;

  bool operator!=(const CFGNode &rhs) const;

 private:
  int statement_number_;
};

#endif  // SPA_CFG_NODE_H
