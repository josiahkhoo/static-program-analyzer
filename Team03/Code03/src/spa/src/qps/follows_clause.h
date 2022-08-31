#ifndef SPA_FOLLOWS_CLAUSE_H
#define SPA_FOLLOWS_CLAUSE_H

#include <string>

class FollowsClause : public QueryTail {
public:
	explicit FollowsClause(std::string stmtRef1, std::string stmtRef2);
	std::string GetSynonym() const;

private:
	std::string stmtRef1;
	std::string stmtRef2;
};

#endif  // SPA_FOLLOWS_CLAUSE_H
