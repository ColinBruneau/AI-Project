#include "stdafx.h"

#include "Game\StateGame.h"
#include "Game\StateMenu.h"
#include "Game\StateMap.h"
#include "Core\SceneManager.h"
#include "Core\ICore.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"


StateGame::StateGame()
{

}

StateGame::~StateGame()
{

}
	
bool StateGame::onInit()
{
	m_pGM = crea::GameManager::getSingleton();
	// Load Map
	crea::Entity* m_pEntity3;
	crea::Map* m_pMap;
	crea::MapRenderer* m_pMapRenderer;
	m_pEntity3 = m_pGM->getEntity("map1");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map1.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	// Text
	crea::IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	m_pTextFPS = m_pGM->getText("fps");
	m_pTextFPS->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextFPS->setColor(pRed);
	m_pTextFPS->setCharacterSize(20);
	m_pTextFPS->setString("fps");

	crea::TextRenderer* pTextRenderer = m_pGM->getTextRenderer("TextRenderer1");
	pTextRenderer->setText(m_pTextFPS);

	crea::Entity* pEntityFPS = m_pGM->getEntity("text 1");
	pEntityFPS->addComponent(pTextRenderer);

	m_pGM->addEntity(pEntityFPS);

	// Sprite
	m_pSprite1 = m_pGM->getSprite("image");
	m_pSprite1->setTexture(m_pGM->getTexture("image.png"));
	m_pSprite1->setPosition(300, 150);

	m_pSpriteRenderer = m_pGM->getSpriteRenderer("SpriteRenderer1");
	m_pSpriteRenderer->setSprite(m_pSprite1);

	m_pEntity1 = m_pGM->getEntity("sprite 1"); 
	m_pEntity1->addComponent(m_pSpriteRenderer);

	m_pGM->addEntity(m_pEntity1);

	// Animated Sprite
	m_pAnimatedSprite1 = m_pGM->getAnimatedSprite("AnimatedSprite1");
	//sf::Texture* texture = m_pGM->getTexture("player.png");
	//m_pAnimatedSprite1->setTexture(*texture); // Texture will be set by each animation
	m_pAnimatedSprite1->setPosition(crea::Vector2f(150.f, 150.f));

	m_pAnimatedSpriteRenderer = m_pGM->getAnimatedSpriteRenderer("AnimatedSpriteRenderer1");
	m_pAnimatedSpriteRenderer->setAnimatedSprite(m_pAnimatedSprite1);

	m_pEntity2 = m_pGM->getEntity(string("animated sprite 1"));
	m_pEntity2->addComponent(m_pAnimatedSpriteRenderer);

	/*
	// set up the animations for all four directions (set spritesheet and push frames)
	walkingAnimationDown.setSpriteSheet(*texture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	walkingAnimationLeft.setSpriteSheet(*texture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	walkingAnimationRight.setSpriteSheet(*texture);
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

	walkingAnimationUp.setSpriteSheet(*texture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));
	*/
	
	// Load Animations
	currentAnimation = m_pGM->getAnimation("player/default.anm");
	m_pGM->getAnimation("player/default-idle.anm");
	m_pGM->getAnimation("player/default-walkdown.anm");
	m_pGM->getAnimation("player/default-walkleft.anm");
	m_pGM->getAnimation("player/default-walkright.anm");
	m_pGM->getAnimation("player/default-walkup.anm");

	speed = 80.f;
	noKeyWasPressed = true;

	m_pGM->addEntity(m_pEntity2);

	// Fill ActionTable
	/*
	m_pActionTable = new crea::ActionTable();
	m_pActionTable->addAnimation(kACond_Default, kAct_Default, &string("player/default.anm"));
	m_pActionTable->addAnimation(kACond_Default, kAct_Idle, &string("player/default-idle.anm"));
	m_pActionTable->addAnimation(kACond_Default, kAct_WalkDown, &string("player/default-walkdown.anm"));
	m_pActionTable->addAnimation(kACond_Default, kAct_WalkLeft, &string("player/default-walkleft.anm"));
	m_pActionTable->addAnimation(kACond_Default, kAct_WalkRight, &string("player/default-walkright.anm"));
	m_pActionTable->addAnimation(kACond_Default, kAct_WalkUp, &string("player/default-walkup.anm"));
	*/

	// Load ActionTable
	m_pActionTable = m_pGM->getActionTable("player/player.act");

	return true;
}

bool StateGame::onUpdate()
{
	// Get direction from keyboard
	if (m_pGM->isKeyPressed('1'))
	{
		m_pGM->setState(new StateMenu());
		return true;
	}

	if (m_pGM->isKeyPressed('3'))
	{
		m_pGM->setState(new StateMap());
		return true;
	}

	// Animated Sprite
	crea::Time frameTime = frameClock.restart();
	m_pTextFPS->setString("                              " + to_string((int)(1/frameTime.asSeconds())) + " fps");
	//m_pTextFPS->setString("                              " + to_string((int)frameClock.getElapsedTime().asSeconds()) + " s");
	// if a key was pressed set the correct animation and move correctly
	crea::Vector2f movement(0.f, 0.f);
	if (m_pGM->isKeyPressed('a'))
	{
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(kACond_Default, kAct_WalkUp, nullptr)); //&walkingAnimationUp;
		movement.addY(-speed);
		noKeyWasPressed = false;
	}
	if (m_pGM->isKeyPressed('q'))
	{
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(kACond_Default, kAct_WalkDown, nullptr)); //&walkingAnimationDown;
		movement.addY(+speed);
		noKeyWasPressed = false;
	}
	if (m_pGM->isKeyPressed('o'))
	{
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(kACond_Default, kAct_WalkLeft, nullptr)); //&walkingAnimationLeft;
		movement.addX(-speed);
		noKeyWasPressed = false;
	}
	if (m_pGM->isKeyPressed('p'))
	{
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(kACond_Default, kAct_WalkRight, nullptr)); //&walkingAnimationRight;
		movement.addX(speed);
		noKeyWasPressed = false;
	}
	m_pAnimatedSprite1->play(*currentAnimation);
	m_pAnimatedSprite1->move(movement * (float) frameTime.asSeconds());

	// if no key was pressed stop the animation
	if (noKeyWasPressed)
	{
		m_pAnimatedSprite1->stop();
	}
	noKeyWasPressed = true;

	// update AnimatedSprite
	m_pAnimatedSprite1->update(frameTime);

	return true;
}

bool StateGame::onDraw()
{
	return true;
}

bool StateGame::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

