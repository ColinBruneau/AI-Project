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
#include "Physics\CharacterController.h"
#include "AI\Agent.h"
#include "AI\Pathfinding\MapSearchManager.h"

namespace crea
{
	class LoggerFile;

	class CREAENGINE_API GameManager
	{
		GameManager();

		IFacade* m_pRenderer;

		LoggerFile* m_pLogger;

	public:
		~GameManager();

		static GameManager* getSingleton();

		IntRect getWindowRect() { return m_pRenderer->getWindowRect(); }

		inline IFacade* getRenderer() { return m_pRenderer; }

		inline void setScene(Scene* s) { SceneManager::getSingleton()->setScene(s); }

		// Input
		inline bool isKeyPressed(Key _key) { return InputManager::getSingleton()->isKeyPressed(_key); }

		inline bool isMouseButtonPressed(Button _button) { return InputManager::getSingleton()->isMouseButtonPressed(_button); }

		inline Vector2f getMousePosition() { return InputManager::getSingleton()->getMousePosition(); }

		// Data
		inline IFont* getFont(string _szName) { return DataManager::getSingleton()->getFont(_szName); }

		inline ITexture* getTexture(string _szName) { return DataManager::getSingleton()->getTexture(_szName); }

		inline IColor* getColor(string _szName) { return DataManager::getSingleton()->getColor(_szName); }

		inline IText* getText(string _szName) { return DataManager::getSingleton()->getText(_szName); }

		inline ISprite* getSprite(string _szName) { return DataManager::getSingleton()->getSprite(_szName); }

		inline Map* getMap(string _szName) { return DataManager::getSingleton()->getMap(_szName); }

		inline Animation* getAnimation(string _szName) { return DataManager::getSingleton()->getAnimation(_szName); }

		inline ActionTable* getActionTable(string _szName) { return DataManager::getSingleton()->getActionTable(_szName); }

		inline Agent* getAgent(string _szName) { return DataManager::getSingleton()->getAgent(_szName); }

		inline Collider* getCollider(string _szName) { return DataManager::getSingleton()->getCollider(_szName); }

		inline Entity* getEntity(string _szName) { return EntityManager::getSingleton()->getEntity(_szName); }

		inline void addEntity(Entity* _pEntity, Entity* _pParent = nullptr)  { EntityManager::getSingleton()->addEntity(_pEntity, _pParent); }

		inline TextRenderer* getTextRenderer(string _szName) { return EntityManager::getSingleton()->getTextRenderer(_szName); }

		inline SpriteRenderer* getSpriteRenderer(string _szName) { return EntityManager::getSingleton()->getSpriteRenderer(_szName); }

		inline MapRenderer* getMapRenderer(string _szName) { return EntityManager::getSingleton()->getMapRenderer(_szName); }
		
		inline Animator* getAnimator(string _szName) { return EntityManager::getSingleton()->getAnimator(_szName); }

		inline CharacterController* getCharacterController(string _szName) { return EntityManager::getSingleton()->getCharacterController(_szName); }

		inline UserController* getUserController(string _szName) { return EntityManager::getSingleton()->getUserController(_szName); }

		inline Steering* getSteering(string _szName) { return EntityManager::getSingleton()->getSteering(_szName); }

		inline MapSearch* getMapSearch(string _szName) { return MapSearchManager::getSingleton()->getMapSearch(_szName); }

		inline void clearAllData() { DataManager::getSingleton()->clear(); }

		inline void clearAllEntities() { EntityManager::getSingleton()->clear(); }

		inline void clearEntity(Entity* _pEntity) { EntityManager::getSingleton()->clearEntity(_pEntity); }

		// Selection
		inline void selectEntities(Vector2f _vStart, Vector2f _vEnd) { EntityManager::getSingleton()->selectEntities(_vStart, _vEnd); }
		
		inline void unselectEntities() { EntityManager::getSingleton()->unselectEntities(); }

		inline ListEntity* getSelectedEntities() { return EntityManager::getSingleton()->getSelectedEntities(); }


		void init();

		void update();

		void quit();
	};

} // namespace crea

#endif
