#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>
#include <array>
#include <vector>
#include <set>
#include <algorithm>

using namespace geode::prelude;

class CustomNextFreeLayer : public FLAlertLayer {
public:
	CCTextInputNode* m_nextFreeInput = nullptr;

	void onClose(CCObject*) {
		auto actualString = std::string(m_nextFreeInput->getString().c_str()) == "" ? "0" : m_nextFreeInput->getString();
		int nextFreeValue = std::stoi(actualString);
		nextFreeValue = nextFreeValue > 0 ? nextFreeValue : 1;
		Mod::get()->setSavedValue("relative-next-free", nextFreeValue);
        this->removeFromParent();
    }

	CCScale9Sprite* createWindow() {
		auto backSprite = CCScale9Sprite::create("GJ_square01.png");
		this->m_mainLayer->addChild(backSprite);
		backSprite->setContentSize(ccp(200, 140));
		backSprite->setScale(0.0f);

		auto winSize = CCDirector::sharedDirector()->getWinSize();

		backSprite->setPosition({winSize.width / 2, winSize.height / 2});

		backSprite->runAction(CCEaseInOut::create(CCScaleTo::create(0.15, 1.0f), 0.7f));
		this->runAction(CCFadeTo::create(0.2f, 0x64));

		return backSprite;
	}

	virtual bool init() {
		if (!FLAlertLayer::init(0))
            return false;

		this->setKeyboardEnabled(true);
		auto window = this->createWindow();

		auto okspr = ButtonSprite::create("OK", "goldFont.fnt", "GJ_button_05.png");
        auto okBtn = CCMenuItemSpriteExtra::create(okspr, this, menu_selector(CustomNextFreeLayer::onClose));

		auto mainMenu = CCMenu::create();

		m_buttonMenu = mainMenu;

		mainMenu->addChild(okBtn);
		m_mainLayer->addChild(mainMenu);

		mainMenu->ignoreAnchorPointForPosition(false);
		mainMenu->setPosition({0., 0.});
		mainMenu->setAnchorPoint({0., 0.});

		auto winSize = CCDirector::sharedDirector()->getWinSize();

		okBtn->setPosition({winSize.width / 2, winSize.height / 2.f - 40.f});

		m_mainLayer->setScale(0.0f);
		m_mainLayer->runAction(CCEaseInOut::create(CCScaleTo::create(0.15, 1.0f), 0.7f));

		std::stringstream ss;
        ss << Mod::get()->getSavedValue("relative-next-free", 1);

		m_nextFreeInput = CCTextInputNode::create(100, 40, "Next free", "bigFont.fnt");
		m_nextFreeInput->setPosition(mainMenu->getContentSize() / 2 + ccp(0.0, 0.0));
		m_nextFreeInput->setString(ss.str());
		m_nextFreeInput->setAllowedChars("0123456789");
		m_nextFreeInput->setMaxLabelLength(5);
		m_nextFreeInput->setID("NEXTFREE_BY_RELATIVE"_spr);

		auto titleLabel = CCLabelBMFont::create("Set Next Free", "bigFont.fnt");
		m_mainLayer->addChild(titleLabel);

		titleLabel->setPosition(mainMenu->getContentSize() / 2 + ccp(0.0, 50.0));
		titleLabel->setScale(0.7f);

		mainMenu->addChild(m_nextFreeInput);

		return true;
	}
	static CustomNextFreeLayer* create() {
		auto ret = new CustomNextFreeLayer();
		if (ret && ret->init()) {
			ret->autorelease();
		} else {
			delete ret;
			ret = nullptr;
		}
		return ret;
	}

	void onNextFreePlus(CCObject* object) {
		auto layer = CustomNextFreeLayer::create();
		CCScene::get()->addChild(layer, 999);
	}
};
