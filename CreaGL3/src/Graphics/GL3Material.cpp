#include "stdafx.h"
#include "Graphics\GL3Material.h"

namespace crea
{
	GL3Material::GL3Material()
	{
		m_pShader = nullptr;
		m_pColor = nullptr;
		m_bUseColor = false;
	}

	GL3Material::~GL3Material()
	{
		if (m_pShader)
		{
			m_pShader->use();
			if (!m_textures.empty())
			{
				for (unsigned int i = 0; i < m_textures.size(); ++i)
				{
					m_textures[i].texture->unbind(i);
				}
			}
			m_pShader->unuse();
		}
	}


	bool GL3Material::loadFromFile(const string& _name)
	{
		Json::Value root;
		std::ifstream matFile(_name, std::ifstream::binary);
		if (matFile.fail())
		{
			cerr << _name << " could not be found." << endl;
			return false;
		}
		m_szName = _name;
		matFile >> root;
		matFile.close();

		GameManager* pGM = GameManager::getSingleton();

		// Shader
		string szShader = root["shader"].asString();
		if (!szShader.empty())
		{
			m_pShader = pGM->getShader(szShader);
		}

		// Color
		Json::Value matColor = root["color"];
		if (!matColor.isNull())
		{
			m_bUseColor = true;
			m_pColor = new GL3Color(matColor["r"].asInt(), matColor["g"].asInt(), matColor["b"].asInt(), matColor["a"].asInt());
		}
		else
		{
			m_bUseColor = false;
		}

		// Textures
		Json::Value matTextures = root["textures"];
		if (!matTextures.isNull())
		{
			for (unsigned int i = 0; i < matTextures.size(); ++i)
			{
				Json::Value matTexture = matTextures[i];
				Texture* texture = pGM->getTexture(matTexture["texture"].asString());
				if (texture)
				{
					setTexture(matTexture["index"].asInt(), matTexture["propertyName"].asString(), texture);
					Json::Value matTextureTransparency = matTexture["transparency"];
					if (!matTextureTransparency.isNull())
					{
						texture->setTransparency(matTextureTransparency.asBool());
					}
				}
				else
				{
					cerr << "No texture " << matTexture["texture"].asString() << " to set for material " << _name << endl;
				}
			}
		}
		
		// Transform
		string szTransform = root["transform"].asString();
		if (!szTransform.empty())
		{
			m_propertyTransform = szTransform;
		}

		// Model View Projection
		string szModel = root["model"].asString();
		if (!szModel.empty())
		{
			m_propertyModel = szModel;
		}
		string szView = root["view"].asString();
		if (!szView.empty())
		{
			m_propertyView = szView;
		}
		string szProjection = root["projection"].asString();
		if (!szProjection.empty())
		{
			m_propertyProjection = szProjection;
		}

		// MaterialInfo
		Json::Value valueMaterialInfo = root["materialInfo"];
		if (!valueMaterialInfo.isNull())
		{
			Json::Value ambientMaterial = valueMaterialInfo["ambient"];
			if (!ambientMaterial.isNull())
			{
				m_materialInfo.ambient.uniform = ambientMaterial["uniform"].asString();
				m_materialInfo.ambient.color = Color(ambientMaterial["r"].asInt(), ambientMaterial["g"].asInt(), ambientMaterial["b"].asInt(), 255);
			}
			Json::Value diffuseMaterial = valueMaterialInfo["diffuse"];
			if (!diffuseMaterial.isNull())
			{
				m_materialInfo.diffuse.uniform = diffuseMaterial["uniform"].asString();
				m_materialInfo.diffuse.color = Color(diffuseMaterial["r"].asInt(), diffuseMaterial["g"].asInt(), diffuseMaterial["b"].asInt(), 255);
			}
			Json::Value specularMaterial = valueMaterialInfo["specular"];
			if (!specularMaterial.isNull())
			{
				m_materialInfo.specular.uniform = specularMaterial["uniform"].asString();
				m_materialInfo.specular.color = Color(specularMaterial["r"].asInt(), specularMaterial["g"].asInt(), specularMaterial["b"].asInt(), 255);
			}
			Json::Value shininessMaterial = valueMaterialInfo["shininess"];
			if (!shininessMaterial.isNull())
			{
				m_materialInfo.shininess.uniform = shininessMaterial["uniform"].asString();
				m_materialInfo.shininess.value = shininessMaterial["value"].asFloat();
			}
			m_bUseMaterialInfo = true;
		}
		
		// LightsInfo
		Json::Value valueLightsInfo = root["lightsInfo"];
		if (!valueLightsInfo.isNull())
		{
			string szNbDirLights = valueLightsInfo["nbDirLights"].asString();
			if (!szNbDirLights.empty())
			{
				m_lightsInfo.nbDirLights = szNbDirLights;
			}
			string szNbPointLights = valueLightsInfo["nbPointLights"].asString();
			if (!szNbPointLights.empty())
			{
				m_lightsInfo.nbPointLights = szNbPointLights;
			}
			string szNbSpotLights = valueLightsInfo["nbSpotLights"].asString();
			if (!szNbSpotLights.empty())
			{
				m_lightsInfo.nbSpotLights = szNbSpotLights;
			}

			m_nbDefaultLights = 0;
			m_nbDirLights = 0;
			m_nbPointLights = 0;
			m_nbSpotLights = 0;

			Json::Value lights = valueLightsInfo["lights"];
			for (unsigned int i = 0; i < lights.size(); ++i)
			{
				Json::Value valueLightInfo = lights[i];
				LightInfo lightInfo;

				lightInfo.type = valueLightInfo["type"].asString();

				lightInfo.ambient = valueLightInfo["ambient"].asString();
				lightInfo.diffuse = valueLightInfo["diffuse"].asString();
				lightInfo.specular = valueLightInfo["specular"].asString();

				// None
				if (lightInfo.type == "DEFAULTLIGHT")
				{
					m_nbDefaultLights++;
					lightInfo.position = valueLightInfo["position"].asString();
				}

				// DirLight
				if (lightInfo.type == "DIRLIGHT")
				{
					m_nbDirLights++;
					lightInfo.direction = valueLightInfo["direction"].asString();
				}

				// Pointlight
				if (lightInfo.type == "POINTLIGHT")
				{
					m_nbPointLights++;
					lightInfo.position = valueLightInfo["position"].asString();
					string szConstant = valueLightInfo["constant"].asString();
					if (!szConstant.empty())
					{
						lightInfo.attenuation.constant = szConstant;
					}
					string szLinear = valueLightInfo["linear"].asString();
					if (!szLinear.empty())
					{
						lightInfo.attenuation.linear = szLinear;
					}
					string szQuadratic = valueLightInfo["quadratic"].asString();
					if (!szQuadratic.empty())
					{
						lightInfo.attenuation.quadratic = szQuadratic;
					}
				}

				// Spotlight
				if (lightInfo.type == "SPOTLIGHT")
				{
					m_nbSpotLights++;
					lightInfo.position = valueLightInfo["position"].asString();
					lightInfo.direction = valueLightInfo["direction"].asString();
					string szConstant = valueLightInfo["constant"].asString();
					if (!szConstant.empty())
					{
						lightInfo.attenuation.constant = szConstant;
					}
					string szLinear = valueLightInfo["linear"].asString();
					if (!szLinear.empty())
					{
						lightInfo.attenuation.linear = szLinear;
					}
					string szQuadratic = valueLightInfo["quadratic"].asString();
					if (!szQuadratic.empty())
					{
						lightInfo.attenuation.quadratic = szQuadratic;
					}
					lightInfo.cutOff.inner = valueLightInfo["inner"].asString();
					lightInfo.cutOff.outer = valueLightInfo["outer"].asString();
				}

				setLightInfo(i, lightInfo);
				m_bUseLightInfo = true;
			}
		}

		// CameraInfo
		Json::Value valueCameraInfo = root["cameraInfo"];
		if (!valueCameraInfo.isNull())
		{
			m_cameraInfo.position = valueCameraInfo["position"].asString();
			m_cameraInfo.view = valueCameraInfo["view"].asString();
			m_cameraInfo.projection = valueCameraInfo["projection"].asString();
			m_bUseCameraInfo = true;
		}

		// ModelInfo
		Json::Value valueModelInfo = root["modelInfo"];
		if (!valueModelInfo.isNull())
		{
			m_modelInfo.model = valueModelInfo["model"].asString();
			m_modelInfo.normalMatrix = valueModelInfo["normalMatrix"].asString();
			m_bUseModelInfo = true;
		}

		// Time
		string szTime = root["time"].asString();
		if (!szTime.empty())
		{
			m_time = szTime;
			m_bUseTime = true;
		}

		return true;
	}

