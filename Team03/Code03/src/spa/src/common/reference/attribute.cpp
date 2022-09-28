#include "attribute.h"

#include <unordered_map>
#include <utility>

std::unordered_map<std::string, AttributeName> attrName_representation = {
    {"procName", PROC_NAME},
    {"varName", VAR_NAME},
    {"value", VALUE},
    {"stmt#", STMT_NO},
};

Attribute::Attribute(Synonym syn, AttributeName name)
    : name_(name), syn_(std::move(syn)) {}

Synonym Attribute::GetSynonym() const { return syn_; }

AttributeName Attribute::GetAttributeName() const { return name_; }

AttributeName Attribute::RetrieveAttributeName(const std::string& name) {
  if (attrName_representation.count(name)) {
    return attrName_representation[name];
  }
  throw std::exception("No such attribute name");
}
