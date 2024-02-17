#include <Geode/Geode.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>
#include <array>
#include <vector>
#include <set>
#include <algorithm>

using namespace geode::prelude;

int LevelEditorLayer_getNextFreeGroupID(LevelEditorLayer* self, CCArray* p0) {
	std::set<short> usedGroups = {};
	
	CCObject* obj = nullptr;

	CCARRAY_FOREACH(self->m_objects, obj) {
		GameObject* thisBlock = static_cast<GameObject*>(obj);
		auto groups = thisBlock->m_groups;

		for (int groupIndex = 0; groupIndex < thisBlock->m_groupCount; groupIndex++) {
			auto group = groups->at(groupIndex);
			usedGroups.insert(group);
		}
	}

	for (short nextFree = Mod::get()->getSavedValue("relative-next-free", 1); nextFree < 10000; nextFree++) {
		if (usedGroups.contains(nextFree)) continue;

		return nextFree;
	}

	return 0;
}

$execute {
	Mod::get()->hook(
		reinterpret_cast<void*>(geode::base::get() + 0x241530), // address
        &LevelEditorLayer_getNextFreeGroupID, // detour
        "LevelEditorLayer::getNextFreeGroupID", // display name, shows up on the console
        tulip::hook::TulipConvention::Thiscall // calling convention
	);
}