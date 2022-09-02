#include "qp_enums.h"

bool QPEnums::IsDesignEntity(std::string s) {
	for (auto const& pair : DesignEntities) {
		if (s == pair.second) { return true; }
	}
	return false;
}
