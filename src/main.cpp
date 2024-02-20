#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>
#include <array>
#include <vector>
#include <set>
#include <algorithm>
#include "CustomNextFreeLayer.h"
#include "SetGroupIDLayer.h"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
	int getNextFreeGroupID(CCArray* p0) {
		int nextFreeMinClamp = Mod::get()->getSavedValue("relative-next-free", 1);
		std::set<short> usedGroups = {};
		CCObject* obj;

		CCARRAY_FOREACH(this->m_objects, obj) {
			GameObject* thisBlock = static_cast<GameObject*>(obj);

			for (int groupIndex = 0; groupIndex < thisBlock->m_groupCount; groupIndex++) {
				usedGroups.insert(thisBlock->m_groups->at(groupIndex));
			}

		}

		for (short nextFree = nextFreeMinClamp; nextFree < 10000; nextFree++) {
			if (usedGroups.contains(nextFree)) continue;
			return nextFree;
		}

		return 0;
	}
};