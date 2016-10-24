#include "stdafx.h"

#include "Data\Map.h"
#include "Data\Node.h"
#include "json\json.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graphics\ISprite.h"

namespace crea
{
	Map::Map()
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_nTileWidth = 0;
		m_nTileHeight = 0;
		m_bIsGrid8 = false;
		m_bDisplayCollision = false;
	}

	Map::~Map()
	{
		clear();
		m_nWidth = 0;
		m_nHeight = 0;
	}

	bool Map::loadFromFileJSON(string& _filename)
	{
		Json::Value root;
		std::ifstream mapStream(_filename, std::ifstream::binary);
		if (mapStream.fail())
		{
			cerr << "Can't open map file!" << endl;
			return false;
		}

		crea::GameManager*	pGM = crea::GameManager::getSingleton();

		setName(_filename);

		// Parse file
		mapStream >> root;

		int version = root.get("version", 0).asInt();
		if (version != 1)
		{
			cerr << "Can't parse map if version != 1" << endl;
			return false;
		}

		int iWidth = root.get("width", 10).asInt();
		int iHeight = root.get("height", 10).asInt();
		// Create all nodes
		setSize(iWidth, iHeight);

		m_nTileWidth = root.get("tilewidth", 10).asInt();
		m_nTileHeight = root.get("tileheight", 10).asInt();
		
		//Tilesets (load tilesets first as layers will refer to them...)
		Json::Value tilesets = root["tilesets"];
		for (unsigned int iTileset = 0; iTileset < tilesets.size(); ++iTileset)
		{
			Json::Value tileset = tilesets[iTileset];

			// Create a tileset
			TileSet* pTileSet = new TileSet();

			pTileSet->m_nColumns = tileset["columns"].asInt();
			pTileSet->m_nFirstgid = tileset["firstgid"].asInt();
			string image = tileset["image"].asString();
			pTileSet->m_nImageheight = tileset["imageheight"].asInt();
			pTileSet->m_nImagewidth = tileset["imagewidth"].asInt();
			pTileSet->m_nMargin = tileset["margin"].asInt();
			string name = tileset["name"].asString();
			pTileSet->m_nSpacing = tileset["spacing"].asInt();
			// terrain not useful?
			pTileSet->m_nTilecount = tileset["tilecount"].asInt();
			pTileSet->m_nTileheight = tileset["tileheight"].asInt();
			pTileSet->m_nTilewidth = tileset["tilewidth"].asInt();

			// Load Image and create sprite
			pTileSet->m_pSprite = pGM->getSprite(name);
			pTileSet->m_pSprite->setTexture(pGM->getTexture(image));

			//  Tiles
			if (pTileSet->m_nTilecount > 1)
			{
				Json::Value tiles = tileset["tiles"];
				/*
				for (short i = 1; i <= tilecount; i++)
				{
				Json::Value tile = tiles.get(; // Comment récupérer une key?
				Json::Value terrain = tile["terrain"];
				int topleft = terrain[0].asInt();
				int topright = terrain[1].asInt();
				int bottomleft = terrain[2].asInt();
				int bottomright = terrain[3].asInt();
				}
				*/
			}

			m_TileSet.push_back(pTileSet);
		}

		// Layers
		Json::Value layers = root["layers"];
		for (unsigned int iLayer = 0; iLayer < layers.size(); ++iLayer)
		{
			Json::Value layer = layers[iLayer];
			int iHeight = layer["height"].asInt();
			int iWidth = layer["width"].asInt();
			int iX = layer["x"].asInt();
			int iY = layer["y"].asInt();
			string type = layer["type"].asString();
			if (type == "tilelayer")
			{
				bool bIsTerrain = (layer["name"].asString() == "Terrain");
				bool bIsCollision = (layer["name"].asString() == "Collision");
				Json::Value data = layer["data"];
				for (short i = 0; i < iWidth; i++)
				{
					for (short j = 0; j < iHeight; j++)
					{
						short nIndex = (short)data[j*iWidth + i].asInt();
						if (bIsTerrain)
						{
							m_Grid[i][j]->setTileTerrainId(nIndex);
						}
						else if (bIsCollision)
						{
							m_Grid[i][j]->setTileCollisionId(nIndex);
						}
					}
				}
			}
			else if (type == "objectgroup")
			{
				bool bIsPersos = (layer["name"].asString() == "Persos");
				if (bIsPersos)
				{
					Json::Value objects = layer["objects"];
					for (unsigned int iObject = 0; iObject < objects.size(); ++iObject)
					{
						Json::Value object = objects[iObject];
						int iPersoHeight = object["height"].asInt();
						int iPersoWidth = object["width"].asInt();
						int iPersoX = object["x"].asInt();
						int iPersoY = object["y"].asInt();
						int iRotation = object["rotation"].asInt();
						int iId = object["id"].asInt();
						int iGId = object["gid"].asInt();
						string szName = object["name"].asString();
						string szType = object["type"].asString();
						bool bVisible = object["visible"].asBool();

						// Create entity
						// A sprite is a gid linked to a tileset that is loaded before in function
						TileSet* pTileSet = getTileSet(iGId);
						pTileSet->m_pSprite->setPosition((float)iPersoX, (float)(iPersoY - iPersoHeight));
						
						SpriteRenderer* pSpriteRenderer = nullptr;
						if (bVisible)
						{
							pSpriteRenderer = new crea::SpriteRenderer();
							pSpriteRenderer->setSprite(pTileSet->m_pSprite);
						}
						
						Entity* pEntity = pGM->getEntity(szName);
						pEntity->addComponent(pSpriteRenderer);

						pGM->addEntity(pEntity);

					}
				}
			}
		}

		return true;
	}

	void Map::setSize(short _nWidth, short _nHeight)
	{
		clear();
		m_nWidth = _nWidth;
		m_nHeight = _nHeight;
		m_Grid.assign(m_nWidth, vector<Node*>(m_nHeight, new Node()));
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				m_Grid[i][j] = new Node(i, j);
			}
		}

		// Set Neighbors
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				if (j != 0)
				{
					m_Grid[i][j]->addChild(m_Grid[i][j - 1]); // top node
				}
				if (m_bIsGrid8 && j != 0 && i != m_nWidth - 1)
				{
					m_Grid[i][j]->addChild(m_Grid[i + 1][j - 1]); // top-right node
				}
				if (i != m_nWidth - 1)
				{
					m_Grid[i][j]->addChild(m_Grid[i + 1][j]); // right node
				}
				if (m_bIsGrid8 && i != m_nWidth - 1 && j != m_nHeight - 1)
				{
					m_Grid[i][j]->addChild(m_Grid[i + 1][j + 1]); // bottom-right node
				}
				if (j != m_nHeight - 1)
				{
					m_Grid[i][j]->addChild(m_Grid[i][j + 1]); // bottom node
				}
				if (m_bIsGrid8 && i != 0 && j != m_nHeight - 1)
				{
					m_Grid[i][j]->addChild(m_Grid[i - 1][j + 1]); // bottom-left node
				}
				if (i != 0)
				{
					m_Grid[i][j]->addChild(m_Grid[i - 1][j]); // left node
				}
				if (m_bIsGrid8 && i != 0 && j != 0)
				{
					m_Grid[i][j]->addChild(m_Grid[i - 1][j - 1]); // top-left node
				}
			}
		}

	}

	TileSet* Map::getTileSet(short _gid)
	{
		TileSet* pTileSet = nullptr;
		for (short i = 0; i < (short) m_TileSet.size(); i++)
		{
			pTileSet = m_TileSet[i];
			if (_gid >= pTileSet->m_nFirstgid && _gid < pTileSet->m_nFirstgid + pTileSet->m_nTilecount)
			{
				return pTileSet;
			}
		}
		return pTileSet;
	}

	bool Map::update()
	{
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				m_Grid[i][j]->update();
			}
		}
		return true;
	}

	bool Map::draw()
	{
		int tileid = 0, w = 0, h = 0, x = 0, y = 0;
		TileSet* pTileSet = m_TileSet[0]; // CB: how to specify this tileset?
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				tileid = m_Grid[i][j]->getTileTerrainId() - 1; // 30 -> 29
				
				if (m_bDisplayCollision)
				{
					short tileCollisionId = m_Grid[i][j]->getTileCollisionId() - 1; 
					if (tileCollisionId != -1)
					{
						tileid = tileCollisionId; // Display collision only if valid
					}
				}
				
				w = pTileSet->m_nTilewidth;
				h = pTileSet->m_nTileheight;
				x = (tileid % pTileSet->m_nColumns) * (w + pTileSet->m_nMargin) + pTileSet->m_nMargin; // 1st margin
				y = (tileid / pTileSet->m_nColumns) * (h + pTileSet->m_nSpacing) + pTileSet->m_nSpacing; // 1st spacing 
				pTileSet->m_pSprite->setTextureRect(x, y, w, h);
				pTileSet->m_pSprite->setPosition((float)i*w, (float)j*h);
				pTileSet->m_pSprite->draw();
			}
		}
		return true;
	}

	void Map::clear()
	{
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				delete m_Grid[i][j];
			}
		}
	}
} // namespace crea
