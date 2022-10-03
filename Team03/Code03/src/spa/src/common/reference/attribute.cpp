#include "attribute.h"

#include <utility>

std::unordered_map<std::string, Attribute::AttributeName>
    Attribute::attrName_representation = {
        {"procName", PROC_NAME},
        {"varName", VAR_NAME},
        {"value", VALUE},
        {"stmt", STMT_NO},
};

Attribute::Attribute(Synonym syn, AttributeName name)
    : name_(name), syn_(std::move(syn)) {}

Synonym Attribute::GetSynonym() const { return syn_; }

Attribute::AttributeName Attribute::GetAttributeName() const { return name_; }

bool Attribute::IsName() const {
  return name_ == VAR_NAME || name_ == PROC_NAME;
}

bool Attribute::IsInteger() const { return name_ == VALUE || name_ == STMT_NO; }