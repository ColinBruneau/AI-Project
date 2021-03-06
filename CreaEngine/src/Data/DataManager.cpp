#include "stdafx.h"

#include "Data\DataManager.h"
#include "Graphics\Color.h"

namespace crea
{
	DataManager::DataManager()
	{
		m_bIsCleared = false;
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

	Font* DataManager::getFont(const string& _szName, bool _bCloned)
	{
		MapStringFont::iterator it = m_pFonts.find(_szName);
		if (it == m_pFonts.end())
		{
			Font* pFont = IFacade::get().createFont();

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
				return IFacade::get().createFont(it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	Texture* DataManager::getTexture(const string& _szName, bool _bCloned)
	{
		MapStringTexture::iterator it = m_pTextures.find(_szName);
		if (it == m_pTextures.end())
		{
			Texture* pTexture = IFacade::get().createTexture();

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
				return IFacade::get().createTexture(it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	Color* DataManager::getColor(const string& _szName, bool _bCloned)
	{
		MapStringColor::iterator it = m_pColors.find(_szName);
		if (it == m_pColors.end())
		{
			Color* pColor = IFacade::get().createColor(); // Create a default Color if none exist
			m_pColors[_szName] = pColor;
			return pColor;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createColor(it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Text* DataManager::getText(const string& _szName, bool _bCloned)
	{
		MapStringText::iterator it = m_pTexts.find(_szName);
		if (it == m_pTexts.end())
		{
			Text* pText = IFacade::get().createText(); // Create a default Text if none exist
			m_pTexts[_szName] = pText;
			return pText;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createText(it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Sprite* DataManager::getSprite(const string& _szName, bool _bCloned)
	{
		MapStringSprite::iterator it = m_pSprites.find(_szName);
		if (it == m_pSprites.end())
		{
			Sprite* pSprite = IFacade::get().createSprite(); // Create a default Sprite if none exist
			m_pSprites[_szName] = pSprite;
			return pSprite;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createSprite(it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Shape* DataManager::getShape(const string& _szType, const string& _szName, bool _bCloned)
	{
		MapStringShape::iterator it = m_pShapes.find(_szName);
		if (it == m_pShapes.end())
		{
			Shape* pShape = IFacade::get().createShape(_szType); // Create a default Shape if none exist
			m_pShapes[_szName] = pShape;
			return pShape;
		}
		else
		{
			if (_bCloned)
			{
				return IFacade::get().createShape(_szType, it->second);
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Map* DataManager::getMap(const string& _szName, bool _bCloned)
	{
		MapStringMap::iterator it = m_pMaps.find(_szName);
		if (it == m_pMaps.end())
		{
			Map* pMap = new Map();
			m_pMaps[_szName] = pMap;
			return pMap;
		}
		else
		{
			if (_bCloned)
			{
				return new Map(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	Agent* DataManager::getAgent(const string& _szName, bool _bCloned)
	{
		MapStringAgent::iterator it = m_pAgents.find(_szName);
		if (it == m_pAgents.end())
		{
			Agent* pAgent = new Agent();
			m_pAgents[_szName] = pAgent;
			return pAgent;
		}
		else
		{
			if (_bCloned)
			{
				return new Agent(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	Animation* DataManager::getAnimation(const string& _szName, bool _bCloned)
	{
		MapStringAnimation::iterator it = m_pAnimations.find(_szName);
		if (it == m_pAnimations.end())
		{
			Animation* pAnimation = new Animation();

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
				return new Animation(*it->second);
			}
			else
			{
				return it->second;
			}
		}
	}

	ActionTable* DataManager::getActionTable(const string& _szName, bool _bCloned)
	{
		MapStringActionTable::iterator it = m_pActionTables.find(_szName);
		if (it == m_pActionTables.end())
		{
			ActionTable* pActionTable = new ActionTable(); // Create a default ActionTable if none exist
			if (!pActionTable->loadFromFileJSON(DATAANIMATIONPATH + _szName))
			{
				delete pActionTable;
				cerr << "Unable to open ActionTable" << endl;
				return nullptr;
			}
			m_pActionTables[_szName] = pActionTable;
			return pActionTable;
		}
		else
		{
			if (_bCloned)
			{
				//return new ActionTable(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Vehicle* DataManager::getVehicle(const string& _szName, bool _bCloned)
	{
		MapStringVehicle::iterator it = m_pVehicles.find(_szName);
		if (it == m_pVehicles.end())
		{
			Vehicle* pVehicle = new Vehicle(); // Create a default Vehicle if none exist
			if (!pVehicle->loadFromFileJSON(DATAAGENTPATH + _szName))
			{
				delete pVehicle;
				cerr << "Unable to open Vehicle" << endl;
				return nullptr;
			}
			m_pVehicles[_szName] = pVehicle;
			return pVehicle;
		}
		else
		{
			if (_bCloned)
			{
				//return new Vehicle(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Material* DataManager::getMaterial(const string& _szName, bool _bCloned)
	{
		MapStringMaterial::iterator it = m_pMaterials.find(_szName);
		if (it == m_pMaterials.end())
		{
			Material* pMaterial = IFacade::get().createMaterial(); // Create a default Material if none exist
			if (!pMaterial->loadFromFile(DATAMATERIALPATH + _szName))
			{
				delete pMaterial;
				cerr << "Unable to open Material" << endl;
				return nullptr;
			}
			m_pMaterials[_szName] = pMaterial;
			return pMaterial;
		}
		else
		{
			if (_bCloned)
			{
				Material* pMaterial = (Material*)it->second->clone();
				m_pMaterials[_szName + to_string(++materialInstanceCount)] = pMaterial;
				return pMaterial;
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Shader* DataManager::getShader(const string& _szName, bool _bCloned)
	{
		MapStringShader::iterator it = m_pShaders.find(_szName);
		if (it == m_pShaders.end())
		{
			Shader* pShader = IFacade::get().createShader(); // Create a default Shader if none exist
			if (!pShader->loadFromFile(DATASHADERPATH + _szName))
			{
				delete pShader;
				cerr << "Unable to open Shader" << endl;
				return nullptr;
			}
			m_pShaders[_szName] = pShader;
			return pShader;
		}
		else
		{
			if (_bCloned)
			{
				//return new Shader(it->second); // CB is it useful to clone?
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
		if (!m_bIsCleared)
		{
			m_bIsCleared = true;
		}
		else
		{
			return;
		}

		MapStringFont::iterator itFont = m_pFonts.begin();
		while (itFont != m_pFonts.end()) {
			delete (*itFont).second;
			itFont = m_pFonts.erase(itFont);
		}

		// Clean Materials before textures
		MapStringMaterial::iterator itMaterial = m_pMaterials.begin();
		while (m_pMaterials.size()) {
			delete (*itMaterial).second;
			itMaterial = m_pMaterials.erase(itMaterial);
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

		MapStringShape::iterator itShape = m_pShapes.begin();
		while (itShape != m_pShapes.end()) {
			delete (*itShape).second;
			itShape = m_pShapes.erase(itShape);
		}

		MapStringMap::iterator itMap = m_pMaps.begin();
		while (itMap != m_pMaps.end()) {
			delete (*itMap).second;
			itMap = m_pMaps.erase(itMap);
		}

		MapStringAgent::iterator itAgent = m_pAgents.begin();
		while (itAgent != m_pAgents.end()) {
			delete (*itAgent).second;
			itAgent = m_pAgents.erase(itAgent);
		}

		MapStringAnimation::iterator itAnimation = m_pAnimations.begin();
		while (itAnimation != m_pAnimations.end()) {
			delete (*itAnimation).second;
			itAnimation = m_pAnimations.erase(itAnimation);
		}

		MapStringActionTable::iterator itActionTable = m_pActionTables.begin();
		while (m_pActionTables.size()) {
			delete (*itActionTable).second;
			itActionTable = m_pActionTables.erase(itActionTable);
		}

		MapStringVehicle::iterator itVehicle = m_pVehicles.begin();
		while (m_pVehicles.size()) {
			delete (*itVehicle).second;
			itVehicle = m_pVehicles.erase(itVehicle);
		}

		MapStringShader::iterator itShader = m_pShaders.begin();
		while (m_pShaders.size()) {
			delete (*itShader).second;
			itShader = m_pShaders.erase(itShader);

		}
	}

} // namespace crea
