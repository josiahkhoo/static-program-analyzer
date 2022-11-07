#include <algorithm>
#include <sstream>

#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/cfg_extractor_impl.h"
#include "sp/simple_lexer.h"
#include "sp/simple_parser.h"

std::vector<CFGNode> CreateVector(
    std::unordered_set<std::shared_ptr<CFGNode>> const &nodes) {
  std::vector<CFGNode> res_nodes;
  for (auto &node : nodes) {
    res_nodes.emplace_back(*node);
  }
  return res_nodes;
}

TEST_CASE("CFG Extractor", "[CFGExtractor]") {
  CFGExtractorImpl cfg_extractor_under_test = CFGExtractorImpl();
  SimpleParser parser;
  SimpleLexer lexer = SimpleLexer(Lexer());

  SECTION("Extract 1-depth node") {
    std::istringstream input("procedure p { m = x * y + z / 100; x = x + 1;}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);

    // Compare each next CFG
    auto next_nodes1 = first_cfg.GetNextNodes(node1);
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 1);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    auto next_nodes2 = first_cfg.GetNextNodes(node2);
    REQUIRE(next_nodes2.empty());
  }

  SECTION("Extract if node") {
    std::istringstream input(
        "procedure p "
        "{ "
        "a = 1;"
        "x = 1;"
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "y = 2;"
        "}"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto next_nodes4 = first_cfg.GetNextNodes(node4);
    REQUIRE(next_nodes4.empty());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.empty());
    auto res_prev_nodes5 = CreateVector(first_cfg.GetPrevNodes(node5));
    REQUIRE(std::find(res_prev_nodes5.begin(), res_prev_nodes5.end(),
                      CFGNode(3)) != res_prev_nodes5.end());
    auto res_prev_nodes4 = CreateVector(first_cfg.GetPrevNodes(node4));
    REQUIRE(std::find(res_prev_nodes4.begin(), res_prev_nodes4.end(),
                      CFGNode(3)) != res_prev_nodes4.end());
    auto res_prev_nodes3 = CreateVector(first_cfg.GetPrevNodes(node3));
    REQUIRE(std::find(res_prev_nodes3.begin(), res_prev_nodes3.end(),
                      CFGNode(2)) != res_prev_nodes3.end());
    auto res_prev_nodes2 = CreateVector(first_cfg.GetPrevNodes(node2));
    REQUIRE(std::find(res_prev_nodes2.begin(), res_prev_nodes2.end(),
                      CFGNode(1)) != res_prev_nodes2.end());
    auto res_prev_nodes1 = CreateVector(first_cfg.GetPrevNodes(node1));
    REQUIRE(res_prev_nodes1.empty());
  }

  SECTION("Extract starting if node") {
    std::istringstream input(
        "procedure p "
        "{ "
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "y = 2;"
        "}"
        "z = 1;"
        "x = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    auto next_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(next_nodes5.empty());
  }

  SECTION("Extract statements before and after if node") {
    std::istringstream input(
        "procedure p "
        "{ "
        "s = 1;"
        "z = 1;"
        "if (z == 1) then {"
        "y = 1;"
        "z = 1;"
        "} else {"
        "y = 2;"
        "l = 1;"
        "}"
        "z = 1;"
        "x = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);
    auto node9 = first_cfg.GetNode(9);
    REQUIRE(node9->GetStatementNumber() == 9);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 1);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(6)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(8)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 1);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(8)) !=
            res_nodes7.end());
    auto res_nodes8 = CreateVector(first_cfg.GetNextNodes(node8));
    REQUIRE(res_nodes8.size() == 1);
    REQUIRE(std::find(res_nodes8.begin(), res_nodes8.end(), CFGNode(9)) !=
            res_nodes8.end());
    auto res_nodes9 = CreateVector(first_cfg.GetNextNodes(node9));
    REQUIRE(res_nodes9.empty());
  }

  SECTION("Extract statements nested if node") {
    std::istringstream input(
        "procedure p "
        "{ "
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "y = 2;"
        "if (x == 1) then {"
        "b = 1;"
        "} else {"
        "c = 1;"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(7)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    auto next_nodes7 = first_cfg.GetNextNodes(node7);
    REQUIRE(next_nodes7.empty());
  }

  SECTION("Extract statements nested if node 2") {
    std::istringstream input(
        "procedure p "
        "{ "
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "if (x == 1) then {"
        "b = 1;"
        "} else {"
        "c = 1;"
        "}"
        "y = 2;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(7)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    auto next_nodes7 = first_cfg.GetNextNodes(node7);
    REQUIRE(next_nodes7.empty());
  }

  SECTION("Extract statements triple nested if node") {
    std::istringstream input(
        "procedure p "
        "{ "
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "if (x == 1) then {"
        "b = 1;"
        "} else {"
        "c = 1;"
        "}"
        "if (b == 1) then {"
        "z = 0;"
        "} else {"
        "c = 0;"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);
    auto node9 = first_cfg.GetNode(9);
    REQUIRE(node9->GetStatementNumber() == 9);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(9)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 2);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(8)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 1);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(9)) !=
            res_nodes7.end());
    auto res_nodes8 = CreateVector(first_cfg.GetNextNodes(node8));
    REQUIRE(res_nodes8.size() == 1);
    REQUIRE(std::find(res_nodes8.begin(), res_nodes8.end(), CFGNode(9)) !=
            res_nodes8.end());
    auto next_nodes9 = first_cfg.GetNextNodes(node9);
    REQUIRE(next_nodes9.empty());
  }

  SECTION("Extract statements triple nested if node 2") {
    std::istringstream input(
        "procedure p "
        "{ "
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "if (x == 1) then {"
        "b = 1;"
        "} else {"
        "if (b == 1) then {"
        "z = 0;"
        "} else {"
        "c = 0;"
        "}"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(8)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(8)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 2);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(8)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 1);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(8)) !=
            res_nodes7.end());
    auto next_nodes8 = first_cfg.GetNextNodes(node8);
    REQUIRE(next_nodes8.empty());
  }

  SECTION("Extract statements triple nested if node 3") {
    std::istringstream input(
        "procedure p "
        "{ "
        "if (z == 1) then {"
        "y = 1;"
        "} else {"
        "if (x == 1) then {"
        "b = 1;"
        "} else {"
        "if (b == 1) then {"
        "z = 0;"
        "} else {"
        "c = 0;"
        "}"
        "}"
        "z = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);
    auto node9 = first_cfg.GetNode(9);
    REQUIRE(node9->GetStatementNumber() == 9);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(9)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(8)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 2);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(8)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 1);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(8)) !=
            res_nodes7.end());
    auto res_nodes8 = CreateVector(first_cfg.GetNextNodes(node8));
    REQUIRE(res_nodes8.size() == 1);
    REQUIRE(std::find(res_nodes8.begin(), res_nodes8.end(), CFGNode(9)) !=
            res_nodes8.end());
    auto next_nodes9 = first_cfg.GetNextNodes(node9);
    REQUIRE(next_nodes9.empty());
  }

  SECTION("Extract statements before while node") {
    std::istringstream input(
        "procedure p "
        "{"
        "s = 1;"
        "while (i == 0) {"
        "x = 1;"
        "}"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 1);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(2)) !=
            res_nodes3.end());
  }

  SECTION("Extract statements after while node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "x = 1;"
        "}"
        "s = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(1)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.empty());
  }

  SECTION("Extract statements before and after while node") {
    std::istringstream input(
        "procedure p "
        "{"
        "x = 1;"
        "x = 2;"
        "while (i == 0) {"
        "x = 1;"
        "x = 2;"
        "}"
        "s = 1;"
        "x = 3;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 1);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(6)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(3)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }

  SECTION("Extract statements nested while node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "x = 1;"
        "while (z == 0) {"
        "x = 1;"
        "}"
        "}"
        "s = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(5)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(1)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(3)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.empty());
  }

  SECTION("Extract statements nested while node 2") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "while (z == 0) {"
        "x = 1;"
        "}"
        "x = 1;"
        "}"
        "s = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(5)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(2)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(1)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.empty());
  }

  SECTION("Extract statements nested triple while node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "while (z == 0) {"
        "while (x == 0) {"
        "x = 1;"
        "}"
        "}"
        "}"
        "s = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(5)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(1)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(2)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(3)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.empty());
  }

  SECTION("Extract statements nested triple while node 2") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "while (z == 0) {"
        "while (x == 0) {"
        "x = 1;"
        "}"
        "s = 1;"
        "}"
        "s = 1;"
        "}"
        "s = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(7)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(6)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(3)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(2)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(1)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }

  SECTION("Extract statements if-while nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "if (i == 0) then {"
        "x = 1;"
        "} else {"
        "while (x == 0) {"
        "x = 2;"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(5)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(3)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.empty());
  }

  SECTION("Extract statements while-if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 2;"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(5)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(1)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(1)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.empty());
  }

  SECTION("Extract statements while-s-if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "x = 1;"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 2;"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(6)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(1)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(1)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
  }
  SECTION("Extract statements while-if-s nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 2;"
        "}"
        "x = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(6)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(1)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
  }

  SECTION("Extract statements while-s-if-s nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "x = 1;"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 2;"
        "}"
        "x = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(7)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(1)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }

  SECTION("Extract statements while-if-if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 1;"
        "}"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(7)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(1)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(1)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(1)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }
  SECTION("Extract statements while-if-if s nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 1;"
        "}"
        "}"
        "z = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(8)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(7)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 1);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(1)) !=
            res_nodes7.end());
    auto res_nodes8 = CreateVector(first_cfg.GetNextNodes(node8));
    REQUIRE(res_nodes8.empty());
  }
  SECTION("Extract statements while-if-if if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 1;"
        "}"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 1;"
        "}"
        "x = 1;"
        "}"
        "z = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);
    auto node9 = first_cfg.GetNode(9);
    REQUIRE(node9->GetStatementNumber() == 9);
    auto node10 = first_cfg.GetNode(10);
    REQUIRE(node10->GetStatementNumber() == 10);
    auto node11 = first_cfg.GetNode(11);
    REQUIRE(node11->GetStatementNumber() == 11);
    auto node12 = first_cfg.GetNode(12);
    REQUIRE(node12->GetStatementNumber() == 12);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(12)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(11)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 2);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(8)) !=
            res_nodes7.end());
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(9)) !=
            res_nodes7.end());
    auto res_nodes8 = CreateVector(first_cfg.GetNextNodes(node8));
    REQUIRE(res_nodes8.size() == 1);
    REQUIRE(std::find(res_nodes8.begin(), res_nodes8.end(), CFGNode(10)) !=
            res_nodes8.end());
    auto res_nodes9 = CreateVector(first_cfg.GetNextNodes(node9));
    REQUIRE(res_nodes9.size() == 1);
    REQUIRE(std::find(res_nodes9.begin(), res_nodes9.end(), CFGNode(10)) !=
            res_nodes9.end());
    auto res_nodes10 = CreateVector(first_cfg.GetNextNodes(node10));
    REQUIRE(res_nodes10.size() == 1);
    REQUIRE(std::find(res_nodes10.begin(), res_nodes10.end(), CFGNode(11)) !=
            res_nodes10.end());
    auto res_nodes11 = CreateVector(first_cfg.GetNextNodes(node11));
    REQUIRE(res_nodes11.size() == 1);
    REQUIRE(std::find(res_nodes11.begin(), res_nodes11.end(), CFGNode(1)) !=
            res_nodes11.end());
    auto res_nodes12 = CreateVector(first_cfg.GetNextNodes(node12));
    REQUIRE(res_nodes12.empty());
  }

  SECTION("Extract statements while-if-while if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "while (x == 0) {"
        "x = 1;"
        "}"
        "if (x == 0) then {"
        "x = 1;"
        "} else {"
        "x = 1;"
        "}"
        "x = 1;"
        "}"
        "z = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);
    auto node8 = first_cfg.GetNode(8);
    REQUIRE(node8->GetStatementNumber() == 8);
    auto node9 = first_cfg.GetNode(9);
    REQUIRE(node9->GetStatementNumber() == 9);
    auto node10 = first_cfg.GetNode(10);
    REQUIRE(node10->GetStatementNumber() == 10);
    auto node11 = first_cfg.GetNode(11);
    REQUIRE(node11->GetStatementNumber() == 11);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(11)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(4)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(10)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(4)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 2);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(7)) !=
            res_nodes6.end());
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(8)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.size() == 1);
    REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode(9)) !=
            res_nodes7.end());
    auto res_nodes8 = CreateVector(first_cfg.GetNextNodes(node8));
    REQUIRE(res_nodes8.size() == 1);
    REQUIRE(std::find(res_nodes8.begin(), res_nodes8.end(), CFGNode(9)) !=
            res_nodes8.end());
    auto res_nodes9 = CreateVector(first_cfg.GetNextNodes(node9));
    REQUIRE(res_nodes9.size() == 1);
    REQUIRE(std::find(res_nodes9.begin(), res_nodes9.end(), CFGNode(10)) !=
            res_nodes9.end());
    auto res_nodes10 = CreateVector(first_cfg.GetNextNodes(node10));
    REQUIRE(res_nodes10.size() == 1);
    REQUIRE(std::find(res_nodes10.begin(), res_nodes10.end(), CFGNode(1)) !=
            res_nodes10.end());
    auto res_nodes11 = CreateVector(first_cfg.GetNextNodes(node11));
    REQUIRE(res_nodes11.empty());
  }
  SECTION("Extract statements if-while-s nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "if (i == 0) then {"
        "x = 1;"
        "} else {"
        "while (x == 0) {"
        "x = 2;"
        "}"
        "z = 1;"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(6)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(3)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
  }
  SECTION("Extract statements if-s-while nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "if (i == 0) then {"
        "x = 1;"
        "} else {"
        "z = 1;"
        "while (x == 0) {"
        "x = 2;"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(6)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(4)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
  }
  SECTION("Extract statements if-if-while nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "if (i == 0) then {"
        "x = 1;"
        "} else {"
        "if (z == 0) then {"
        "x = 0;"
        "} else {"
        "while (x == 0) {"
        "x = 2;"
        "}"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(7)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(7)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 2);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(5)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }

  SECTION("Extract statements if-while-if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "if (i == 0) then {"
        "x = 1;"
        "} else {"
        "while (z == 0) {"
        "if (x == 0) then {"
        "x = 0;"
        "} else {"
        "z = 0;"
        "}"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = first_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(7)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(7)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(6)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(3)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode(3)) !=
            res_nodes6.end());
    auto res_nodes7 = CreateVector(first_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }

  SECTION("Extract statements if-while-while nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "if (i == 0) then {"
        "x = 1;"
        "} else {"
        "while (z == 0) {"
        "while (x == 0) {"
        "x = 0;"
        "}"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(3)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(6)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(6)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(3)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(4)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
  }

  SECTION("Extract statements while-while-if nested node") {
    std::istringstream input(
        "procedure p "
        "{"
        "while (i == 0) {"
        "while (x == 0) {"
        "if (z == 0) then {"
        "x = 1;"
        "} else {"
        "v = 1;"
        "}"
        "}"
        "}"
        "z = 1;"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = first_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = first_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = first_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(6)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 2);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(1)) !=
            res_nodes2.end());
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 2);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(4)) !=
            res_nodes3.end());
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(5)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(first_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(2)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(first_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(2)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(first_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
  }

  SECTION("Extract multiple procedures") {
    std::istringstream input(
        "procedure p "
        "{"
        "z = 1;"
        "while (i == 0) {"
        "x = 1;"
        "}"
        "}"
        "procedure x"
        "{"
        "b = 1;"
        "if (m == 0) then {"
        "p = 1;"
        "} else {"
        "y = 1;"
        "}"
        "}");
    std::vector<Token> tokens = lexer.Execute(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res = cfg_extractor_under_test.Extract(ast);

    REQUIRE(res.size() == 2);
    CFG first_cfg = res[0];
    CFG second_cfg = res[1];

    // Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    REQUIRE(node1->GetStatementNumber() == 1);
    auto node2 = first_cfg.GetNode(2);
    REQUIRE(node2->GetStatementNumber() == 2);
    auto node3 = first_cfg.GetNode(3);
    REQUIRE(node3->GetStatementNumber() == 3);
    auto node4 = second_cfg.GetNode(4);
    REQUIRE(node4->GetStatementNumber() == 4);
    auto node5 = second_cfg.GetNode(5);
    REQUIRE(node5->GetStatementNumber() == 5);
    auto node6 = second_cfg.GetNode(6);
    REQUIRE(node6->GetStatementNumber() == 6);
    auto node7 = second_cfg.GetNode(7);
    REQUIRE(node7->GetStatementNumber() == 7);

    // Compare each next CFGNode
    auto res_nodes1 = CreateVector(first_cfg.GetNextNodes(node1));
    REQUIRE(res_nodes1.size() == 1);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode(2)) !=
            res_nodes1.end());
    auto res_nodes2 = CreateVector(first_cfg.GetNextNodes(node2));
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode(3)) !=
            res_nodes2.end());
    auto res_nodes3 = CreateVector(first_cfg.GetNextNodes(node3));
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode(2)) !=
            res_nodes3.end());
    auto res_nodes4 = CreateVector(second_cfg.GetNextNodes(node4));
    REQUIRE(res_nodes4.size() == 1);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode(5)) !=
            res_nodes4.end());
    auto res_nodes5 = CreateVector(second_cfg.GetNextNodes(node5));
    REQUIRE(res_nodes5.size() == 2);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(6)) !=
            res_nodes5.end());
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode(7)) !=
            res_nodes5.end());
    auto res_nodes6 = CreateVector(second_cfg.GetNextNodes(node6));
    REQUIRE(res_nodes6.empty());
    auto res_nodes7 = CreateVector(second_cfg.GetNextNodes(node7));
    REQUIRE(res_nodes7.empty());
  }
}