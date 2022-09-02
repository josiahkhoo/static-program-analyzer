#ifndef SPA_MODIFIES_P_CLAUSE_H
#define SPA_MODIFIES_P_CLAUSE_H

#include "token.h"

class ModifiesPClause : public QueryTail {
public:
	explicit ModifiesPClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_MODIFIES_P_CLAUSE_H
