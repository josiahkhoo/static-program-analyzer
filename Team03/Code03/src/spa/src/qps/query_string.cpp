#include "query_string.h"

SelectClause QueryString::GetSelectClause() const { return select_clause_; }
std::vector<DeclarationClause> QueryString::GetDeclarationClauses() const { return declaration_clauses_; }
std::vector<FollowsClause> QueryString::GetFollowsClauses() const {	return follows_clauses_; }
std::vector<FollowsTClause> QueryString::GetFollowsTClauses() const { return follows_t_clauses_; }
std::vector<ModifiesPClause> QueryString::GetModifiesPClauses() const { return modifies_p_clauses_; }
std::vector<ModifiesSClause> QueryString::GetModifiesSClauses() const {	return modifies_s_clauses_; }
std::vector<ParentClause> QueryString::GetParentClauses() const { return parent_clauses_; }
std::vector<ParentTClause> QueryString::GetParentTClauses() const { return parent_t_clauses_; }
std::vector<PatternClause> QueryString::GetPatternClauses() const { return pattern_clauses_; }
std::vector<UsesPClause> QueryString::GetUsesPClauses() const { return uses_p_clauses_; }
std::vector<UsesSClause> QueryString::GetUsesSClauses() const { return uses_s_clauses_; }

void QueryString::AddSelectClause(SelectClause select_clause_) const
{
	this->select_clause_ = select_clause_;
}

int QueryString::AddDeclarationClause(DeclarationClause clause_) const
{
	declaration_clauses_.push_back(clause_);
	return declaration_clauses_.size;
}

int QueryString::AddFollowsClause(FollowsClause clause_) const
{
	follows_clauses_.push_back(clause_);
	return follows_clauses_.size;
SelectClause QueryString::GetSelectClause() const {
  return select_clause_;
}

std::vector<QueryTail> QueryString::GetTails() const {
  return {};
}

void QueryString::AddSelectClause(SelectClause select_clause) {
  select_clause_ = select_clause;
}
