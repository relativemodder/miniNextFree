#include <Geode/Geode.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>
#include <array>
#include <vector>
#include <set>
#include <algorithm>

using namespace geode::prelude;

class $modify(SetGroupIDLayer) {

	bool init(GameObject* p0, CCArray* p1) {
		if (!SetGroupIDLayer::init(p0, p1)) return false; // fallback

		log::info("SetGroupIDLayer::init");

		auto innerLayer = dynamic_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
		log::info("InnerLayer: {}", innerLayer);


		auto nextFreeSprite = CCSprite::createWithSpriteFrameName("GJ_plus2Btn_001.png");
		auto nextFreeBtn = CCMenuItemSpriteExtra::create(nextFreeSprite, this, menu_selector(CustomNextFreeLayer::onNextFreePlus));

		nextFreeBtn->setPosition({-75.0, 175.0f});

		log::info("Added nextFreeBtn");
		this->m_buttonMenu->addChild(nextFreeBtn);

		return true;
	}
};