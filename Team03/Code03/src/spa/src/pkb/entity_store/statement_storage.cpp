#include "statement_storage.h"

StatementStorage::StatementStorage() {}

void StatementStorage::AddCallStatement(CallEntity callEntity) {
  call_statement_num_to_proc_map_.emplace(callEntity.GetStatementNumber(),
                                          callEntity.GetProcedureName());
  statement_list_.emplace(callEntity.GetStatementNumber());
}

void StatementStorage::AddReadStatement(ReadEntity readEntity) {
  read_statement_num_to_var_map_.emplace(readEntity.GetStatementNumber(),
                                         readEntity.GetVariableName());
  statement_list_.emplace(readEntity.GetStatementNumber());
}

void StatementStorage::AddPrintStatement(PrintEntity printEntity) {
  print_statement_num_to_var_map_.emplace(printEntity.GetStatementNumber(),
                                          printEntity.GetVariableName());
  statement_list_.emplace(printEntity.GetStatementNumber());
}

void StatementStorage::AddAssignStatement(AssignEntity assignEntity) {
  assign_statement_list_.emplace(assignEntity.GetStatementNumber());
  statement_list_.emplace(assignEntity.GetStatementNumber());
}

void StatementStorage::AddIfStatement(IfEntity ifEntity) {
  if_statement_list_.emplace(ifEntity.GetStatementNumber());
  statement_list_.emplace(ifEntity.GetStatementNumber());
}

void StatementStorage::AddWhileStatement(WhileEntity whileEntity) {
  while_statement_list_.emplace(whileEntity.GetStatementNumber());
  statement_list_.emplace(whileEntity.GetStatementNumber());
}

std::unordered_set<std::string> StatementStorage::GetStatements() const {
  std::unordered_set<std::string> res;
  for (int stmt : statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetCallStatements() const {
  std::unordered_set<std::string> res;
  for (auto stmt : call_statement_num_to_proc_map_) {
    res.emplace(std::to_string(stmt.first));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetCallStatements(
    std::string proc) const {
  std::unordered_set<std::string> res;
  for (auto stmt : call_statement_num_to_proc_map_) {
    if (stmt.second == proc) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

std::string StatementStorage::GetCallStatementProcedure(
    int statement_number) const {
  std::string result;
  if (call_statement_num_to_proc_map_.find(statement_number) !=
      call_statement_num_to_proc_map_.end()) {
    result = call_statement_num_to_proc_map_.at(statement_number);
  }
  return result;
}

std::unordered_set<std::string> StatementStorage::GetReadStatements() const {
  std::unordered_set<std::string> res;
  for (auto stmt : read_statement_num_to_var_map_) {
    res.emplace(std::to_string(stmt.first));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetReadStatements(
    std::string var) const {
  std::unordered_set<std::string> res;
  for (auto stmt : read_statement_num_to_var_map_) {
    if (stmt.second == var) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

std::string StatementStorage::GetReadStatementVariable(
    int statement_number) const {
  std::string result;
  if (read_statement_num_to_var_map_.find(statement_number) !=
      read_statement_num_to_var_map_.end()) {
    result = read_statement_num_to_var_map_.at(statement_number);
  }
  return result;
}

std::unordered_set<std::string> StatementStorage::GetPrintStatements() const {
  std::unordered_set<std::string> res;
  for (auto stmt : print_statement_num_to_var_map_) {
    res.emplace(std::to_string(stmt.first));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetPrintStatements(
    std::string var) const {
  std::unordered_set<std::string> res;
  for (auto stmt : print_statement_num_to_var_map_) {
    if (stmt.second == var) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

std::string StatementStorage::GetPrintStatementVariable(
    int statement_number) const {
  std::string result;
  if (print_statement_num_to_var_map_.find(statement_number) !=
      print_statement_num_to_var_map_.end()) {
    result = print_statement_num_to_var_map_.at(statement_number);
  }
  return result;
}

std::unordered_set<std::string> StatementStorage::GetAssignStatements() const {
  std::unordered_set<std::string> res;
  for (int stmt : assign_statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetIfStatements() const {
  std::unordered_set<std::string> res;
  for (int stmt : if_statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetWhileStatements() const {
  std::unordered_set<std::string> res;
  for (int stmt : while_statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}
