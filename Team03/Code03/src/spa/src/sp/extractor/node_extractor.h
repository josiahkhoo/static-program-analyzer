#ifndef SPA_NODE_EXTRACTOR_H
#define SPA_NODE_EXTRACTOR_H

#include "common/t_node.h"

template<typename T>
class NodeExtractor {
public:
    virtual std::optional<T> TryExtractFromNode(const TNode &ast) const = 0;
};

#endif  // SPA_NODE_EXTRACTOR_H
