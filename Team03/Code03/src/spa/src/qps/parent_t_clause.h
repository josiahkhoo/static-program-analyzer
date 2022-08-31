#ifndef SPA_PARENT_T_CLAUSE_H
#define SPA_PARENT_T_CLAUSE_H

#include "token.h"

class ParentTClause : public QueryTail {
public:
	explicit ParentTClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_PARENT_T_CLAUSE_H
