/***************************************************/
/* Nom:	GameManager.h
/* Description: GameManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GameManager_H_
#define __GameManager_H_

#include "SceneManager.h"
#include "EntityManager.h"
#include "Core\DataManager.h"
#include "Input\InputManager.h"
#include "Graphics\IFacade.h"

namespace crea
{

	class CREAENGINE_API GameManager
	{
		GameManager();

		IFacade* m_pRenderer;

	public:
		~GameManager();

		static GameManager* getSingleton();

		inline IFacade* getRenderer() { return m_pRenderer; }

		inline void setState(State* s) { SceneManager::getSingleton()->setState(s); }

		inline bool isKeyPressed(Key _key) { return InputManager::getSingleton()->isKeyPressed(_key); }

		inline IFont* getFont(string _szName) { return DataManager::getSingleton()->getFont(_szName); }

		inline ITexture* getTexture(string _szName) { return DataManager::getSingleton()->getTexture(_szName); }

		inline IColor* getColor(string _szName) { return DataManager::getSingleton()->getColor(_szName); }

		inline IText* getText(string _szName) { return DataManager::getSingleton()->getText(_szName); }

		inline ISprite* getSprite(string _szName) { return DataManager::getSingleton()->getSprite(_szName); }

		inline Map* getMap(string _szName) { return DataManager::getSingleton()->getMap(_szName); }

		inline Animation* getAnimation(string _szName) { return DataManager::getSingleton()->getAnimation(_szName); }

		inline ActionTable* getActionTable(string _szName) { return DataManager::getSingleton()->getActionTable(_szName); }

		inline Entity* getEntity(string _szName) { return EntityManager::getSingleton()->getEntity(_szName); }

		inline void addEntity(Entity* _pEntity, Entity* _pParent = nullptr)  { EntityManager::getSingleton()->addEntity(_pEntity, _pParent); }

		inline TextRenderer* getTextRenderer(string _szName) { return EntityManager::getSingleton()->getTextRenderer(_szName); }

		inline SpriteRenderer* getSpriteRenderer(string _szName) { return EntityManager::getSingleton()->getSpriteRenderer(_szName); }

		inline MapRenderer* getMapRenderer(string _szName) { return EntityManager::getSingleton()->getMapRenderer(_szName); }

		inline AnimatedSprite* getAnimatedSprite(string _szName) { return DataManager::getSingleton()->getAnimatedSprite(_szName); }

		inline AnimatedSpriteRenderer* getAnimatedSpriteRenderer(string _szName) { return EntityManager::getSingleton()->getAnimatedSpriteRenderer(_szName); }

		inline void clearAllData() { DataManager::getSingleton()->clear(); }

		inline void clearAllEntities() { EntityManager::getSingleton()->clear(); }

		void init();

		void update();

		void quit();
	};

} // namespace crea

#endif
