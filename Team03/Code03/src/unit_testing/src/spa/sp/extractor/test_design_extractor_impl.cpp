#include "catch.hpp"
#include "fakeit.hpp"
#include "sp/extractor/design_extractor_impl.h"

using namespace fakeit;

TEST_CASE("Design Extractor", "[DesignExtractor]") {
  Mock<EntityExtractor> mock_entity_extractor;
  EntityExtractorResult eer =
      EntityExtractorResult({}, {}, {}, {}, {}, {}, {}, {}, {}, {});
  When(Method(mock_entity_extractor, Extract)).Return(eer);
  Mock<AbstractionExtractorImpl> mock_abstraction_extractor;
  AbstractionExtractorResult aer = AbstractionExtractorResult(
      {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {});
  When(Method(mock_abstraction_extractor, Extract)).Return(aer);

  DesignExtractorImpl extractor_under_test = DesignExtractorImpl(
      mock_entity_extractor.get(), mock_abstraction_extractor.get());

  TNode test_node = TNode(1, TNode::Program, 0, "");
  SECTION("Calls entity extractor and abstraction extractor") {
    DesignExtractorResult der = extractor_under_test.Extract(test_node);
    Verify(Method(mock_entity_extractor, Extract).Using(test_node));
    Verify(Method(mock_abstraction_extractor, Extract)).Exactly(1);
    REQUIRE(der.GetEntityExtractorResult() == eer);
    REQUIRE(der.GetAbstractionExtractorResult() == aer);
    VerifyNoOtherInvocations(Method(mock_entity_extractor, Extract));
    VerifyNoOtherInvocations(Method(mock_abstraction_extractor, Extract));
  }
}
