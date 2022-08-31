#ifndef SPA_SELECT_CLAUSE_H
#define SPA_SELECT_CLAUSE_H

#include <string>

class SelectClause : public QueryTail {
public:
	explicit SelectClause(std::string synonym);
	std::string GetSynonym() const;

private:
	std::string synonym;
};

#endif  // SPA_SELECT_CLAUSE_H
