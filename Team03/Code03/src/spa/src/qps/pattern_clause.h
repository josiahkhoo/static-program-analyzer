#ifndef SPA_PATTERN_CLAUSE_H
#define SPA_PATTERN_CLAUSE_H

#include "token.h"

class PatternClause : public QueryTail {
public:
	explicit PatternClause(Token::IDENTIFIER synonym);

private:
	Token::IDENTIFIER synonym;
};

#endif  // SPA_PATTERN_CLAUSE_H
