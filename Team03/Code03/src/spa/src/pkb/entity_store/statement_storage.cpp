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

std::unordered_set<std::string> StatementStorage::GetStatements() {
  std::unordered_set<std::string> res;
  for (int stmt : statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetCallStatements() {
  std::unordered_set<std::string> res;
  for (auto stmt : call_statement_num_to_proc_map_) {
    res.emplace(std::to_string(stmt.first));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetCallStatements(std::string proc) {
  std::unordered_set<std::string> res;
  for (auto stmt : call_statement_num_to_proc_map_) {
    if (stmt.second == proc) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetReadStatements() {
  std::unordered_set<std::string> res;
  for (auto stmt : read_statement_num_to_var_map_) {
    res.emplace(std::to_string(stmt.first));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetReadStatements(std::string var) {
  std::unordered_set<std::string> res;
  for (auto stmt : read_statement_num_to_var_map_) {
    if (stmt.second == var) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetPrintStatements() {
  std::unordered_set<std::string> res;
  for (auto stmt : print_statement_num_to_var_map_) {
    res.emplace(std::to_string(stmt.first));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetPrintStatements(std::string var) {
  std::unordered_set<std::string> res;
  for (auto stmt : print_statement_num_to_var_map_) {
    if (stmt.second == var) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetAssignStatements() {
  std::unordered_set<std::string> res;
  for (int stmt : assign_statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetIfStatements() {
  std::unordered_set<std::string> res;
  for (int stmt : if_statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

std::unordered_set<std::string> StatementStorage::GetWhileStatements() {
  std::unordered_set<std::string> res;
  for (int stmt : while_statement_list_) {
    res.emplace(std::to_string(stmt));
  }
  return res;
}

void StatementStorage::Clear() {
  statement_list_.clear();
  assign_statement_list_.clear();
  if_statement_list_.clear();
  while_statement_list_.clear();
  call_statement_num_to_proc_map_.clear();
  read_statement_num_to_var_map_.clear();
  print_statement_num_to_var_map_.clear();
}
