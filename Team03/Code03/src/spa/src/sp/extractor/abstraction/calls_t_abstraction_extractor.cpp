#include "calls_t_abstraction_extractor.h"

std::vector<CallsTAbstraction> CallsTAbstractionExtractor::Extract(
    const SubAbstractionExtractorContext &context) const {
  std::vector<CallsTAbstraction> calls_t_abstractions = {};
  auto proc_node_call_ent_umap = context.GetProcNodeCallEntUmap();
  auto t_node_proc_ent_umap = context.GetTNodeProcEntUmap();
  auto proc_name_node_umap = context.GetProcNameNodeUmap();
  for (const auto &[parent, children] : proc_node_call_ent_umap) {
    auto lhs = t_node_proc_ent_umap.find(*parent)->second;
    std::unordered_set<std::string> unique_procedures;
    TraverseProcedureTree(t_node_proc_ent_umap, calls_t_abstractions,
                          proc_name_node_umap, proc_node_call_ent_umap,
                          children, lhs, unique_procedures);
  }

  return calls_t_abstractions;
}

void CallsTAbstractionExtractor::TraverseProcedureTree(
    std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap,
    std::vector<CallsTAbstraction> &calls_t_abstractions,
    std::unordered_map<std::string, const TNode *> &proc_name_node_umap,
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        &proc_node_call_ent_umap,
    const std::unordered_set<const TNode *> &children, ProcedureEntity &lhs,
    std::unordered_set<std::string> &unique_procedures) const {
  for (const auto &child : children) {
    auto proc_child_node = proc_name_node_umap[child->GetStringValue()];
    auto rhs = t_node_proc_ent_umap.find(*proc_child_node)->second;
    if (unique_procedures.find(rhs.GetName()) == unique_procedures.end()) {
      unique_procedures.emplace(rhs.GetName());
      calls_t_abstractions.emplace_back(lhs, rhs);
      std::unordered_set<const TNode *> next_children =
          proc_node_call_ent_umap[proc_child_node];
      TraverseProcedureTree(t_node_proc_ent_umap, calls_t_abstractions,
                            proc_name_node_umap, proc_node_call_ent_umap,
                            next_children, lhs, unique_procedures);
    }
  }
}
