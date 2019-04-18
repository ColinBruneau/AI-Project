#include "stdafx.h"

#include "Data\Map.h"
#include "Data\Node.h"
#include "Graphics\Sprite.h"

namespace crea
{
	Map::Map()
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_nTileWidth = 0;
		m_nTileHeight = 0;
		m_bIsGrid8 = false;
		m_pTerrainTileSet = nullptr;
		m_pGM = crea::GameManager::getSingleton();
		m_Clusters = nullptr;
		m_bUseHPA = false;
		m_bUseAStar = false;
		m_bUseAA = false;
	}

	Map::~Map()
	{
		clear();
		m_nWidth = 0;
		m_nHeight = 0;
	}

	// Remove path
	string getFileName(const string& _fullName, const string& _fromName)
	{
		size_t s = _fullName.size();
		int quotePos = _fullName.rfind(_fromName, s); //finds last quote mark
		return _fullName.substr(quotePos + _fromName.size(), s - quotePos);
	}

	bool Map::loadFromFileJSON(const string& _filename)
	{
		Json::Value root;
		std::ifstream mapStream(_filename, std::ifstream::binary);
		if (mapStream.fail())
		{
			cerr << "Can't open map file: " << _filename << endl;
			return false;
		}

		setName(_filename);

		// Parse file
		mapStream >> root;

		float version = root.get("version", 0).asFloat();
		if (version < 1.0f || version > 1.2f)
		{
			cerr << "Can't parse map if version < 1.0 or > 1.2" << endl;
			return false;
		}

		int iWidth = root.get("width", 10).asInt();
		int iHeight = root.get("height", 10).asInt();
		// Create all nodes
		setSize(iWidth, iHeight);

		m_nTileWidth = root.get("tilewidth", 10).asInt();
		m_nTileHeight = root.get("tileheight", 10).asInt();

		updateTileIndexLimits();

		//Tilesets (load tilesets first as layers will refer to them...)
		Json::Value tilesets = root["tilesets"];
		for (unsigned int iTileset = 0; iTileset < tilesets.size(); ++iTileset)
		{
			Json::Value tileset = tilesets[iTileset];
			if (version == 1.2f)
			{
				string source = tileset.get("source", "none").asString();
				if (source != "none")
				{
					cerr << "Can't parse map if tileset not embeded in map (version 1.2) " << endl;
					return false;
				}
			}

			// Create a tileset
			TileSet* pTileSet = new TileSet();
			pTileSet->m_nColumns = tileset["columns"].asInt();
			pTileSet->m_nFirstgid = tileset["firstgid"].asInt();
			string image = getFileName(tileset["image"].asString(), "Image/");
			pTileSet->m_nImageheight = tileset["imageheight"].asInt();
			pTileSet->m_nImagewidth = tileset["imagewidth"].asInt();
			pTileSet->m_nMargin = tileset["margin"].asInt();
			pTileSet->m_szName = tileset["name"].asString();
			pTileSet->m_nSpacing = tileset["spacing"].asInt();
			pTileSet->m_nTilecount = tileset["tilecount"].asInt();
			pTileSet->m_nTileheight = tileset["tileheight"].asInt();
			pTileSet->m_nTilewidth = tileset["tilewidth"].asInt();
			pTileSet->m_vTileOffset = Vector2f((float)tileset["tileoffset"]["x"].asInt(), (float)tileset["tileoffset"]["y"].asInt());

			if (pTileSet->m_szName == "Terrain")
			{
				m_pTerrainTileSet = pTileSet;
			}
			else if (pTileSet->m_szName == "Clearance")
			{
				m_pClearanceTileSet = pTileSet;
			}

			// terrain 
			Json::Value terrains = tileset["terrains"];
			for (unsigned int iTerrain = 0; iTerrain < terrains.size(); ++iTerrain)
			{
				Json::Value terrain = terrains[iTerrain];
				Terrain* pTerrain = new Terrain();
				pTerrain->m_szName = terrain["name"].asString();
				pTerrain->m_nTile = terrain["tile"].asInt();
				if (version == 1.0f)
				{
					pTerrain->m_fFriction = terrain["properties"]["Friction"].asFloat();
				}
				else if (version == 1.2f)
				{
					Json::Value properties = terrain["properties"];
					for (unsigned int iProperties = 0; iProperties < properties.size(); ++iProperties)
					{
						Json::Value property = properties[iProperties];
						string name = property["name"].asString();
						if (name == "friction")
						{
							pTerrain->m_fFriction = property["value"].asFloat();
						}
					}
				}
				pTileSet->m_Terrains.push_back(pTerrain);
			}

			// Load Image and create sprite
			pTileSet->m_pSprite = m_pGM->getSprite(pTileSet->m_szName);
			pTileSet->m_pSprite->setTexture(m_pGM->getTexture(image));

			// origin of a tile at lower left in Tiled, upper left in SFML. Move Origin to center
			pTileSet->m_pSprite->setOrigin(-pTileSet->m_vTileOffset.getX(), pTileSet->m_nTileheight - pTileSet->m_vTileOffset.getY());

			//  Tiles
			if (pTileSet->m_nTilecount > 1)
			{
				Json::Value tiles = tileset["tiles"];
				if (version == 1.0f)
				{
					for (unsigned int i = 0; i < tiles.size(); ++i)
					{
						string tilenumber = tiles.getMemberNames()[i];
						Json::Value tile = tiles[tilenumber];
						Json::Value tileinfo = tile["terrain"];
						TileInfo* pTileInfo = new TileInfo;
						for (unsigned int iTerrain = 0; iTerrain < 4; iTerrain++)
						{
							pTileInfo->m_nTerrain[iTerrain] = tileinfo[iTerrain].asInt();
						}
						pTileSet->m_TileInfos[tilenumber] = pTileInfo;
					}
				}
				else if (version == 1.2f)
				{
					for (unsigned int i = 0; i < tiles.size(); ++i)
					{
						Json::Value tile = tiles[i];
						string tilenumber = tile["id"].asString();
						Json::Value tileinfo = tile["terrain"];
						TileInfo* pTileInfo = new TileInfo;
						for (unsigned int iTerrain = 0; iTerrain < 4; iTerrain++)
						{
							pTileInfo->m_nTerrain[iTerrain] = tileinfo[iTerrain].asInt();
						}
						pTileSet->m_TileInfos[tilenumber] = pTileInfo;
					}
				}
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
				string szLayerName = layer["name"].asString();
				bool bIsTerrain = (szLayerName == "Terrain");
				bool bIsCollisionTiles = (szLayerName == "CollisionTiles");
				bool bIsClearanceGround = (szLayerName == "ClearanceGround");

				if (version == 1.2f)
				{
					bool isEntity = false;
					Json::Value properties = layer["properties"];
					for (unsigned int iProperty = 0; iProperty < properties.size(); ++iProperty)
					{
						Json::Value property = properties[iProperty];
						string szEntityName = property["name"].asString();
						if (szEntityName == "UseHPA")
						{
							m_bUseHPA = property["value"].asBool();
						}
						else if (szEntityName == "UseAStar")
						{
							m_bUseAStar = property["value"].asBool();
						}
						else if (szEntityName == "UseAA")
						{
							m_bUseAA = property["value"].asBool();
						}
					}
				}

				// TD A*
				if (m_bUseAStar && bIsCollisionTiles)
				{
					MapSearchManager::getSingleton()->setCurrentMap(this);
				}

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
						else if (bIsCollisionTiles)
						{
							m_Grid[i][j]->setTileCollisionId(nIndex);
						}
						else if (bIsClearanceGround && m_pClearanceTileSet)
						{
							m_Grid[i][j]->setTileClearanceId(nIndex == 0 ? 0 : nIndex - m_pClearanceTileSet->m_nFirstgid + 1, 0);
						}
					}
				}
			}

			// TD Agents
			if (type == "objectgroup")
			{
				string szLayerName = layer["name"].asString();

				if (szLayerName == "Entities")
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

						Entity* pEntity = m_pGM->getEntity(szName);
						pEntity->setPosition(Vector2f((float)iPersoX, (float)iPersoY));

						m_pGM->addEntity(pEntity);

						// Properties
						if (version == 1.0f)
						{
							Json::Value entityName = object["properties"]["Entity"];
							if (entityName.isString())
							{
								pEntity->loadFromFileJSON(DATAAGENTPATH + entityName.asString());
							}
							else
							{
								SpriteRenderer* pSpriteRenderer = new crea::SpriteRenderer();
								pSpriteRenderer->setSprite(pTileSet->m_pSprite);
								IntRect iRect = pTileSet->getTextureRect(iGId);
								pSpriteRenderer->setTextureRect(&iRect);
								pEntity->addComponent(pSpriteRenderer);
							}
						}
						else if (version == 1.2f)
						{
							bool isEntity = false;
							Json::Value properties = object["properties"];
							for (unsigned int iProperty = 0; iProperty < properties.size(); ++iProperty)
							{
								Json::Value property = properties[iProperty];
								Json::Value propertyName = property["name"];
								string szPropertyName = propertyName.asString();
								if (szPropertyName == "Entity")
								{
									isEntity = true;
									Json::Value entityType = property["type"];
									if (propertyName.isString())
									{
										Json::Value entityValue = property["value"];
										string entityFileName = entityValue.asString();
										Entity* pModel = m_pGM->getEntityByModel(entityFileName);
										if (pModel)
										{
											pEntity->cloneComponents(pModel);
										}
										else
										{
											pEntity->loadFromFileJSON(DATAAGENTPATH + entityFileName);
											m_pGM->addEntityByModel(entityFileName, pEntity);
										}
									}
								}
							}
							// if it's not an entity, make it visible
							if (!isEntity)
							{
								SpriteRenderer* pSpriteRenderer = new crea::SpriteRenderer();
								pSpriteRenderer->setSprite(pTileSet->m_pSprite);
								IntRect iRect = pTileSet->getTextureRect(iGId);
								pSpriteRenderer->setTextureRect(&iRect);
								pEntity->addComponent(pSpriteRenderer);
							}
						}
					}
				}
				else if (szLayerName == "Collisions")
				{
					PhysicsManager::getSingleton()->setCurrentMap(this);

					Json::Value objects = layer["objects"];
					for (unsigned int iObject = 0; iObject < objects.size(); ++iObject)
					{
						Json::Value object = objects[iObject];
						int iColliderHeight = object["height"].asInt();
						int iColliderWidth = object["width"].asInt();
						int iColliderX = object["x"].asInt();
						int iColliderY = object["y"].asInt();
						int iRotation = object["rotation"].asInt();
						int iId = object["id"].asInt();
						string szName = object["name"].asString();
						string szType = object["type"].asString();
						bool bVisible = object["visible"].asBool();

						bool bEllipse = object["ellipse"].asBool();
						if (bEllipse)
						{
							// CircleCollider
							CircleCollider* pCircleCollider = new CircleCollider();
							float fRadius = iColliderWidth * 0.5f;
							pCircleCollider->getCenter() = Vector2f((float)iColliderX + fRadius, (float)iColliderY + fRadius);
							pCircleCollider->getRadius() = fRadius;
							if (szType.find("trigger") != string::npos)
							{
								pCircleCollider->getIsTrigger() = true;
							}
							PhysicsManager::getSingleton()->addStaticCollider(szName, pCircleCollider);
						}
						else
						{
							// BoxCollider
							BoxCollider* pBoxCollider = new BoxCollider();
							pBoxCollider->getOrigin() = Vector2f((float)iColliderX, (float)iColliderY);
							pBoxCollider->getSize() = Vector2f((float)iColliderWidth, (float)iColliderHeight);
							if (szType.find("trigger") != string::npos)
							{
								pBoxCollider->getIsTrigger() = true;
							}
							PhysicsManager::getSingleton()->addStaticCollider(szName, pBoxCollider);
						}

					}
				}
			}
		}

		// Terrain Tileset must be set (make sure the name of the tileset is "Terrain")
		if (m_pTerrainTileSet == nullptr)
		{
			cerr << "Terrain Tileset must be set! make sure the name of the tileset is \"Terrain\"" << endl;
			return false;
		}
		assert(m_pTerrainTileSet != nullptr);


		// Clusters
		if (m_bUseHPA)
		{
			findClusters();
		}

		if (m_bUseAA)
		{
			findClearance();
		}

		return true;
	}

	// 
	void Map::findClearance()
	{
		int capability = 0;
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				Node* pNode = getNode(i, j);
				int clearance = 0;
				if (pNode->getTileCollisionId() == 0)
				{
					clearance = 1;
					bool bClear = true;
					while (bClear)
					{
						// Expand down
						if (j + clearance == m_nHeight)
						{
							bClear = false;
						}
						else
						{
							for (short di = i; bClear && di <= i + clearance && di < m_nWidth; di++)
							{
								Node* pNode = getNode(di, j + clearance);
								if (pNode->getTileCollisionId() != 0)
								{
									bClear = false;
								}
							}
						}
						// Expand right
						if (!bClear || i + clearance == m_nWidth)
						{
							bClear = false;
						}
						else
						{
							for (short dj = j; bClear && dj <= j + clearance && dj < m_nHeight; dj++)
							{
								Node* pNode = getNode(i + clearance, dj);
								if (pNode->getTileCollisionId() != 0)
								{
									bClear = false;
								}
							}
							if (bClear)
							{
								clearance++;
							}
						}
					}
				}
				// Test pour vérifier concordance p/r au fichier
				short oldClearance = pNode->getTileClearanceId(capability);
				if (oldClearance != clearance)
				{
					cout << pNode->getX() << " " << pNode->getY() << " old clearance: " << oldClearance << "clearance: " << clearance << endl;
				}

				pNode->setTileClearanceId(clearance, capability);
			}
		}
	}

	void Map::findClusters()
	{
		// Create all clusters		
		setClusterSize(10, 10);

		// Find entrances in each clusters
		for (short i = 0; i < m_nNbClustersX; i++)
		{
			for (short j = 0; j < m_nNbClustersY; j++)
			{
				Cluster* pCluster = m_Clusters[i][j];
				pCluster->findEntrances();
			}
		}

		// Find transitions in each clusters
		for (short i = 0; i < m_nNbClustersX; i++)
		{
			for (short j = 0; j < m_nNbClustersY; j++)
			{
				Cluster* pCluster = m_Clusters[i][j];
				pCluster->findTransitions();
			}
		}

		// Find edges in each clusters
		for (short i = 0; i < m_nNbClustersX; i++)
		{
			for (short j = 0; j < m_nNbClustersY; j++)
			{
				Cluster* pCluster = m_Clusters[i][j];
				pCluster->findEdges();
			}
		}
	}

	void Map::setClusterSize(short _nClusterWidth, short _nClusterHeight)
	{
		m_nClusterWidth = _nClusterWidth;
		m_nClusterHeight = _nClusterHeight;

		// TD HPA		
		m_nNbClustersX = (m_nWidth / _nClusterWidth) + (m_nWidth % _nClusterWidth > 0.f ? 1 : 0);
		m_nNbClustersY = (m_nHeight / _nClusterHeight) + (m_nHeight % _nClusterHeight > 0.f ? 1 : 0);
		m_Clusters = new Cluster**[m_nNbClustersX];
		for (short i = 0; i < m_nNbClustersX; i++)
		{
			m_Clusters[i] = new Cluster*[m_nNbClustersY];
			for (short j = 0; j < m_nNbClustersY; j++)
			{
				Cluster* pCluster = new Cluster();
				pCluster->setPosition(i, j);
				short iSize = (i == m_nNbClustersX - 1) ? m_nWidth % m_nClusterWidth : m_nClusterWidth;
				short jSize = (j == m_nNbClustersY - 1) ? m_nHeight % m_nClusterHeight : m_nClusterHeight;
				pCluster->setSize(iSize, jSize);
				m_Clusters[i][j] = pCluster;
			}
		}

		// Set Neighbors
		for (short i = 0; i < m_nNbClustersX; i++)
		{
			for (short j = 0; j < m_nNbClustersY; j++)
			{
				if (j != 0)
				{
					m_Clusters[i][j]->addTopCluster(m_Clusters[i][j - 1]); // top node
				}
				if (i != m_nNbClustersX - 1)
				{
					m_Clusters[i][j]->addRightCluster(m_Clusters[i + 1][j]); // right node
				}
				if (j != m_nHeight - 1)
				{
					m_Clusters[i][j]->addBottomCluster(m_Clusters[i][j + 1]); // bottom node
				}
				if (i != 0)
				{
					m_Clusters[i][j]->addLeftCluster(m_Clusters[i - 1][j]); // left node
				}
			}
		}
	}

	void Map::getClusterSize(short& _nClusterWidth, short& _nClusterHeight)
	{
		_nClusterWidth = m_nClusterWidth;
		_nClusterHeight = m_nClusterHeight;
	}

	Node* Map::getNodeInCluster(Cluster* _pCluster, short _i, short _j)
	{
		short nX, nY;
		_pCluster->getPosition(nX, nY);
		return getNode(nX*m_nClusterWidth + _i, nY*m_nClusterHeight + _j);
	}

	Cluster* Map::getClusterFromNode(Node* _pNode)
	{
		return getCluster(_pNode->getX() / m_nClusterWidth, _pNode->getY() / m_nClusterHeight);
	}

	void Map::setSize(short _nWidth, short _nHeight)
	{
		clear();
		m_nWidth = _nWidth;
		m_nHeight = _nHeight;
		m_Grid = new Node**[m_nWidth];
		for (short i = 0; i < m_nWidth; i++)
		{
			m_Grid[i] = new Node*[m_nHeight];
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
		for (short i = 0; i < (short)m_TileSet.size(); i++)
		{
			pTileSet = m_TileSet[i];
			if (_gid >= pTileSet->m_nFirstgid && _gid < pTileSet->m_nFirstgid + pTileSet->m_nTilecount)
			{
				return pTileSet;
			}
		}
		return pTileSet;
	}

	Node* Map::getNodeAtPosition(Vector2f _v)
	{
		int i = (int)_v.getX() / m_nTileWidth;
		int j = (int)_v.getY() / m_nTileHeight;
		if (i >= 0 && i < m_nWidth && j >= 0 && j < m_nHeight)
			return m_Grid[i][j];
		else
			return nullptr;
	}

	Vector2f Map::getNodePositionFromPixels(Vector2f _v)
	{
		int i = (int)_v.getX() / m_nTileWidth;
		int j = (int)_v.getY() / m_nTileHeight;
		if (i >= 0 && i < m_nWidth && j >= 0 && j < m_nHeight)
			return Vector2f((float)i, (float)j);
		else
			return Vector2f(0.f, 0.f);
	}

	Vector2f Map::getPixelsFromNodePosition(Vector2f _v)
	{
		int i = (int)_v.getX() * m_nTileWidth;
		int j = (int)_v.getY() * m_nTileHeight;
		return Vector2f((float)i, (float)j);
	}

	void Map::updateTileIndexLimits()
	{
		// Camera/Window restriction
		IntRect r = m_pGM->getWindowRect();
		m_iMin = (int)r.getLeft() / m_nTileWidth;
		m_iMax = (int)(r.getLeft() + r.getWidth()) / m_nTileWidth;
		m_jMin = (int)r.getTop() / m_nTileHeight;
		m_jMax = (int)(r.getTop() + r.getHeight()) / m_nTileHeight;

		// Protection if map smaller than window
		m_iMax = MIN(m_iMax, m_nWidth - 1);
		m_jMax = MIN(m_jMax, m_nHeight - 1);
	}

	float Map::getFrictionAtPosition(Vector2f _v)
	{
		Node* pNode = getNodeAtPosition(_v);
		if (pNode)
		{
			unsigned short nTerrain = pNode->getTileTerrainId() - 1;
			unsigned short nQuad = getQuadAtPosition(_v);
			return m_pTerrainTileSet->getFriction(nTerrain, nQuad);
		}
		else
		{
			return 0.0f; // No friction outside map...
		}
	}

	unsigned short Map::getQuadAtPosition(Vector2f& _v)
	{
		float i = _v.getX() / m_nTileWidth;
		float j = _v.getY() / m_nTileHeight;
		float di = i - (int)i;
		float dj = j - (int)j;
		if (di < 0.5f && dj < 0.5f)
			return 0;
		else if (di >= 0.5f && dj < 0.5f)
			return 1;
		else if (di < 0.5f && dj >= 0.5f)
			return 2;
		else
			return 3;
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

		// Camera/Window restriction
		IntRect r = m_pGM->getWindowRect();
		int iMin = (int)r.getLeft() / m_nTileWidth;
		int iMax = (int)(r.getLeft() + r.getWidth()) / m_nTileWidth;
		int jMin = (int)r.getTop() / m_nTileHeight;
		int jMax = (int)(r.getTop() + r.getHeight()) / m_nTileHeight;

		// Protection if map smaller than window
		iMax = MIN(iMax, m_nWidth - 1);
		jMax = MIN(jMax, m_nHeight - 1);

		TileSet* pTileSet = m_pTerrainTileSet;
		for (short i = iMin; i <= iMax; i++)
		{
			Node** line = m_Grid[i];
			for (short j = jMin; j <= jMax; j++)
			{
				Node* pNode = line[j];
				tileid = pNode->getTileTerrainId(); // -1; // 30 -> 29

				IntRect iRect = pTileSet->getTextureRect(tileid);
				pTileSet->m_pSprite->setTextureRect(iRect.getLeft(), iRect.getTop(), iRect.getWidth(), iRect.getHeight());
				pTileSet->m_pSprite->setPosition((float)i*pTileSet->m_nTilewidth, (float)(j + 1)*pTileSet->m_nTileheight);
				pTileSet->m_pSprite->draw();
			}
		}

		return true;
	}

	void Map::clear()
	{
		// Grid
		for (short i = 0; i < m_nWidth; i++)
		{
			for (short j = 0; j < m_nHeight; j++)
			{
				delete m_Grid[i][j];
			}
			delete[] m_Grid[i];
		}
		delete[] m_Grid;

		// Tilesets
		TileSet* pTileSet = nullptr;
		for (short i = 0; i < (short)m_TileSet.size(); i++)
		{
			pTileSet = m_TileSet[i];
			delete pTileSet;
		}
		m_TileSet.clear();
		m_pTerrainTileSet = nullptr;
	}
} // namespace crea
