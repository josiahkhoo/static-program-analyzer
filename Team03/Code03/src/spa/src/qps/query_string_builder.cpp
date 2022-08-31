#include "query_string_builder.h"
#include "query_parser.h"
#include "token.h"
#include "common/parser.h"
#include "qp_enums.h"
#include <stdexcept>

QueryString QueryStringBuilder::parse(std::vector<Token> tokens_)
{
	try {
		this->tokens_ = tokens_;

		FindDeclarationClauses();

		FindSelectClause();

		FindSuchThatPatternClauses();

		return queryString;
	}
	catch (const std::runtime_error& e_) {
		cout << e_.what();
	}
}

Token Peek(int pos) {
	if (pos >= tokens_.size()) {
		throw std::runtime_error("No more tokens left to Peek");
	}
	return tokens_[pos];
}

bool MatchKind(Token::Kind kind) {
	return Peek(token_pos_).Is(kind);
}

bool MatchString(const std::string& s) {
	return (Peek(token_pos_).GetValue() == s);
}

bool MatchStmtRef() {
	return MatchKind(Token::IDENTIFIER) || MatchKind(Token::UNDERSCORE) || MatchKind(Token::NUMBER);
}

void Expect(Token::Kind kind) {
	if (MatchKind(kind)) {
		token_pos_++;
	}
	else {
		throw std::runtime_error("Expected a different token kind");
	}
}

void Expect(const std::string& s) {
	if (MatchString(s)) {
		token_pos_++;
	}
	else {
		throw std::runtime_error("Expected a different token string");
	}
}

void ExpectStmtRef() {
	if (MatchStmtRef()) {
		token_pos_++;
	}
	else {
		throw std::runtime_error("Expected a stmtRef");
	}
}

void FindDeclarationClauses() {
	while (IsDesignEntity()) {
		DeclarationClause decCl = ParseDeclaration();
		queryString.AddDeclarationClause(decCl);
		if (MatchKind(Token::COMMA)) {
			token_pos_++;
			continue;
		}
		else if (MatchKind(Token::SEMICOLON)) {
			Expect(Token::NEXT_LINE);
			token_pos_++;
			break;
		}
	}
}

bool IsDesignEntity() {
	return (QPEnums::IsDesignEntity(Peek(token_pos_).GetValue()));
}

DeclarationClause ParseDeclaration() {
	QPEnums::DesignEntities ent;
	for (auto const& pair : QPEnums::DesignEntities) {
		if (Peek(token_pos_).GetValue() == pair.second) {
			ent = pair.second;
			token_pos_++;
			break;
		}
	}

	Token syn = Peek(token_pos_);
	Expect(Token::IDENTIFIER);

	return DeclarationClause(ent, syn);
}

void FindSelectClause() {
	next = Peek(token_pos_);
	Expect("Select");
	next = Peek(token_pos_);
	Expect(Token::IDENTIFIER);
	queryString.AddSelectClause(SelectClause(next.GetValue()));
}

void FindSuchThatPatternClauses() {
	while (!MatchKind(Token::END)) {
		if (MatchString("such")) {
			token_pos_++;
			Expect("that");
			FollowsClause folCl = ParseFollows();
			queryString.AddFollowsClause(folCl);
		}
		/*else if (MatchString("pattern")) {

		}*/
		else {
			throw std::runtime_error("Unexpected token: " + Peek(token_pos_).GetValue());
		}
	}
}

FollowsClause ParseFollows() {
	std::string stmtRef1, stmtRef2;

	Expect("Follows");
	Expect(Token::LEFT_ROUND_BRACKET);
	stmtRef1 = Peek(token_pos_).GetValue();
	ExpectStmtRef();
	stmtRef2 = Peek(token_pos_).GetValue();
	ExpectStmtRef();
	Expect(Token::RIGHT_ROUND_BRACKET);
	return FollowsClause(stmtRef1, stmtRef2);
}
