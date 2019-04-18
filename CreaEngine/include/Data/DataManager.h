/***************************************************/
/* Nom:	DataManager.h
/* Description: DataManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __DATAMANAGER_H_
#define __DATAMANAGER_H_
#include <map>
using namespace std;

#define DATAFONTPATH	"data/Font/"
#define DATATEXTUREPATH "data/Image/"
#define DATAMAPPATH		"data/Map/"
#define DATAAGENTPATH	"data/Agent/"
#define DATAANIMATIONPATH	"data/Animation/"

namespace crea
{
	class Font;
	class Texture;
	class Color;
	class Text;
	class Sprite;
	class Shape;
	class Map;
	class Agent;
	class Animation;
	class ActionTable;
	class Vehicle;

	class CREAENGINE_API MapStringFont : public map<string, Font*> {};
	class CREAENGINE_API MapStringTexture : public map<string, Texture*> {};
	class CREAENGINE_API MapStringColor : public map<string, Color*> {};
	class CREAENGINE_API MapStringText : public map<string, Text*> {};
	class CREAENGINE_API MapStringSprite : public map<string, Sprite*> {};
	class CREAENGINE_API MapStringShape : public map<string, Shape*> {};
	class CREAENGINE_API MapStringMap : public map<string, Map*> {};
	class CREAENGINE_API MapStringAgent : public map<string, Agent*> {};
	class CREAENGINE_API MapStringAnimation : public map<string, Animation*> {};
	class CREAENGINE_API MapStringActionTable : public map<string, ActionTable*> {};
	class CREAENGINE_API MapStringVehicle : public map<string, Vehicle*> {};

	class CREAENGINE_API DataManager
	{
		MapStringFont m_pFonts;

		MapStringTexture m_pTextures;

		MapStringColor m_pColors;

		MapStringText m_pTexts;

		MapStringSprite m_pSprites;

		MapStringShape m_pShapes;

		MapStringMap m_pMaps;

		MapStringAgent m_pAgents;

		MapStringAnimation m_pAnimations;

		MapStringActionTable m_pActionTables;

		MapStringVehicle m_pVehicles;

		bool m_bIsCleared;

		DataManager();

	public:
		virtual ~DataManager();

		static DataManager* getSingleton();

		Font* getFont(const string& _szName, bool _bCloned = false);

		Texture* getTexture(const string& _szName, bool _bCloned = false);

		Color* getColor(const string& _szName, bool _bCloned = false);

		Text* getText(const string& _szName, bool _bCloned = false);

		Sprite* getSprite(const string& _szName, bool _bCloned = false);

		Shape* getShape(const string& _szType, const string& _szName, bool _bCloned = false);

		Map* getMap(const string& _szName, bool _bCloned = false);

		Agent* getAgent(const string& _szName, bool _bCloned = false);

		Animation* getAnimation(const string& _szName, bool _bCloned = false);

		ActionTable* getActionTable(const string& _szName, bool _bCloned = false);

		Vehicle* getVehicle(string _szName, bool _bCloned = false);

		void clear();
	};

} // namespace crea

#endif
