#ifndef SPA_ENTITY_EXTRACTOR_IMPL_H
#define SPA_ENTITY_EXTRACTOR_IMPL_H

#include "entity_extractor.h"
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

class EntityExtractorImpl : public EntityExtractor {
 public:
  EntityExtractorImpl(
      const NodeExtractor<AssignEntity> &assign_entity_node_extractor,
      const NodeExtractor<CallEntity> &call_entity_node_extractor,
      const NodeExtractor<ConstantEntity> &constant_entity_node_extractor,
      const NodeExtractor<IfEntity> &if_entity_node_extractor,
      const NodeExtractor<PrintEntity> &print_entity_node_extractor,
      const NodeExtractor<ProcedureEntity> &procedure_entity_node_extractor,
      const NodeExtractor<ReadEntity> &read_entity_node_extractor,
      const NodeExtractor<StatementEntity> &statement_entity_node_extractor,
      const NodeExtractor<VariableEntity> &variable_entity_node_extractor,
      const NodeExtractor<WhileEntity> &while_entity_node_extractor);

  [[nodiscard]] EntityExtractorResult Extract(const TNode &ast) const override;

 private:
  // Extractors
  const NodeExtractor<AssignEntity> &assign_entity_node_extractor_;
  const NodeExtractor<CallEntity> &call_entity_node_extractor_;
  const NodeExtractor<ConstantEntity> &constant_entity_node_extractor_;
  const NodeExtractor<IfEntity> &if_entity_node_extractor_;
  const NodeExtractor<PrintEntity> &print_entity_node_extractor_;
  const NodeExtractor<ProcedureEntity> &procedure_entity_node_extractor_;
  const NodeExtractor<ReadEntity> &read_entity_node_extractor_;
  const NodeExtractor<StatementEntity> &statement_entity_node_extractor_;
  const NodeExtractor<VariableEntity> &variable_entity_node_extractor_;
  const NodeExtractor<WhileEntity> &while_entity_node_extractor_;

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

#endif  // SPA_ENTITY_EXTRACTOR_IMPL_H
