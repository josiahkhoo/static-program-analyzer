//
// Created by kohha on 5/11/2022.
//

#include "print_entity_storable.h"

PrintEntityStorable::PrintEntityStorable() = default;

/// Store Print Entities
/// \param ts List of entities
void PrintEntityStorable::Store(std::vector<PrintEntity> ts) {
  for (const PrintEntity& entity : ts) {
    entity_manager_.AddPrintStatement(entity);
  }
}