	Asset* GL3Material::clone()
	{ 
		GL3Material* pMaterial = new GL3Material();
		*pMaterial = *this;
		return pMaterial;
	}

	bool GL3Material::applyShaderToShape(Shape* _pShape)
	{
		if (_pShape)
		{
			// Color
			if (m_bUseColor)
			{
				_pShape->setColor(m_pColor);
			}

			// Texture
			if (m_pShader && !m_textures.empty())
			{
				m_pShader->use();
				for (unsigned int i = 0; i < m_textures.size(); ++i)
				{
					m_pShader->setInt(m_textures[i].name.c_str(), i);
				}
			}
		}

		return true;
	}

	void GL3Material::use(Entity* _pEntity)
	{
		if (m_pShader)
		{
			if (!m_textures.empty())
			{
				for (unsigned int i = 0; i < m_textures.size(); ++i)
				{
					m_textures[i].texture->bind(i);
				}
			}

			m_pShader->use();
			// todo: integrate functions from 2019-2020 GL3 little by little
			// pour le moment une entité a un transform et pas de glm::mat4 donc il faut la classe Matrix44
			// Intégrer la lib de math?
			
			if (_pEntity) 
			{
				if (!m_propertyTransform.empty())
				{
					//glm::mat4 transform = _pEntity->getTransform()->getLocalToWorldMatrix();
					//m_pShader->setMat4x4(m_propertyTransform, transform);
				}
				if (!m_propertyModel.empty())
				{
					//glm::mat4 model = _pEntity->getTransform()->getLocalToWorldMatrix();
					//m_pShader->setMat4x4(m_propertyModel, model);
				}
				if (!m_propertyView.empty())
				{
					//glm::mat4 view = GameManager::getSingleton()->getMainCamera()->getViewMatrix();
					//m_pShader->setMat4x4(m_propertyView, view);
				}
				if (!m_propertyProjection.empty())
				{
					//glm::mat4 projection = GameManager::getSingleton()->getMainCamera()->getProjectionMatrix();
					//m_pShader->setMat4x4(m_propertyProjection, projection);
				}
				if (m_bUseMaterialInfo)
				{
					if (!m_materialInfo.ambient.uniform.empty())
					{
						//Color ambient = m_materialInfo.ambient.color;
						//m_pShader->setVec3(m_materialInfo.ambient.uniform, glm::vec3(ambient.getR(), ambient.getG(), ambient.getB()));
					}
					if (!m_materialInfo.diffuse.uniform.empty())
					{
						//Color diffuse = m_materialInfo.diffuse.color;
						//m_pShader->setVec3(m_materialInfo.diffuse.uniform, glm::vec3(diffuse.getR(), diffuse.getG(), diffuse.getB()));
					}
					if (!m_materialInfo.specular.uniform.empty())
					{
						//Color specular = m_materialInfo.specular.color;
						//m_pShader->setVec3(m_materialInfo.specular.uniform, glm::vec3(specular.getR(), specular.getG(), specular.getB()));
					}
					if (!m_materialInfo.shininess.uniform.empty())
					{
						//m_pShader->setFloat(m_materialInfo.shininess.uniform, m_materialInfo.shininess.value);
					}
				}
				if (m_bUseLightInfo)
				{/*
					m_pShader->setInt(m_lightsInfo.nbDirLights, m_nbDirLights);
					m_pShader->setInt(m_lightsInfo.nbPointLights, m_nbPointLights);
					m_pShader->setInt(m_lightsInfo.nbSpotLights, m_nbSpotLights);
					for (unsigned int i = 0; i < m_lightInfos.size(); ++i)
					{
						Light* pLight = GameManager::getSingleton()->getLight(i);
						assert(pLight);
						LightInfo lightInfo = getLightInfo(i);
						// All type
						Color ambient = pLight->getAmbient();
						m_pShader->setVec3(lightInfo.ambient, glm::vec3(ambient.getR(), ambient.getG(), ambient.getB()));
						Color diffuse = pLight->getDiffuse();
						m_pShader->setVec3(lightInfo.diffuse, glm::vec3(diffuse.getR(), diffuse.getG(), diffuse.getB()));
						Color specular = pLight->getSpecular();
						m_pShader->setVec3(lightInfo.specular, glm::vec3(specular.getR(), specular.getG(), specular.getB()));
						// DefaultLight
						if (pLight->getLightType() == DEFAULTLIGHT && lightInfo.type == "DEFAULTLIGHT")
						{
							m_pShader->setVec3(lightInfo.position, pLight->getEntity()->getTransform()->getPosition());
						}
						// DirLight
						if (pLight->getLightType() == DIRLIGHT && lightInfo.type == "DIRLIGHT")
						{
							glm::vec3 dir = pLight->getEntity()->getTransform()->getForward();
							m_pShader->setVec3(lightInfo.direction, dir);
						}
						// PointLight
						if (pLight->getLightType() == POINTLIGHT && lightInfo.type == "POINTLIGHT")
						{
							m_pShader->setVec3(lightInfo.position, pLight->getEntity()->getTransform()->getPosition());
							Attenuation attenuation = pLight->getAttenuation();
							m_pShader->setFloat(lightInfo.attenuation.constant, attenuation.constant);
							m_pShader->setFloat(lightInfo.attenuation.linear, attenuation.linear);
							m_pShader->setFloat(lightInfo.attenuation.quadratic, attenuation.quadratic);
						}
						// SpotLight
						if (pLight->getLightType() == SPOTLIGHT && lightInfo.type == "SPOTLIGHT")
						{
							m_pShader->setVec3(lightInfo.position, pLight->getEntity()->getTransform()->getPosition());
							glm::vec3 dir = pLight->getEntity()->getTransform()->getForward();
							m_pShader->setVec3(lightInfo.direction, dir);
							Attenuation attenuation = pLight->getAttenuation();
							m_pShader->setFloat(lightInfo.attenuation.constant, attenuation.constant);
							m_pShader->setFloat(lightInfo.attenuation.linear, attenuation.linear);
							m_pShader->setFloat(lightInfo.attenuation.quadratic, attenuation.quadratic);
							CutOff cutOff = pLight->getCutOff();
							m_pShader->setFloat(lightInfo.cutOff.inner, cutOff.inner);
							m_pShader->setFloat(lightInfo.cutOff.outer, cutOff.outer);
						}
					}*/
				}
				if (m_bUseCameraInfo)
				{/*
					Camera* pCamera = GameManager::getSingleton()->getMainCamera();
					m_pShader->setVec3(m_cameraInfo.position, pCamera->getEntity()->getTransform()->getPosition());
					glm::mat4 view = GameManager::getSingleton()->getMainCamera()->getViewMatrix();
					m_pShader->setMat4x4(m_cameraInfo.view, view);
					glm::mat4 projection = GameManager::getSingleton()->getMainCamera()->getProjectionMatrix();
					m_pShader->setMat4x4(m_cameraInfo.projection, projection);*/
				}
				if (m_bUseModelInfo)
				{/*
					glm::mat4 model = _pEntity->getTransform()->getLocalToWorldMatrix();
					m_pShader->setMat4x4(m_modelInfo.model, model);
					// Normal Matrix
					glm::mat3 model3x3(model);
					glm::mat3 normalMatrix = glm::transpose(glm::inverse(model3x3));
					m_pShader->setMat3(m_modelInfo.normalMatrix, normalMatrix);*/
				}
				if (m_bUseTime)
				{
					//m_pShader->setFloat(m_time, (float) glfwGetTime());
				}
			}
		}
	}

	void GL3Material::unuse()
	{
		if (m_pShader)
		{
			m_pShader->unuse();
		}
	}

} // namespace Crea