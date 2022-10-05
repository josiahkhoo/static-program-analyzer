#include "catch.hpp"
#include "fakeit.hpp"
#include "sp/extractor/cfg_extractor_impl.h"
#include "common/lexer.h"
#include "sp/simple_parser.h"

#include <algorithm>

using namespace fakeit;

TEST_CASE("CFG Extractor", "[CFGExtractor]") {
  CFGExtractorImpl cfg_extractor_under_test = CFGExtractorImpl();
  SimpleParser parser;
  Lexer lexer;
//  SECTION("Extract 1-depth node") {
//    std::string input = "procedure p { m = x * y + z / 100; x = x + 1;}";
//    std::vector<Token> tokens = lexer.LexLine(input);
//    tokens.emplace_back(Token::END);
//    auto ast = parser.Parse(tokens);
//    std::vector<CFG> res =
//        cfg_extractor_under_test.Extract(ast);
//    CFG first_cfg = res[0];
//
//    // Compare statement numbers for each node
//    auto node1 = first_cfg.GetNode(1);
//    std::vector<int> v = {1, 2};
//    REQUIRE(node1->GetStatementNumbers() == v);
//
//    // Compare each next CFG
//    auto next_nodes1 = first_cfg.GetNextNodes(node1);
//    REQUIRE(next_nodes1.empty());
//  }
//
//  SECTION("Extract if node") {
//    std::string input = "procedure p "
//        "{ "
//          "a = 1;"
//          "x = 1;"
//          "if (z == 1) then {"
//            "y = 1;"
//          "} else {"
//            "y = 2;"
//          "}"
//        "}";
//    std::vector<Token> tokens = lexer.LexLine(input);
//    tokens.emplace_back(Token::END);
//    auto ast = parser.Parse(tokens);
//    std::vector<CFG> res =
//        cfg_extractor_under_test.Extract(ast);
//    CFG first_cfg = res[0];
//
//    // Compare statement numbers for each node
//    auto node1 = first_cfg.GetNode(1);
//    std::vector<int> v1 = {1, 2};
//    REQUIRE(node1->GetStatementNumbers() == v1);
//    auto node2 = first_cfg.GetNode(3);
//    std::vector<int> v2 = {3};
//    REQUIRE(node2->GetStatementNumbers() == v2);
//    auto node3 = first_cfg.GetNode(4);
//    std::vector<int> v3 = {4};
//    REQUIRE(node3->GetStatementNumbers() == v3);
//    auto node4 = first_cfg.GetNode(5);
//    std::vector<int> v4 = {5};
//    REQUIRE(node4->GetStatementNumbers() == v4);
//
//    // Compare each next CFGNode
//    auto next_nodes1 = first_cfg.GetNextNodes(node1);
//    std::vector<CFGNode> res_nodes1;
//    for (auto & node : next_nodes1) {
//      res_nodes1.emplace_back(*node);
//    }
//    std::vector<CFGNode> test_nodes1 = {CFGNode({3})};
//    REQUIRE(res_nodes1 == test_nodes1);
//
//    auto next_nodes2 = first_cfg.GetNextNodes(node2);
//    std::vector<CFGNode> res_nodes2;
//    for (auto & node : next_nodes2) {
//      res_nodes2.emplace_back(*node);
//    }
//    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({4})) != res_nodes2.end());
//    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({5})) != res_nodes2.end());
//
//    auto next_nodes3 = first_cfg.GetNextNodes(node3);
//    REQUIRE(next_nodes3.empty());
//
//    auto next_nodes4 = first_cfg.GetNextNodes(node4);
//    REQUIRE(next_nodes4.empty());
//  }
//
//  SECTION("Extract starting if node") {
//    std::string input = "procedure p "
//        "{ "
//        "if (z == 1) then {"
//        "y = 1;"
//        "} else {"
//        "y = 2;"
//        "}"
//        "z = 1;"
//        "x = 1;"
//        "}";
//    std::vector<Token> tokens = lexer.LexLine(input);
//    tokens.emplace_back(Token::END);
//    auto ast = parser.Parse(tokens);
//    std::vector<CFG> res =
//        cfg_extractor_under_test.Extract(ast);
//    CFG first_cfg = res[0];
//
//    // Compare statement numbers for each node
//    auto node1 = first_cfg.GetNode(1);
//    std::vector<int> v1 = {1};
//    REQUIRE(node1->GetStatementNumbers() == v1);
//    auto node2 = first_cfg.GetNode(2);
//    std::vector<int> v2 = {2};
//    REQUIRE(node2->GetStatementNumbers() == v2);
//    auto node3 = first_cfg.GetNode(3);
//    std::vector<int> v3 = {3};
//    REQUIRE(node3->GetStatementNumbers() == v3);
//    auto node4 = first_cfg.GetNode(4);
//    std::vector<int> v4 = {4, 5};
//    REQUIRE(node4->GetStatementNumbers() == v4);
//
//    // Compare each next CFGNode
//    auto next_nodes1 = first_cfg.GetNextNodes(node1);
//    std::vector<CFGNode> res_nodes1;
//    for (auto & node : next_nodes1) {
//      res_nodes1.emplace_back(*node);
//    }
//    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({2})) != res_nodes1.end());
//    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({3})) != res_nodes1.end());
//
//    auto next_nodes2 = first_cfg.GetNextNodes(node2);
//    std::vector<CFGNode> res_nodes2;
//    for (auto & node : next_nodes2) {
//      res_nodes2.emplace_back(*node);
//    }
//    std::vector<CFGNode> test_nodes2 = {CFGNode({4, 5})};
//    REQUIRE(res_nodes2 == test_nodes2);
//
//    auto next_nodes3 = first_cfg.GetNextNodes(node3);
//    std::vector<CFGNode> res_nodes3;
//    for (auto & node : next_nodes3) {
//      res_nodes3.emplace_back(*node);
//    }
//    std::vector<CFGNode> test_nodes3 = {CFGNode({4, 5})};
//    REQUIRE(res_nodes3 == test_nodes3);
//
//    auto next_nodes4 = first_cfg.GetNextNodes(node4);
//    REQUIRE(next_nodes4.empty());
//  }
//
//  SECTION("Extract statements before and after if node") {
//    std::string input = "procedure p "
//        "{ "
//        "s = 1;"
//        "z = 1;"
//        "if (z == 1) then {"
//        "y = 1;"
//        "z = 1;"
//        "} else {"
//        "y = 2;"
//        "l = 1;"
//        "}"
//        "z = 1;"
//        "x = 1;"
//        "}";
//    std::vector<Token> tokens = lexer.LexLine(input);
//    tokens.emplace_back(Token::END);
//    auto ast = parser.Parse(tokens);
//    std::vector<CFG> res =
//        cfg_extractor_under_test.Extract(ast);
//    CFG first_cfg = res[0];
//
//    // Compare statement numbers for each node
//    auto node1 = first_cfg.GetNode(1);
//    std::vector<int> v1 = {1, 2};
//    REQUIRE(node1->GetStatementNumbers() == v1);
//    auto node2 = first_cfg.GetNode(3);
//    std::vector<int> v2 = {3};
//    REQUIRE(node2->GetStatementNumbers() == v2);
//    auto node3 = first_cfg.GetNode(5);
//    std::vector<int> v3 = {4, 5};
//    REQUIRE(node3->GetStatementNumbers() == v3);
//    auto node4 = first_cfg.GetNode(6);
//    std::vector<int> v4 = {6, 7};
//    REQUIRE(node4->GetStatementNumbers() == v4);
//    auto node5 = first_cfg.GetNode(9);
//    std::vector<int> v5 = {8, 9};
//    REQUIRE(node5->GetStatementNumbers() == v5);
//
//    // Compare each next CFGNode
//    auto next_nodes1 = first_cfg.GetNextNodes(node1);
//    std::vector<CFGNode> res_nodes1;
//    for (auto & node : next_nodes1) {
//      res_nodes1.emplace_back(*node);
//    }
//    REQUIRE(res_nodes1.size() == 1);
//    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({3})) != res_nodes1.end());
//
//    auto next_nodes2 = first_cfg.GetNextNodes(node2);
//    std::vector<CFGNode> res_nodes2;
//    for (auto & node : next_nodes2) {
//      res_nodes2.emplace_back(*node);
//    }
//    REQUIRE(res_nodes2.size() == 2);
//    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({4, 5})) != res_nodes2.end());
//    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({6, 7})) != res_nodes2.end());
//
//    auto next_nodes3 = first_cfg.GetNextNodes(node3);
//    std::vector<CFGNode> res_nodes3;
//    for (auto & node : next_nodes3) {
//      res_nodes3.emplace_back(*node);
//    }
//    REQUIRE(res_nodes3.size() == 1);
//    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode({8, 9})) != res_nodes3.end());
//
//    auto next_nodes4 = first_cfg.GetNextNodes(node4);
//    std::vector<CFGNode> res_nodes4;
//    for (auto & node : next_nodes4) {
//      res_nodes4.emplace_back(*node);
//    }
//    REQUIRE(res_nodes4.size() == 1);
//    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode({8, 9})) != res_nodes4.end());
//
//    auto next_nodes5 = first_cfg.GetNextNodes(node5);
//    REQUIRE(next_nodes5.empty());
//  }
//
  SECTION("Extract statements before and after if node") {
    std::string input = "procedure p "
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
        "}";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    auto ast = parser.Parse(tokens);
    std::vector<CFG> res =
        cfg_extractor_under_test.Extract(ast);
    CFG first_cfg = res[0];

    //Compare statement numbers for each node
    auto node1 = first_cfg.GetNode(1);
    std::vector<int> v1 = {1};
    REQUIRE(node1->GetStatementNumbers() == v1);
    auto node2 = first_cfg.GetNode(2);
    std::vector<int> v2 = {2};
    REQUIRE(node2->GetStatementNumbers() == v2);
    auto node3 = first_cfg.GetNode(3);
    std::vector<int> v3 = {3};
    REQUIRE(node3->GetStatementNumbers() == v3);
    auto node4 = first_cfg.GetNode(4);
    std::vector<int> v4 = {4};
    REQUIRE(node4->GetStatementNumbers() == v4);
    auto node5 = first_cfg.GetNode(5);
    std::vector<int> v5 = {5};
    REQUIRE(node5->GetStatementNumbers() == v5);
    auto node6 = first_cfg.GetNode(6);
    std::vector<int> v6 = {6};
    REQUIRE(node6->GetStatementNumbers() == v6);
    auto node7 = first_cfg.GetNode(7);
    std::vector<int> v7 = {7};
    REQUIRE(node7->GetStatementNumbers() == v7);

    // Compare each next CFGNode
    auto next_nodes1 = first_cfg.GetNextNodes(node1);
    std::vector<CFGNode> res_nodes1;
    for (auto & node : next_nodes1) {
      res_nodes1.emplace_back(*node);
    }
    REQUIRE(res_nodes1.size() == 2);
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({2})) != res_nodes1.end());
    REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({3})) != res_nodes1.end());

    auto next_nodes2 = first_cfg.GetNextNodes(node2);
    std::vector<CFGNode> res_nodes2;
    for (auto & node : next_nodes2) {
      res_nodes2.emplace_back(*node);
    }
    REQUIRE(res_nodes2.size() == 1);
    REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({7})) != res_nodes2.end());

    auto next_nodes3 = first_cfg.GetNextNodes(node3);
    std::vector<CFGNode> res_nodes3;
    for (auto & node : next_nodes3) {
      res_nodes3.emplace_back(*node);
    }
    REQUIRE(res_nodes3.size() == 1);
    REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode({4})) != res_nodes3.end());

    auto next_nodes4 = first_cfg.GetNextNodes(node4);
    std::vector<CFGNode> res_nodes4;
    for (auto & node : next_nodes4) {
      res_nodes4.emplace_back(*node);
    }
    REQUIRE(res_nodes4.size() == 2);
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode({5})) != res_nodes4.end());
    REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode({6})) != res_nodes4.end());

    auto next_nodes5 = first_cfg.GetNextNodes(node5);
    std::vector<CFGNode> res_nodes5;
    for (auto & node : next_nodes5) {
      res_nodes5.emplace_back(*node);
    }
    REQUIRE(res_nodes5.size() == 1);
    REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode({7})) != res_nodes5.end());

    auto next_nodes6 = first_cfg.GetNextNodes(node6);
    std::vector<CFGNode> res_nodes6;
    for (auto & node : next_nodes6) {
      res_nodes6.emplace_back(*node);
    }
    REQUIRE(res_nodes6.size() == 1);
    REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode({7})) != res_nodes6.end());

    auto next_nodes7 = first_cfg.GetNextNodes(node7);
    REQUIRE(next_nodes7.empty());
   }

   SECTION("Extract statements before and after if node") {
     std::string input = "procedure p "
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
         "}";
     std::vector<Token> tokens = lexer.LexLine(input);
     tokens.emplace_back(Token::END);
     auto ast = parser.Parse(tokens);
     std::vector<CFG> res =
         cfg_extractor_under_test.Extract(ast);
     CFG first_cfg = res[0];

     //Compare statement numbers for each node
     auto node1 = first_cfg.GetNode(1);
     std::vector<int> v1 = {1};
     REQUIRE(node1->GetStatementNumbers() == v1);
     auto node2 = first_cfg.GetNode(2);
     std::vector<int> v2 = {2};
     REQUIRE(node2->GetStatementNumbers() == v2);
     auto node3 = first_cfg.GetNode(3);
     std::vector<int> v3 = {3};
     REQUIRE(node3->GetStatementNumbers() == v3);
     auto node4 = first_cfg.GetNode(4);
     std::vector<int> v4 = {4};
     REQUIRE(node4->GetStatementNumbers() == v4);
     auto node5 = first_cfg.GetNode(5);
     std::vector<int> v5 = {5};
     REQUIRE(node5->GetStatementNumbers() == v5);
     auto node6 = first_cfg.GetNode(6);
     std::vector<int> v6 = {6};
     REQUIRE(node6->GetStatementNumbers() == v6);
     auto node7 = first_cfg.GetNode(7);
     std::vector<int> v7 = {7};
     REQUIRE(node7->GetStatementNumbers() == v7);

     // Compare each next CFGNode
     auto next_nodes1 = first_cfg.GetNextNodes(node1);
     std::vector<CFGNode> res_nodes1;
     for (auto & node : next_nodes1) {
       res_nodes1.emplace_back(*node);
     }
     REQUIRE(res_nodes1.size() == 2);
     REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({2})) != res_nodes1.end());
     REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({3})) != res_nodes1.end());

     auto next_nodes2 = first_cfg.GetNextNodes(node2);
     std::vector<CFGNode> res_nodes2;
     for (auto & node : next_nodes2) {
       res_nodes2.emplace_back(*node);
     }
     REQUIRE(res_nodes2.size() == 1);
     REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({7})) != res_nodes2.end());

     auto next_nodes3 = first_cfg.GetNextNodes(node3);
     std::vector<CFGNode> res_nodes3;
     for (auto & node : next_nodes3) {
       res_nodes3.emplace_back(*node);
     }
     REQUIRE(res_nodes3.size() == 2);
     REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode({4})) != res_nodes3.end());
     REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode({5})) != res_nodes3.end());

     auto next_nodes4 = first_cfg.GetNextNodes(node4);
     std::vector<CFGNode> res_nodes4;
     for (auto & node : next_nodes4) {
       res_nodes4.emplace_back(*node);
     }
     REQUIRE(res_nodes4.size() == 1);
     REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode({6})) != res_nodes4.end());

     auto next_nodes5 = first_cfg.GetNextNodes(node5);
     std::vector<CFGNode> res_nodes5;
     for (auto & node : next_nodes5) {
       res_nodes5.emplace_back(*node);
     }
     REQUIRE(res_nodes5.size() == 1);
     REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode({6})) != res_nodes5.end());

     auto next_nodes6 = first_cfg.GetNextNodes(node6);
     std::vector<CFGNode> res_nodes6;
     for (auto & node : next_nodes6) {
       res_nodes6.emplace_back(*node);
     }
     REQUIRE(res_nodes6.size() == 1);
     REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode({7})) != res_nodes6.end());

     auto next_nodes7 = first_cfg.GetNextNodes(node7);
     REQUIRE(next_nodes7.empty());
   }

