/***************************************************/
/* Nom:	GameManager.h
/* Description: GameManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GameManager_H_
#define __GameManager_H_

#include "SceneManager.h"
#include "EntityManager.h"
#include "Data\DataManager.h"
#include "Input\InputManager.h"
#include "Core\Math.h"
#include "AI\Agent.h"
#include "Core\Script.h"
#include "Core\PhysicsManager.h"
#include "AI\Pathfinding\MapSearchManager.h"
#include "AI\Pathfinding\ClusterSearchManager.h"
#include "Graphics\IFacade.h"

namespace crea
{
	class Collider;
	class LoggerFile;

	enum EnumRendererType
	{
		Renderer_Invalid = -1,
		Renderer_SFML = 0,
		Renderer_DX9 = 1,
		Renderer_GL3 = 2,
		Renderer_Max,
	};

	class CREAENGINE_API GameManager
	{
		GameManager();

		// Renderer
		IFacade* m_pRenderer;
		EnumRendererType m_rendererType;

		LoggerFile* m_pLogger;

		bool m_bContinueMainLoop = true;

	public:
		~GameManager();

		static GameManager* getSingleton();

		void setRendererType(EnumRendererType _rendererType);

		inline IFacade* getRenderer() { return m_pRenderer; }

		IntRect getWindowRect() { return m_pRenderer->getWindowRect(); }

		void setWindowRect(IntRect _rect) { m_pRenderer->setWindowRect(_rect); }

		inline void setScene(Scene* s) 
		{ 
			SceneManager::getSingleton()->setScene(s);
			EntityManager::getSingleton()->init();
		}

		// Input
		inline bool isKeyPressed(Key _key) { return InputManager::getSingleton()->isKeyPressed(_key); }

		inline bool isMouseButtonPressed(Button _button) { return InputManager::getSingleton()->isMouseButtonPressed(_button); }

		inline Vector2f getMousePosition() { return InputManager::getSingleton()->getMousePosition(); }

		// Data
		inline Font* getFont(const string& _szName) { return DataManager::getSingleton()->getFont(_szName); }

		inline Texture* getTexture(const string& _szName) { return DataManager::getSingleton()->getTexture(_szName); }

		inline Color* getColor(const string& _szName) { return DataManager::getSingleton()->getColor(_szName); }

		inline Text* getText(const string& _szName) { return DataManager::getSingleton()->getText(_szName); }

		inline Sprite* getSprite(const string& _szName) { return DataManager::getSingleton()->getSprite(_szName); }

		inline Shape* getShape(const string& _szType, const string& _szName) { return DataManager::getSingleton()->getShape(_szType, _szName); }

		inline Map* getMap(const string& _szName) { return DataManager::getSingleton()->getMap(_szName); }

		inline Agent* getAgent(const string& _szName) { return DataManager::getSingleton()->getAgent(_szName); }

		inline Animation* getAnimation(const string& _szName) { return DataManager::getSingleton()->getAnimation(_szName); }

		inline ActionTable* getActionTable(const string& _szName) { return DataManager::getSingleton()->getActionTable(_szName); }

		inline Animator* getAnimator(const string& _szName) { return EntityManager::getSingleton()->getAnimator(_szName); }

		inline Script* getScript(const string& _szName) { return EntityManager::getSingleton()->getScript(_szName); }

		inline void setScriptFactory(ScriptFactory* _pScriptFactory) { return EntityManager::getSingleton()->setScriptFactory(_pScriptFactory); }

		inline MapRenderer* getMapRenderer(const string& _szName) { return EntityManager::getSingleton()->getMapRenderer(_szName); }

		inline TextRenderer* getTextRenderer(const string& _szName) { return EntityManager::getSingleton()->getTextRenderer(_szName); }

		inline SpriteRenderer* getSpriteRenderer(const string& _szName) { return EntityManager::getSingleton()->getSpriteRenderer(_szName); }

		inline Entity* getEntity(const string& _szName) { return EntityManager::getSingleton()->getEntity(_szName); }

		inline void addEntity(Entity* _pEntity, Entity* _pParent = nullptr) { EntityManager::getSingleton()->addEntity(_pEntity, _pParent); }

		inline void clearAllData() { DataManager::getSingleton()->clear(); }

		inline void clearAllEntities() { EntityManager::getSingleton()->clear(); }

		inline void clearEntity(Entity* _pEntity) { EntityManager::getSingleton()->clearEntity(_pEntity); }

		inline Entity* getEntityByModel(const string& _szName) { return EntityManager::getSingleton()->getEntityByModel(_szName); }

		inline void addEntityByModel(const string& _szName, Entity* _pEntity) { EntityManager::getSingleton()->addEntityByModel(_szName, _pEntity); }

		inline void clearCollisions() { PhysicsManager::getSingleton()->clearCollisions(); }

		inline Entity* instanciate(string _szName, Entity* _pEntity) { return EntityManager::getSingleton()->instanciate(_szName, _pEntity); }

		inline Steering* getSteering(string _szName) { return EntityManager::getSingleton()->getSteering(_szName); }

		inline Vehicle* getVehicle(string _szName) { return DataManager::getSingleton()->getVehicle(_szName); }

		inline Material* getMaterial(string _szName, bool _bCloned = false) { return DataManager::getSingleton()->getMaterial(_szName, _bCloned); }

		inline Shader* getShader(string _szName) { return DataManager::getSingleton()->getShader(_szName); }

		// Selection
		inline void selectEntities(Vector2f _vStart, Vector2f _vEnd) { EntityManager::getSingleton()->selectEntities(_vStart, _vEnd); }

		inline void unselectEntities() { EntityManager::getSingleton()->unselectEntities(); }

		inline ListEntity* getSelectedEntities() { return EntityManager::getSingleton()->getSelectedEntities(); }

		// Physics

		inline Collider* getStaticCollider(const string& _szName) { return PhysicsManager::getSingleton()->getStaticCollider(_szName); }

		inline Collider* getDynamicCollider(const string& _szName) { return PhysicsManager::getSingleton()->getDynamicCollider(_szName); }

		// A*
		inline MapSearch* getMapSearch(string _szName) { return MapSearchManager::getSingleton()->getMapSearch(_szName); }

		inline ClusterSearch* getClusterSearch(string _szName) { return ClusterSearchManager::getSingleton()->getClusterSearch(_szName); }

		void init();

		void update();

		void quit();
	};

} // namespace crea

#endif
