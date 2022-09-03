#ifndef SPA_REFERENCE_H
#define SPA_REFERENCE_H

#include <optional>
#include <string>

class Reference {
 public:
  explicit Reference();
  [[nodiscard]] std::optional<std::string> GetSynonym() const;

  [[nodiscard]] bool IsSynonym() const;
  [[nodiscard]] bool IsWildCard() const;

  void SetSynonym(const std::string& synonym);
  void SetWildCard();

 private:
  std::optional<std::string> synonym_;
  bool is_wild_card_;
};

#endif  // SPA_REFERENCE_H
