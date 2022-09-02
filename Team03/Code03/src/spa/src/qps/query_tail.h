#ifndef SPA_QUERY_TAIL_H
#define SPA_QUERY_TAIL_H

class QueryTail {
 public:
  virtual std::vector<Entity> Filter(QueryablePkb &pkb) = 0;
  virtual std::vector<Entity> Filter(QueryablePkb &pkb, std::vector<Entity> list_of_entity) = 0;
};

#endif  // SPA_QUERY_TAIL_H