#pragma once

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include "common/queryable_pkb.h"
#include "common/storable_pkb.h"

typedef short PROC;

class t_node;

class VarTable; // no need to #include "VarTable.h" as all I need is pointer

class PKB : public QueryablePkb, public StorablePkb {
public:
  static VarTable *varTable;
  static int setProcToAST(PROC p, t_node *r);
  static t_node *getRootAST(PROC p);
};