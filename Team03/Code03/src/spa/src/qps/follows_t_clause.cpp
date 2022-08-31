#include "follows_t_clause.h"

FollowsTClause::FollowsTClause(std::string stmtRef1, std::string stmtRef2) : stmtRef1(stmtRef1), stmtRef2(stmtRef2){}

std::string FollowsTClause::GetSynonym() const { return synonym; }
