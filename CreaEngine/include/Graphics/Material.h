/**
* Header Material
*
* @author  cbruneau
* @since   09/10/2019
* @version 2.0
*/

#ifndef Material_H
#define Material_H

namespace crea
{

	class CREAENGINE_API Material : public Asset
	{
	protected:
		Shader* m_pShader;
		Color* m_pColor;

	public:

		Material() {}
		virtual ~Material() {};

		inline void setShader(Shader* _pShader) { m_pShader = _pShader; }
		inline Shader* getShader() { return m_pShader; }

		inline void setColor(Color* _pColor) { m_pColor = _pColor; }
		inline Color* getColor() { return m_pColor; }

		virtual void setTexture(unsigned int _index, const string& _propertyName, Texture* _pTexture) {};
		virtual Texture* getTexture(unsigned int _index) { return nullptr; }
		
		virtual bool loadFromFile(const string& _name) { return false; }
		virtual Asset* clone() { return new Material(*this); }

		// apply the Material to a Shape
		virtual bool applyShaderToShape(Shape* _pShape) { return false; }

		// use the Material
		virtual void use(Entity* _pEntity = nullptr) {}

		// unuse the Material
		virtual void unuse() {}
	};

}
#endif
