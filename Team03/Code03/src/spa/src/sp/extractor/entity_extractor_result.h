#ifndef SPA_ENTITY_EXTRACTOR_RESULT_H
#define SPA_ENTITY_EXTRACTOR_RESULT_H

#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/while_entity.h"
#include "vector"

class EntityExtractorResult {
 public:
  EntityExtractorResult(std::vector<AssignEntity> assign_entities,
                        std::vector<CallEntity> call_entities,
                        std::vector<ConstantEntity> constant_entities,
                        std::vector<IfEntity> if_entities,
                        std::vector<PrintEntity> print_entities,
                        std::vector<ProcedureEntity> procedure_entities,
                        std::vector<ReadEntity> read_entities,
                        std::vector<StatementEntity> statement_entities,
                        std::vector<VariableEntity> variable_entities,
                        std::vector<WhileEntity> while_entities);

  [[nodiscard]] std::vector<AssignEntity> GetAssignEntities() const;

  [[nodiscard]] std::vector<CallEntity> GetCallEntities() const;

  [[nodiscard]] std::vector<ConstantEntity> GetConstantEntities() const;

  [[nodiscard]] std::vector<IfEntity> GetIfEntities() const;

  [[nodiscard]] std::vector<PrintEntity> GetPrintEntities() const;

  [[nodiscard]] std::vector<ProcedureEntity> GetProcedureEntities() const;

  [[nodiscard]] std::vector<ReadEntity> GetReadEntities() const;

  [[nodiscard]] std::vector<StatementEntity> GetStatementEntities() const;

  [[nodiscard]] std::vector<VariableEntity> GetVariableEntities() const;

  [[nodiscard]] std::vector<WhileEntity> GetWhileEntities() const;

  bool operator==(const EntityExtractorResult &rhs) const;

  bool operator!=(const EntityExtractorResult &rhs) const;

  class Builder {
   public:
    Builder();
    Builder AssignEntities(std::vector<AssignEntity> *assign_entities);
    Builder CallEntities(std::vector<CallEntity> *call_entities);
    Builder ConstantEntities(std::vector<ConstantEntity> *constant_entities);
    Builder IfEntities(std::vector<IfEntity> *if_entities);
    Builder PrintEntities(std::vector<PrintEntity> *print_entities);
    Builder ProcedureEntities(std::vector<ProcedureEntity> *procedure_entities);
    Builder ReadEntities(std::vector<ReadEntity> *read_entities);
    Builder StatementEntities(std::vector<StatementEntity> *statement_entities);
    Builder VariableEntities(std::vector<VariableEntity> *variable_entities);
    Builder WhileEntities(std::vector<WhileEntity> *while_entities);
    EntityExtractorResult Build();

   private:
    std::vector<AssignEntity> *assign_entities_{};
    std::vector<CallEntity> *call_entities_{};
    std::vector<ConstantEntity> *constant_entities_{};
    std::vector<IfEntity> *if_entities_{};
    std::vector<PrintEntity> *print_entities_{};
    std::vector<ProcedureEntity> *procedure_entities_{};
    std::vector<ReadEntity> *read_entities_{};
    std::vector<StatementEntity> *statement_entities_{};
    std::vector<VariableEntity> *variable_entities_{};
    std::vector<WhileEntity> *while_entities_{};
  };

 private:
  std::vector<AssignEntity> assign_entities_;
  std::vector<CallEntity> call_entities_;
  std::vector<ConstantEntity> constant_entities_;
  std::vector<IfEntity> if_entities_;
  std::vector<PrintEntity> print_entities_;
  std::vector<ProcedureEntity> procedure_entities_;
  std::vector<ReadEntity> read_entities_;
  std::vector<StatementEntity> statement_entities_;
  std::vector<VariableEntity> variable_entities_;
  std::vector<WhileEntity> while_entities_;
};

#endif  // SPA_ENTITY_EXTRACTOR_RESULT_H
