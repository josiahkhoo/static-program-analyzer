#ifndef SPA_QUERY_STRING_H
#define SPA_QUERY_STRING_H

#include <vector>
#include "declaration_clause.h"
#include "follows_clause.h"
#include "follows_t_clause.h"
#include "modifies_p_clause.h"
#include "modifies_s_clause.h"
#include "parent_clause.h"
#include "parent_t_clause.h"
#include "pattern_clause.h"
#include "select_clause.h"
#include "uses_p_clause.h"
#include "uses_s_clause.h"

class QueryString {
public:
	SelectClause GetSelectClause() const;
	std::vector<DeclarationClause> GetDeclarationClauses() const;
	std::vector<FollowsClause> GetFollowsClauses() const;
	std::vector<FollowsTClause> GetFollowsTClauses() const;
	std::vector<ModifiesPClause> GetModifiesPClauses() const;
	std::vector<ModifiesSClause> GetModifiesSClauses() const;
	std::vector<ParentClause> GetParentClauses() const;
	std::vector<ParentTClause> GetParentTClauses() const;
	std::vector<PatternClause> GetPatternClauses() const;
	std::vector<UsesPClause> GetUsesPClauses() const;
	std::vector<UsesSClause> GetUsesSClauses() const;

	void AddSelectClause(SelectClause select_clause_) const;
	int AddDeclarationClause(DeclarationClause clause_) const;
	int AddFollowsClause(FollowsClause clause_) const;
	int AddFollowsTClause() const;
	int AddModifiesPClause() const;
	int AddModifiesSClause() const;
	int AddParentClause() const;
	int AddParentTClause() const;
	int AddPatternClause() const;
	int AddUsesPClause() const;
	int AddUsesSClause() const;

private:
	SelectClause select_clause_;
	std::vector<DeclarationClause> declaration_clauses_;
	std::vector<FollowsClause> follows_clauses_;
	std::vector<FollowsTClause> follows_t_clauses_;
	std::vector<ModifiesPClause> modifies_p_clauses_;
	std::vector<ModifiesSClause> modifies_s_clauses_;
	std::vector<ParentClause> parent_clauses_;
	std::vector<ParentTClause> parent_t_clauses_;
	std::vector<PatternClause> pattern_clauses_;
	std::vector<UsesPClause> uses_p_clauses_;
	std::vector<UsesSClause> uses_s_clauses_;
};

#endif  // SPA_QUERY_STRING_H


#include "query_tail.h"
#include "select_clause.h"

class QueryString {
 public:
  [[nodiscard]] SelectClause GetSelectClause() const;
  [[nodiscard]] std::vector<QueryTail> GetTails() const;
  void AddSelectClause(SelectClause select_clause);
 private:
  SelectClause select_clause_;
};

#endif  // SPA_QUERY_STRING_H