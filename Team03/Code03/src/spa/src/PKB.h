#pragma once

#include "queryable_pkb.h"
#include "storable_pkb.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

typedef short PROC;

class TNode;

class VarTable; // no need to #include "VarTable.h" as all I need is pointer

class PKB : public QueryablePkb, public StorablePkb {
public:
  static VarTable *varTable;
  static int setProcToAST(PROC p, TNode *r);
  static TNode *getRootAST(PROC p);
};