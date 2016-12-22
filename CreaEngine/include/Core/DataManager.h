/***************************************************/
/* Nom:	DataManager.h
/* Description: DataManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __DATAMANAGER_H_
#define __DATAMANAGER_H_
#include <map>
using namespace std;

#define DATAFONTPATH		"data/Font/"
#define DATATEXTUREPATH		"data/Image/"
#define DATAANIMATIONPATH	"data/Animation/"
#define DATAMAPPATH			"data/Map/"
#define DATAAGENTPATH		"data/Agent/"

// Prédéfinitions
namespace crea
{
	class IFont;
	class ITexture;
	class IColor;
	class IText;
	class ISprite;
	class Animation;
	class ActionTable;
	class AnimatedSprite;
	class Map;
	class Agent;
	class Collider;
}

namespace crea
{
	class CREAENGINE_API MapStringFont : public map<string, IFont*> {};
	class CREAENGINE_API MapStringTexture : public map<string, ITexture*> {};
	class CREAENGINE_API MapStringColor : public map<string, IColor*> {};
	class CREAENGINE_API MapStringText : public map<string, IText*> {};
	class CREAENGINE_API MapStringSprite : public map<string, ISprite*> {};
	class CREAENGINE_API MapStringAnimation : public map<string, Animation*> {};
	class CREAENGINE_API MapStringActionTable : public map<string, ActionTable*> {};
	class CREAENGINE_API MapStringMap : public map<string, Map*> {};
	class CREAENGINE_API MapStringAnimatedSprite : public map<string, AnimatedSprite*> {};
	class CREAENGINE_API MapStringAgent : public map<string, Agent*> {};
	class CREAENGINE_API MapStringCollider : public map<string, Collider*> {};

	class CREAENGINE_API DataManager
	{
		MapStringFont m_pFonts;

		MapStringTexture m_pTextures;

		MapStringColor m_pColors;

		MapStringText m_pTexts;

		MapStringSprite m_pSprites;

		MapStringAnimation m_pAnimations;

		MapStringActionTable m_pActionTables;

		MapStringAgent m_pAgents;

		MapStringMap m_pMaps;

		MapStringAnimatedSprite m_pAnimatedSprites;

		MapStringCollider m_pColliders;

		DataManager();

	public:
		virtual ~DataManager();

		static DataManager* getSingleton();

		IFont* getFont(string _szName, bool _bCloned = false);

		ITexture* getTexture(string _szName, bool _bCloned = false);

		IColor* getColor(string _szName, bool _bCloned = false);

		IText* getText(string _szName, bool _bCloned = false);

		ISprite* getSprite(string _szName, bool _bCloned = false);

		Animation* getAnimation(string _szName, bool _bCloned = false);
		
		ActionTable* getActionTable(string _szName, bool _bCloned = false);

		Agent* getAgent(string _szName, bool _bCloned = false);

		Map* getMap(string _szName, bool _bCloned = false);

		Collider* getCollider(string _szName, bool _bCloned = false);
		
		void clear();
	};

} // namespace crea

#endif