//   SECTION("Extract statements before and after if node") {
//     std::string input = "procedure p "
//         "{ "
//         "if (z == 1) then {"
//         "y = 1;"
//         "} else {"
//         "if (x == 1) then {"
//         "b = 1;"
//         "} else {"
//         "c = 1;"
//         "}"
//         "if (b == 1) then {"
//         "z == 0;"
//         "} else {"
//         "c == 0;"
//         "}"
//         "}"
//         "z = 1;"
//         "}";
//     std::vector<Token> tokens = lexer.LexLine(input);
//     tokens.emplace_back(Token::END);
//     auto ast = parser.Parse(tokens);
//     std::vector<CFG> res =
//         cfg_extractor_under_test.Extract(ast);
     //CFG first_cfg = res[0];

     //Compare statement numbers for each node
//     auto node1 = first_cfg.GetNode(1);
//     std::vector<int> v1 = {1};
//     REQUIRE(node1->GetStatementNumbers() == v1);
//     auto node2 = first_cfg.GetNode(2);
//     std::vector<int> v2 = {2};
//     REQUIRE(node2->GetStatementNumbers() == v2);
//     auto node3 = first_cfg.GetNode(3);
//     std::vector<int> v3 = {3};
//     REQUIRE(node3->GetStatementNumbers() == v3);
//     auto node4 = first_cfg.GetNode(4);
//     std::vector<int> v4 = {4};
//     REQUIRE(node4->GetStatementNumbers() == v4);
//     auto node5 = first_cfg.GetNode(5);
//     std::vector<int> v5 = {5};
//     REQUIRE(node5->GetStatementNumbers() == v5);
//     auto node6 = first_cfg.GetNode(6);
//     std::vector<int> v6 = {6};
//     REQUIRE(node6->GetStatementNumbers() == v6);
//     auto node7 = first_cfg.GetNode(7);
//     std::vector<int> v7 = {7};
//     REQUIRE(node7->GetStatementNumbers() == v7);
//     auto node8 = first_cfg.GetNode(8);
//     std::vector<int> v8 = {8};
//     REQUIRE(node8->GetStatementNumbers() == v8);
//     auto node9 = first_cfg.GetNode(9);
//     std::vector<int> v9 = {9};
//     REQUIRE(node9->GetStatementNumbers() == v9);

