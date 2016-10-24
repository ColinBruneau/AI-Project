#include "stdafx.h"

#include "Core\DataManager.h"
#include "AI\ActionTable.h"
#include "Graphics\IFont.h"
#include "Graphics\ITexture.h"
#include "Graphics\IGraphics.h"
#include "Graphics\IText.h"
#include "Graphics\ISprite.h"
#include "Data\Map.h"

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
			IFont* pFont = IRenderer::get().createIFont();

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
				return IRenderer::get().createIFont(it->second);
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
			ITexture* pTexture = IRenderer::get().createITexture();

			if (!pTexture->loadFromFile(DATATEXTUREPATH + _szName))
			{
				delete pTexture;
				cerr << "Unable to open Texture" << endl;
				return nullptr;
			}
			m_pTextures[_szName] = pTexture;
			return pTexture;
		}
		else
		{
			if (_bCloned)
			{
				return IRenderer::get().createITexture(it->second);
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
			IColor* pColor = IRenderer::get().createIColor(); // Create a default Color if none exist
			m_pColors[_szName] = pColor;
			return pColor;
		}
		else
		{
			if (_bCloned)
			{
				return IRenderer::get().createIColor(it->second);
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
			IText* pText = IRenderer::get().createIText(); // Create a default Text if none exist
			m_pTexts[_szName] = pText;
			return pText;
		}
		else
		{
			if (_bCloned)
			{
				return IRenderer::get().createIText(it->second);
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
			ISprite* pSprite = IRenderer::get().createISprite(); // Create a default Sprite if none exist
			m_pSprites[_szName] = pSprite;
			return pSprite;
		}
		else
		{
			if (_bCloned)
			{
				return IRenderer::get().createISprite(it->second);
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

			if (!pAnimation->loadFromFile(DATAANIMATIONPATH + _szName))
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

	AnimatedSprite* DataManager::getAnimatedSprite(string _szName, bool _bCloned)
	{
		MapStringAnimatedSprite::iterator it = m_pAnimatedSprites.find(_szName);
		if (it == m_pAnimatedSprites.end())
		{
			AnimatedSprite* pAnimatedSprite = new AnimatedSprite(); // Create a default AnimatedSprite if none exist
			m_pAnimatedSprites[_szName] = pAnimatedSprite;
			return pAnimatedSprite;
		}
		else
		{
			if (_bCloned)
			{
				return new AnimatedSprite();
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
		while (itFont != m_pFonts.end()) {
			delete (*itFont).second;
			itFont = m_pFonts.erase(itFont);
		}

		MapStringTexture::iterator itTexture = m_pTextures.begin();
		while (itTexture != m_pTextures.end()) {
			delete (*itTexture).second;
			itTexture = m_pTextures.erase(itTexture);
		}

		MapStringColor::iterator itColor = m_pColors.begin();
		while (itColor != m_pColors.end()) {
			delete (*itColor).second;
			itColor = m_pColors.erase(itColor);
		}

		MapStringText::iterator itText = m_pTexts.begin();
		while (itText != m_pTexts.end()) {
			delete (*itText).second;
			itText = m_pTexts.erase(itText);
		}

		MapStringSprite::iterator itSprite = m_pSprites.begin();
		while (itSprite != m_pSprites.end()) {
			delete (*itSprite).second;
			itSprite = m_pSprites.erase(itSprite);
		}

		MapStringAnimation::iterator itAnimation = m_pAnimations.begin();
		while (itAnimation != m_pAnimations.end()) {
			delete (*itAnimation).second;
			itAnimation = m_pAnimations.erase(itAnimation);
		}

		MapStringActionTable::iterator itActionTable = m_pActionTables.begin();
		while (itActionTable != m_pActionTables.end()) {
			delete (*itActionTable).second;
			itActionTable = m_pActionTables.erase(itActionTable);
		}

		MapStringMap::iterator itMap = m_pMaps.begin();
		while (itMap != m_pMaps.end()) {
			delete (*itMap).second;
			itMap = m_pMaps.erase(itMap);
		}

		MapStringAnimatedSprite::iterator itAnimatedSprite = m_pAnimatedSprites.begin();
		while (itAnimatedSprite != m_pAnimatedSprites.end()) {
			delete (*itAnimatedSprite).second;
			itAnimatedSprite = m_pAnimatedSprites.erase(itAnimatedSprite);
		}
	}

} // namespace crea