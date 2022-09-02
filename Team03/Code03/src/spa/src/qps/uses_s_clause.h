#ifndef SPA_USES_S_CLAUSE_H
#define SPA_USES_S_CLAUSE_H

#include "token.h"

class UsesSClause : public QueryTail {
public:
	explicit UsesSClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_USES_S_CLAUSE_H
