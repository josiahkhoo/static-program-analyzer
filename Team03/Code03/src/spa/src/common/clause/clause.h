#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include "common/pair.h"
#include "common/such_that.h"

template <class T, class U>
class Clause : public Pair<T, U>, public SuchThat {};

#endif  // SPA_CLAUSE_H
