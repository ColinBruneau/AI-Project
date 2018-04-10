#include "stdafx.h"

#include "Core\DataManager.h"
#include "AI\ActionTable.h"
#include "AI\Agent.h"
#include "Graphics\IFont.h"
#include "Graphics\ITexture.h"
#include "Graphics\IGraphics.h"
#include "Graphics\IText.h"
#include "Graphics\ISprite.h"
#include "Data\Map.h"
#include "Physics\Collider.h"

namespace crea
{
	DataManager::DataManager()
	{

	}

	DataManager::~DataManager()
	{
		clear();
	}

	DataManager* DataManager::getSingleton()
	{
		static DataManager instanceUnique;
		return
			&instanceUnique;
	}

	IFont* DataManager::getFont(string _szName, bool _bCloned)
	{
		MapStringFont::iterator it = m_pFonts.find(_szName);
		if (it == m_pFonts.end())
		{
			IFont* pFont = IFacade::get().createIFont();

			if (!pFont->loadFromFile(DATAFONTPATH + _szName))
			{
				delete pFont;
				cerr << "Unable to open font" << endl;
				return nullptr;
			}
			m_pFonts[_szName] = pFont;
			return pFont;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createIFont(it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	ITexture* DataManager::getTexture(string _szName, bool _bCloned)
	{
		MapStringTexture::iterator it = m_pTextures.find(_szName);
		if (it == m_pTextures.end())
		{
			ITexture* pTexture = IFacade::get().createITexture();

			if (!pTexture->loadFromFile(DATATEXTUREPATH + _szName))
			{
				delete pTexture;
				cerr << "Unable to open Texture " << _szName << endl;
				return nullptr;
			}
			m_pTextures[_szName] = pTexture;
			return pTexture;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createITexture(it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	IColor* DataManager::getColor(string _szName, bool _bCloned)
	{
		MapStringColor::iterator it = m_pColors.find(_szName);
		if (it == m_pColors.end())
		{
			IColor* pColor = IFacade::get().createIColor(); // Create a default Color if none exist
			m_pColors[_szName] = pColor;
			return pColor;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createIColor(it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	IText* DataManager::getText(string _szName, bool _bCloned)
	{
		MapStringText::iterator it = m_pTexts.find(_szName);
		if (it == m_pTexts.end())
		{
			IText* pText = IFacade::get().createIText(); // Create a default Text if none exist
			m_pTexts[_szName] = pText;
			return pText;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createIText(it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	ISprite* DataManager::getSprite(string _szName, bool _bCloned)
	{
		MapStringSprite::iterator it = m_pSprites.find(_szName);
		if (it == m_pSprites.end())
		{
			ISprite* pSprite = IFacade::get().createISprite(); // Create a default Sprite if none exist
			m_pSprites[_szName] = pSprite;
			return pSprite;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createISprite(it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	crea::Animation* DataManager::getAnimation(string _szName, bool _bCloned)
	{
		MapStringAnimation::iterator it = m_pAnimations.find(_szName);
		if (it == m_pAnimations.end())
		{
			crea::Animation* pAnimation = new crea::Animation();

			if (!pAnimation->loadFromFileJSON(DATAANIMATIONPATH + _szName))
			{
				delete pAnimation;
				cerr << "Unable to open Animation" << endl;
				return nullptr;
			}
			m_pAnimations[_szName] = pAnimation;
			return pAnimation;
		}
		else
		{
			if (_bCloned)
			{
				return new crea::Animation(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	crea::ActionTable* DataManager::getActionTable(string _szName, bool _bCloned)
	{
		MapStringActionTable::iterator it = m_pActionTables.find(_szName);
		if (it == m_pActionTables.end())
		{
			crea::ActionTable* pActionTable = new crea::ActionTable();

			if (!pActionTable->loadFromFileJSON(DATAANIMATIONPATH + _szName))
			{
				delete pActionTable;
				cerr << "Unable to open ActionTable file" << endl;
				return nullptr;
			}
			m_pActionTables[_szName] = pActionTable;
			return pActionTable;
		}
		else
		{
			if (_bCloned)
			{
				return new crea::ActionTable(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	crea::Agent* DataManager::getAgent(string _szName, bool _bCloned)
	{
		MapStringAgent::iterator it = m_pAgents.find(_szName);
		if (it == m_pAgents.end())
		{
			crea::Agent* pAgent = new crea::Agent();

			if (!pAgent->loadFromFileJSON(DATAAGENTPATH + _szName))
			{
				delete pAgent;
				cerr << "Unable to open Agent file" << endl;
				return nullptr;
			}
			m_pAgents[_szName] = pAgent;
			return pAgent;
		}
		else
		{
			if (_bCloned)
			{
				return new crea::Agent(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	crea::Map* DataManager::getMap(string _szName, bool _bCloned)
	{
		MapStringMap::iterator it = m_pMaps.find(_szName);
		if (it == m_pMaps.end())
		{
			crea::Map* pMap = new crea::Map();

			if (!pMap->loadFromFileJSON(DATAMAPPATH + _szName))
			{
				delete pMap;
				cerr << "Unable to open Map file" << endl;
				return nullptr;
			}
			m_pMaps[_szName] = pMap;
			return pMap;
		}
		else
		{
			if (_bCloned)
			{
				return new crea::Map(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	Collider* DataManager::getCollider(string _szName, bool _bCloned)
	{
		MapStringCollider::iterator it = m_pColliders.find(_szName);
		if (it == m_pColliders.end())
		{
			Collider* pCollider = new Collider(); // Create a default Collider if none exist

			if (!pCollider->loadFromFileJSON(DATAAGENTPATH + _szName))
			{
				delete pCollider;
				cerr << "Unable to open Collider file" << endl;
				return nullptr;
			}

			m_pColliders[_szName] = pCollider;
			return pCollider;
		}
		else
		{
			if (_bCloned)
			{
				//return new Collider(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	void DataManager::clear()
	{
		MapStringFont::iterator itFont = m_pFonts.begin();
		while (m_pFonts.size()) {
			IFacade::get().destroyIFont((*itFont).second);
			itFont = m_pFonts.erase(itFont);
		}

		MapStringTexture::iterator itTexture = m_pTextures.begin();
		while (m_pTextures.size()) {
			IFacade::get().destroyITexture((*itTexture).second);
			itTexture = m_pTextures.erase(itTexture);
		}

		MapStringColor::iterator itColor = m_pColors.begin();
		while (m_pColors.size()) {
			IFacade::get().destroyIColor((*itColor).second);
			itColor = m_pColors.erase(itColor);
		}

		MapStringText::iterator itText = m_pTexts.begin();
		while (m_pTexts.size()) {
			IFacade::get().destroyIText((*itText).second);
			itText = m_pTexts.erase(itText);
		}

		MapStringSprite::iterator itSprite = m_pSprites.begin();
		while (m_pSprites.size()) {
			IFacade::get().destroyISprite((*itSprite).second);
			itSprite = m_pSprites.erase(itSprite);
		}

		MapStringAnimation::iterator itAnimation = m_pAnimations.begin();
		while (m_pAnimations.size()) {
			delete (*itAnimation).second;
			itAnimation = m_pAnimations.erase(itAnimation);
		}

		MapStringActionTable::iterator itActionTable = m_pActionTables.begin();
		while (m_pActionTables.size()) {
			delete (*itActionTable).second;
			itActionTable = m_pActionTables.erase(itActionTable);
		}

		MapStringAgent::iterator itAgent = m_pAgents.begin();
		while (m_pAgents.size()) {
			delete (*itAgent).second;
			itAgent = m_pAgents.erase(itAgent);
		}

		MapStringMap::iterator itMap = m_pMaps.begin();
		while (m_pMaps.size()) {
			delete (*itMap).second;
			itMap = m_pMaps.erase(itMap);
		}

		MapStringCollider::iterator itCollider = m_pColliders.begin();
		while (m_pColliders.size()) {
			delete (*itCollider).second;
			itCollider = m_pColliders.erase(itCollider);
		}

	}

} // namespace crea
