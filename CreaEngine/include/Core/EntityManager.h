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
	class AnimatedSpriteRenderer;
	class Entity;
}

namespace crea
{
	class CREAENGINE_API MapStringTextRenderer : public map<string, TextRenderer*> {};
	class CREAENGINE_API MapStringSpriteRenderer : public map<string, SpriteRenderer*> {};
	class CREAENGINE_API MapStringMapRenderer : public map<string, MapRenderer*> {};
	class CREAENGINE_API MapStringAnimatedSpriteRenderer : public map<string, AnimatedSpriteRenderer*> {};

	class CREAENGINE_API EntityManager
	{
		MapStringTextRenderer m_pTextRenderers;

		MapStringSpriteRenderer m_pSpriteRenderers;

		MapStringMapRenderer m_pMapRenderers;

		MapStringAnimatedSpriteRenderer m_pAnimatedSpriteRenderers;

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

		AnimatedSpriteRenderer* getAnimatedSpriteRenderer(string _szName, bool _bCloned = false);

		bool update();

		bool draw();

		void clear();
	};

} // namespace crea

#endif
