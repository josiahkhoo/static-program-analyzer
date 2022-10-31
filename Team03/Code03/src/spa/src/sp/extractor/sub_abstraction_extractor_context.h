#ifndef SPA_SUB_ABSTRACTION_EXTRACTOR_CONTEXT_H_
#define SPA_SUB_ABSTRACTION_EXTRACTOR_CONTEXT_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"
#include "common/entity/while_entity.h"
#include "common/t_node.h"

class SubAbstractionExtractorContext {
 public:
  SubAbstractionExtractorContext(
      const std::vector<AssignEntity> &assign_entities,
      const std::vector<CallEntity> &call_entities,
      const std::vector<ConstantEntity> &constant_entities,
      const std::vector<IfEntity> &if_entities,
      const std::vector<PrintEntity> &print_entities,
      const std::vector<ProcedureEntity> &procedure_entities,
      const std::vector<ReadEntity> &read_entities,
      const std::vector<StatementEntity> &statement_entities,
      const std::vector<VariableEntity> &variable_entities,
      const std::vector<WhileEntity> &while_entities,
      std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap,
      std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap,
      std::unordered_map<TNode, ConstantEntity> &t_node_const_ent_umap,
      std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap,
      std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
          &proc_node_call_ent_umap,
      std::unordered_map<std::string, const TNode *> &proc_name_node_umap);

  [[nodiscard]] const std::vector<AssignEntity> &GetAssignEntities() const;
  [[nodiscard]] const std::vector<CallEntity> &GetCallEntities() const;
  [[nodiscard]] const std::vector<ConstantEntity> &GetConstantEntities() const;
  [[nodiscard]] const std::vector<IfEntity> &GetIfEntities() const;
  [[nodiscard]] const std::vector<PrintEntity> &GetPrintEntities() const;
  [[nodiscard]] const std::vector<ProcedureEntity> &GetProcedureEntities()
      const;
  [[nodiscard]] const std::vector<ReadEntity> &GetReadEntities() const;
  [[nodiscard]] const std::vector<StatementEntity> &GetStatementEntities()
      const;
  [[nodiscard]] const std::vector<VariableEntity> &GetVariableEntities() const;
  [[nodiscard]] const std::vector<WhileEntity> &GetWhileEntities() const;
  [[nodiscard]] std::unordered_map<TNode, StatementEntity>
      &GetTNodeStmtEntUmap() const;
  [[nodiscard]] std::unordered_map<TNode, VariableEntity> &GetTNodeVarEntUmap()
      const;
  [[maybe_unused]] [[nodiscard]] std::unordered_map<TNode, ConstantEntity>
      &GetTNodeConstEntUmap() const;
  [[nodiscard]] std::unordered_map<TNode, ProcedureEntity>
      &GetTNodeProcEntUmap() const;
  [[nodiscard]] std::unordered_map<const TNode *,
                                   std::unordered_set<const TNode *>>
      &GetProcNodeCallEntUmap() const;
  [[nodiscard]] std::unordered_map<std::string, const TNode *>
      &GetProcNameNodeUmap() const;

  class Builder {
   public:
    Builder();
    Builder AssignEntities(const std::vector<AssignEntity> *assign_entities);
    Builder CallEntities(const std::vector<CallEntity> *call_entities);
    Builder ConstantEntities(
        const std::vector<ConstantEntity> *constant_entities);
    Builder IfEntities(const std::vector<IfEntity> *if_entities);
    Builder PrintEntities(const std::vector<PrintEntity> *print_entities);
    Builder ProcedureEntities(
        const std::vector<ProcedureEntity> *procedure_entities);
    Builder ReadEntities(const std::vector<ReadEntity> *read_entities);
    Builder StatementEntities(
        const std::vector<StatementEntity> *statement_entities);
    Builder VariableEntities(
        const std::vector<VariableEntity> *variable_entities);
    Builder WhileEntities(const std::vector<WhileEntity> *while_entities);
    Builder TNodeStmtEntUmap(
        std::unordered_map<TNode, StatementEntity> *t_node_stmt_ent_umap);
    Builder TNodeVarEntUmap(
        std::unordered_map<TNode, VariableEntity> *t_node_var_ent_umap);
    Builder TNodeConstEntUmap(
        std::unordered_map<TNode, ConstantEntity> *t_node_const_ent_umap);
    Builder TNodeProcEntUmap(
        std::unordered_map<TNode, ProcedureEntity> *t_node_proc_ent_umap);
    Builder ProcNodeCallEntUmap(
        std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
            *proc_node_call_ent_umap);
    Builder ProcNameNodeUmap(
        std::unordered_map<std::string, const TNode *> *proc_name_node_umap);
    SubAbstractionExtractorContext Build();

   private:
    const std::vector<AssignEntity> *assign_entities_{};
    const std::vector<CallEntity> *call_entities_{};
    const std::vector<ConstantEntity> *constant_entities_{};
    const std::vector<IfEntity> *if_entities_{};
    const std::vector<PrintEntity> *print_entities_{};
    const std::vector<ProcedureEntity> *procedure_entities_{};
    const std::vector<ReadEntity> *read_entities_{};
    const std::vector<StatementEntity> *statement_entities_{};
    const std::vector<VariableEntity> *variable_entities_{};
    const std::vector<WhileEntity> *while_entities_{};
    std::unordered_map<TNode, StatementEntity> *t_node_stmt_ent_umap_{};
    std::unordered_map<TNode, VariableEntity> *t_node_var_ent_umap_{};
    std::unordered_map<TNode, ConstantEntity> *t_node_const_ent_umap_{};
    std::unordered_map<TNode, ProcedureEntity> *t_node_proc_ent_umap_{};
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        *proc_node_call_ent_umap_{};
    std::unordered_map<std::string, const TNode *> *proc_name_node_umap_{};
  };

 private:
  const std::vector<AssignEntity> &assign_entities_;
  const std::vector<CallEntity> &call_entities_;
  const std::vector<ConstantEntity> &constant_entities_;
  const std::vector<IfEntity> &if_entities_;
  const std::vector<PrintEntity> &print_entities_;
  const std::vector<ProcedureEntity> &procedure_entities_;
  const std::vector<ReadEntity> &read_entities_;
  const std::vector<StatementEntity> &statement_entities_;
  const std::vector<VariableEntity> &variable_entities_;
  const std::vector<WhileEntity> &while_entities_;
  std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap_;
  std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap_;
  std::unordered_map<TNode, ConstantEntity> &t_node_const_ent_umap_;
  std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap_;
  std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
      &proc_node_call_ent_umap_;
  std::unordered_map<std::string, const TNode *> &proc_name_node_umap_;
};

#endif  // SPA_SUB_ABSTRACTION_EXTRACTOR_CONTEXT_H_
