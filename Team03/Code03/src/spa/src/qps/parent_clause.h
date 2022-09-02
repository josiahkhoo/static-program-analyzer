#ifndef SPA_PARENT_CLAUSE_H
#define SPA_PARENT_CLAUSE_H

#include "token.h"

class ParentClause : public QueryTail {
public:
	explicit ParentClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_PARENT_CLAUSE_H
