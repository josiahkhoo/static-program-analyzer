#ifndef SPA_TOKEN_BUILDER_PAIR_H
#define SPA_TOKEN_BUILDER_PAIR_H

#include <memory>

#include "qps/query_string_builder.h"
#include "qps/token_handler.h"

typedef std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder &>
    TokenBuilderPair;

#endif  // SPA_TOKEN_BUILDER_PAIR_H
