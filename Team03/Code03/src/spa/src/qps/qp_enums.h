#ifndef SPA_QP_ENUMS_H
#define SPA_QP_ENUMS_H

#include "vector"
#include <string>

class QPEnums {
public:
    enum ClauseType {
        Select,
        Follows,
        FollowsT,
    };
    enum DesignEntity {
        Stmt,
        Read,
        Print,
        Call,
        While,
        If,
        Assign,
        Variable,
        Constant,
        Procedure,
    };
    std::vector<std::pair<DesignEntity, std::string>> DesignEntities = {
    {Stmt, "stmt"},
    {Read, "read"},
    {Print, "print"},
    {Call, "call"},
    {While, "while"},
    {If, "if"},
    {Assign, "assign"},
    {Variable, "variable"},
    {Constant, "constant"},
    {Procedure, "procedure"}
    };

    bool IsDesignEntity(std::string s);
};

#endif  // SPA_QP_ENUMS_H
