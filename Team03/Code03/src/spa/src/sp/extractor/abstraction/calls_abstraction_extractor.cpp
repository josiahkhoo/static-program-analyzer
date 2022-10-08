#include "calls_abstraction_extractor.h"

std::vector<CallsAbstraction> CallsAbstractionExtractor::Extract(
    const SubAbstractionExtractorContext &context) const {
  std::vector<CallsAbstraction> calls_abstractions = {};
  auto proc_node_call_ent_umap = context.GetProcNodeCallEntUmap();
  auto t_node_proc_ent_umap = context.GetTNodeProcEntUmap();
  auto proc_name_node_umap = context.GetProcNameNodeUmap();
  for (const auto &[parent, children] : proc_node_call_ent_umap) {
    auto lhs = t_node_proc_ent_umap.find(*parent)->second;
    for (const auto &child : children) {
      auto proc_node = proc_name_node_umap[child->GetStringValue()];
      auto rhs = t_node_proc_ent_umap.find(*proc_node)->second;
      calls_abstractions.emplace_back(lhs, rhs);
    }
  }
  return calls_abstractions;
}
