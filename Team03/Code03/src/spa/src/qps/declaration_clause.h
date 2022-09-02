#ifndef SPA_DECLARATION_CLAUSE_H
#define SPA_DECLARATION_CLAUSE_H

#include "qp_enums.h"
#include <string>

class DeclarationClause : public QueryTail {
public:
	explicit DeclarationClause(QPEnums::DesignEntity type, std::string synonym);
	QPEnums::DesignEntity GetType() const;
	std::string GetSynonym() const;

private:
	QPEnums::DesignEntity type;
	std::string synonym;
};

#endif  // SPA_DECLARATION_CLAUSE_H
