#include "spa.h"

SPA::SPA() = default;

void SPA::Parse(const std::string& filename) {
  source_processor_.Process(filename);
}

void SPA::Evaluate(const std::string& query, std::list<std::string>& results) {
  query_processing_subsystem.Process(query, results);
}
