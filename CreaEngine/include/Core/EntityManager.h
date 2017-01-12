/***************************************************/
/* Nom:	EntityManager.h
/* Description: EntityManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __EntityManager_H_
#define __EntityManager_H_

#include <string>
#include <map>
using namespace std;

// Prédéfinitions
namespace crea
{
	class TextRenderer;
	class SpriteRenderer;
	class MapRenderer;
	class Animator;
	class Entity;
	class CharacterController;
	class UserController;
	class Steering;
}

namespace crea
{
	class CREAENGINE_API MapStringTextRenderer : public map<string, TextRenderer*> {};
	class CREAENGINE_API MapStringSpriteRenderer : public map<string, SpriteRenderer*> {};
	class CREAENGINE_API MapStringMapRenderer : public map<string, MapRenderer*> {};
	class CREAENGINE_API MapStringAnimator : public map<string, Animator*> {};
	class CREAENGINE_API MapStringCharacterController : public map<string, CharacterController*> {};
	class CREAENGINE_API MapStringUserController : public map<string, UserController*> {};
	class CREAENGINE_API MapStringSteering : public map<string, Steering*> {};

	class CREAENGINE_API EntityManager
	{
		MapStringTextRenderer m_pTextRenderers;

		MapStringSpriteRenderer m_pSpriteRenderers;

		MapStringMapRenderer m_pMapRenderers;

		MapStringAnimator m_pAnimators;

		MapStringCharacterController m_pCharacterControllers;

		MapStringUserController m_pUserControllers;

		MapStringSteering m_pSteerings;

		Entity* m_pRoot;

		EntityManager();

	public:
		virtual ~EntityManager();

		static EntityManager* getSingleton();

		Entity* getEntity(string& _szName);

		void addEntity(Entity* _pEntity, Entity* _pParent = nullptr);

		TextRenderer* getTextRenderer(string _szName, bool _bCloned = false);

		SpriteRenderer* getSpriteRenderer(string _szName, bool _bCloned = false);

		MapRenderer* getMapRenderer(string _szName, bool _bCloned = false);

		Animator* getAnimator(string _szName, bool _bCloned = false);

		CharacterController* getCharacterController(string _szName, bool _bCloned = false);

		UserController* getUserController(string _szName, bool _bCloned = false);

		Steering* getSteering(string _szName, bool _bCloned = false);

		bool init();

		bool update();

		bool draw();

		void clear();
	};


} // namespace crea

#endif
