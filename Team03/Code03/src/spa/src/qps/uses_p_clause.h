#ifndef SPA_USES_P_CLAUSE_H
#define SPA_USES_P_CLAUSE_H

#include "token.h"

class UsesPClause : public QueryTail {
public:
	explicit UsesPClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_USES_P_CLAUSE_H