//     // Compare each next CFGNode
//     auto next_nodes1 = first_cfg.GetNextNodes(node1);
//     std::vector<CFGNode> res_nodes1;
//     for (auto & node : next_nodes1) {
//       res_nodes1.emplace_back(*node);
//     }
//     REQUIRE(res_nodes1.size() == 2);
//     REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({2})) != res_nodes1.end());
//     REQUIRE(std::find(res_nodes1.begin(), res_nodes1.end(), CFGNode({3})) != res_nodes1.end());
//
//     auto next_nodes2 = first_cfg.GetNextNodes(node2);
//     std::vector<CFGNode> res_nodes2;
//     for (auto & node : next_nodes2) {
//       res_nodes2.emplace_back(*node);
//     }
//     REQUIRE(res_nodes2.size() == 1);
//     REQUIRE(std::find(res_nodes2.begin(), res_nodes2.end(), CFGNode({7})) != res_nodes2.end());
//
//     auto next_nodes3 = first_cfg.GetNextNodes(node3);
//     std::vector<CFGNode> res_nodes3;
//     for (auto & node : next_nodes3) {
//       res_nodes3.emplace_back(*node);
//     }
//     REQUIRE(res_nodes3.size() == 2);
//     REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode({4})) != res_nodes3.end());
//     REQUIRE(std::find(res_nodes3.begin(), res_nodes3.end(), CFGNode({5})) != res_nodes3.end());
//
//     auto next_nodes4 = first_cfg.GetNextNodes(node4);
//     std::vector<CFGNode> res_nodes4;
//     for (auto & node : next_nodes4) {
//       res_nodes4.emplace_back(*node);
//     }
//     REQUIRE(res_nodes4.size() == 1);
//     REQUIRE(std::find(res_nodes4.begin(), res_nodes4.end(), CFGNode({6})) != res_nodes4.end());
//
//     auto next_nodes5 = first_cfg.GetNextNodes(node5);
//     std::vector<CFGNode> res_nodes5;
//     for (auto & node : next_nodes5) {
//       res_nodes5.emplace_back(*node);
//     }
//     REQUIRE(res_nodes5.size() == 1);
//     REQUIRE(std::find(res_nodes5.begin(), res_nodes5.end(), CFGNode({6})) != res_nodes5.end());
//
//     auto next_nodes6 = first_cfg.GetNextNodes(node6);
//     std::vector<CFGNode> res_nodes6;
//     for (auto & node : next_nodes6) {
//       res_nodes6.emplace_back(*node);
//     }
//     REQUIRE(res_nodes6.size() == 2);
//     REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode({7})) != res_nodes6.end());
//     REQUIRE(std::find(res_nodes6.begin(), res_nodes6.end(), CFGNode({8})) != res_nodes6.end());
//
//     auto next_nodes7 = first_cfg.GetNextNodes(node7);
//     std::vector<CFGNode> res_nodes7;
//     for (auto & node : next_nodes7) {
//       res_nodes7.emplace_back(*node);
//     }
//     REQUIRE(res_nodes7.size() == 1);
//     REQUIRE(std::find(res_nodes7.begin(), res_nodes7.end(), CFGNode({9})) != res_nodes7.end());
//
//     auto next_nodes8 = first_cfg.GetNextNodes(node8);
//     std::vector<CFGNode> res_nodes8;
//     for (auto & node : next_nodes8) {
//       res_nodes8.emplace_back(*node);
//     }
//     REQUIRE(res_nodes8.size() == 1);
//     REQUIRE(std::find(res_nodes8.begin(), res_nodes8.end(), CFGNode({9})) != res_nodes8.end());
//
//     auto next_nodes9 = first_cfg.GetNextNodes(node9);
//     REQUIRE(next_nodes9.empty());
   //}




//  SECTION("Extract 1-depth node") {
//    std::string input = "procedure p "
//        "{ "
//          "if (x == 0) then {"
//            "m = 100; "
//          "} else {"
//            "while (i != 0) {"
//              "z = z + 1;"
//            "}"
//            "c = c + 1;"
//          "}"
//          "b = b + 1;"
//        "}";
//    std::vector<Token> tokens = lexer.LexLine(input);
//    tokens.emplace_back(Token::END);
//    auto ast = parser.Parse(tokens);
//    std::vector<CFG> res =
//        cfg_extractor_under_test.Extract(ast);
//    CFG first_cfg = res[0];
//
//    // Compare statement numbers for each node
//    auto node1 = first_cfg.GetNode(1);
//    std::vector<int> v = {1};
//    REQUIRE(node1->GetStatementNumbers() == v);
//
//    // Compare each next CFGNode
//    auto next_nodes1 = first_cfg.GetNextNodes(node1);
//    REQUIRE(next_nodes1.empty());
//  }
}