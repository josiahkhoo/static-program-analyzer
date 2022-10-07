#include "attribute.h"

#include <utility>

#include "common/reference/attribute_name.h"

std::unordered_map<std::string, AttributeName>
    Attribute::attrNameRepresentation = {
        {"procName", PROC_NAME},
        {"varName", VAR_NAME},
        {"value", VALUE},
        {"stmt", STMT_NO},
};

// Map of allowed Synonym x Attribute Name
std::unordered_map<EntityType, std::unordered_set<AttributeName>>
    Attribute::entityAllowedAttributes = {
        {PROCEDURE, {PROC_NAME}},     {CALL, {PROC_NAME, STMT_NO}},
        {VARIABLE, {VAR_NAME}},       {READ, {VAR_NAME, STMT_NO}},
        {PRINT, {VAR_NAME, STMT_NO}}, {CONSTANT, {VALUE}},
        {STATEMENT, {STMT_NO}},       {IF, {STMT_NO}},
        {WHILE, {STMT_NO}},           {ASSIGN, {STMT_NO}},
};

Attribute::Attribute(Synonym syn, AttributeName name)
    : name_(name), syn_(std::move(syn)) {}

Synonym Attribute::GetSynonym() const { return syn_; }

AttributeName Attribute::GetAttributeName() const { return name_; }

bool Attribute::IsName() const {
  return name_ == VAR_NAME || name_ == PROC_NAME;
}

bool Attribute::IsInteger() const { return name_ == VALUE || name_ == STMT_NO; }