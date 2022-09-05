#ifndef SPA_QUERYABLE_ONE_ARG_H
#define SPA_QUERYABLE_ONE_ARG_H

#include <vector>

template<class T, class R>
class QueryableWithOneArg {
public:
    virtual std::vector<R> query(T) = 0;
};

#endif  // SPA_QUERYABLE_ONE_ARG_H
