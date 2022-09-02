#ifndef SPA_MODIFIES_S_CLAUSE_H
#define SPA_MODIFIES_S_CLAUSE_H

#include "token.h"

class ModifiesSClause : public QueryTail {
public:
	explicit ModifiesSClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_MODIFIES_S_CLAUSE_H
