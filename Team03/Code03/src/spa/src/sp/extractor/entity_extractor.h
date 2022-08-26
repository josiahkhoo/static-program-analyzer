#ifndef SPA_ENTITY_EXTRACTOR_H
#define SPA_ENTITY_EXTRACTOR_H

#include "entity_extractor_result.h"
#include "sp/extractor/entity/assign_entity_node_extractor.h"
#include "sp/extractor/entity/call_entity_node_extractor.h"
#include "sp/extractor/entity/constant_entity_node_extractor.h"
#include "sp/extractor/entity/if_entity_node_extractor.h"
#include "sp/extractor/entity/print_entity_node_extractor.h"
#include "sp/extractor/entity/procedure_entity_node_extractor.h"
#include "sp/extractor/entity/read_entity_node_extractor.h"
#include "sp/extractor/entity/statement_entity_node_extractor.h"
#include "sp/extractor/entity/variable_entity_node_extractor.h"
#include "sp/extractor/entity/while_entity_node_extractor.h"

class EntityExtractor {
 public:
  EntityExtractor(
      const AssignEntityNodeExtractor &assign_entity_node_extractor,
      const CallEntityNodeExtractor &call_entity_node_extractor,
      const ConstantEntityNodeExtractor &constant_entity_node_extractor,
      const IfEntityNodeExtractor &if_entity_node_extractor,
      const PrintEntityNodeExtractor &print_entity_node_extractor,
      const ProcedureEntityNodeExtractor &procedure_entity_node_extractor,
      const ReadEntityNodeExtractor &read_entity_node_extractor,
      const StatementEntityNodeExtractor &statement_entity_node_extractor,
      const VariableEntityNodeExtractor &variable_entity_node_extractor,
      const WhileEntityNodeExtractor &while_entity_node_extractor);

  EntityExtractorResult Extract(const TNode &ast) const;

 private:
  // Extractors
  const AssignEntityNodeExtractor &assign_entity_node_extractor_;
  const CallEntityNodeExtractor &call_entity_node_extractor_;
  const ConstantEntityNodeExtractor &constant_entity_node_extractor_;
  const IfEntityNodeExtractor &if_entity_node_extractor_;
  const PrintEntityNodeExtractor &print_entity_node_extractor_;
  const ProcedureEntityNodeExtractor &procedure_entity_node_extractor_;
  const ReadEntityNodeExtractor &read_entity_node_extractor_;
  const StatementEntityNodeExtractor &statement_entity_node_extractor_;
  const VariableEntityNodeExtractor &variable_entity_node_extractor_;
  const WhileEntityNodeExtractor &while_entity_node_extractor_;

  void ExtractNode(const TNode &node,
                   std::vector<AssignEntity> *assign_entities,
                   std::vector<CallEntity> *call_entities,
                   std::vector<ConstantEntity> *constant_entities,
                   std::vector<IfEntity> *if_entities,
                   std::vector<PrintEntity> *print_entities,
                   std::vector<ProcedureEntity> *procedure_entities,
                   std::vector<ReadEntity> *read_entities,
                   std::vector<StatementEntity> *statement_entities,
                   std::vector<VariableEntity> *variable_entities,
                   std::vector<WhileEntity> *while_entities) const;

  void RecursivelyExtractNode(const TNode &node,
                              std::vector<AssignEntity> *assign_entities,
                              std::vector<CallEntity> *call_entities,
                              std::vector<ConstantEntity> *constant_entities,
                              std::vector<IfEntity> *if_entities,
                              std::vector<PrintEntity> *print_entities,
                              std::vector<ProcedureEntity> *procedure_entities,
                              std::vector<ReadEntity> *read_entities,
                              std::vector<StatementEntity> *statement_entities,
                              std::vector<VariableEntity> *variable_entities,
                              std::vector<WhileEntity> *while_entities) const;
};

#endif  // SPA_ENTITY_EXTRACTOR_H
