#ifndef SPA_RELATIONSHIP_MANAGER_H
#define SPA_RELATIONSHIP_MANAGER_H

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "follows_storage.h"

class RelationshipManager {
	public:
		RelationshipManager();
		/* ====================================
		* General Entity Adder Methods
		* ==================================== */
		// store follows to FollowsStorage 
		void AddFollowsAbstraction(FollowsAbstraction followsAbs);

		// store followsT to FollowsStorage 
		void AddFollowsTAbstraction(FollowsTAbstraction followsTAbs);

	private:
		static FollowsStorage followsStore;


};



#endif  // SPA_RELATIONSHIP_MANAGER_H
