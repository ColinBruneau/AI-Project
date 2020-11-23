/**
* Header Material
*
* @author  cbruneau
* @since   09/10/2019
* @version 2.0
*/

#ifndef GL3Material_H
#define GL3Material_H

#include "Graphics\Material.h"

namespace crea
{
	class Shape;
	class Texture;
	class Entity;

	struct TextureInfo
	{
		string name;
		Texture* texture;
		unsigned int id;
	};
	struct ColorUniform
	{
		string uniform;
		Color color;
	};
	struct FloatUniform
	{
		string uniform;
		float value;
	}; 
	struct MaterialInfo
	{
		ColorUniform ambient;
		ColorUniform diffuse;
		ColorUniform specular;
		FloatUniform shininess;
	};
	struct AttenuationInfo
	{
		string constant;
		string linear;
		string quadratic;
	};
	struct CutOffInfo
	{
		string inner;
		string outer;
	};
	struct LightInfo
	{
		string type;
		string position;
		string direction;
		string ambient;
		string diffuse;
		string specular;
		AttenuationInfo attenuation;
		CutOffInfo cutOff;
	};
	struct LightsInfo
	{
		string nbDirLights;
		string nbPointLights;
		string nbSpotLights;
	};
	struct CameraInfo
	{
		string position;
		string view;
		string projection;
		string normalMatrix;
	};
	struct ModelInfo
	{
		string model;
		string normalMatrix;
	};
	class GL3Material : public Material
	{
	protected:
		string m_szName;
		bool m_bUseColor;
		map<unsigned int, TextureInfo> m_textures;
		string m_propertyTransform;
		// MVP
		string m_propertyModel;
		string m_propertyView;	
		string m_propertyProjection;
		// Material
		MaterialInfo m_materialInfo;
		bool m_bUseMaterialInfo = false;
		// Light
		map<unsigned int, LightInfo> m_lightInfos;
		LightsInfo m_lightsInfo;
		unsigned int m_nbDefaultLights = 0;
		unsigned int m_nbDirLights = 0;
		unsigned int m_nbPointLights = 0;
		unsigned int m_nbSpotLights = 0;
		bool m_bUseLightInfo = false;
		// Camera
		CameraInfo m_cameraInfo;
		bool m_bUseCameraInfo = false;
		// Model
		ModelInfo m_modelInfo;
		bool m_bUseModelInfo = false;
		// Time
		string m_time;
		bool m_bUseTime = false;

	public:

		GL3Material();
		virtual ~GL3Material();
		
		virtual void setTexture(unsigned int _index, const string& _propertyName, Texture* _pTexture)
		{ 
			TextureInfo t;
			t.texture = _pTexture;
			t.name = _propertyName;
			t.id = _index;
			// Add to map
			m_textures[_index] = t;
		}
		virtual Texture* getTexture(unsigned int _index) { return m_textures[_index].texture; }
		
		virtual void setLightInfo(unsigned int _index, LightInfo _lightInfo)
		{
			// Add to map
			m_lightInfos[_index] = _lightInfo;
		}

		virtual LightInfo getLightInfo(unsigned int _index) { return m_lightInfos[_index]; }

		virtual bool loadFromFile(const string& _name);
		virtual Asset* clone();
	
		// apply the Material to a Shape
		virtual bool applyShaderToShape(Shape* _pShape);

		// use the Material
		virtual void use(Entity* _pEntity = nullptr);

		// unuse the Material
		virtual void unuse();

	};

}
#endif //GL3Material_H
