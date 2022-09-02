#include "follows_clause.h"

FollowsClause::FollowsClause(std::string stmtRef1, std::string stmtRef2) : stmtRef1(stmtRef1), stmtRef2(stmtRef2){}

std::string FollowsClause::GetSynonym() const { return synonym; }
