/**
* Header Shader
*
* @author  cbruneau
* @since   15/01/2018
* @version 2.0
*/

#ifndef SHADER_H
#define SHADER_H

namespace crea
{

	class CREAENGINE_API Shader
	{

	public:
		// the program ID
		unsigned int shaderProgram;

		// constructor reads and builds the shader
		Shader();
		virtual ~Shader();

		virtual bool loadFromFile(const string& _name);
	
		// use the shader
		virtual void use();

		// unuse the shader
		virtual void unuse();

		// utility uniform functions
		// ------------------------------------------------------------------------
		virtual void setBool(const std::string &name, bool value) const;
		// ------------------------------------------------------------------------
		virtual void setInt(const std::string &name, int value) const;
		// ------------------------------------------------------------------------
		void setFloat(const std::string &name, float value) const;
		// ------------------------------------------------------------------------
		virtual void setVec3(const std::string &name, float* vec3) const;
		// ------------------------------------------------------------------------
		virtual void setMat3(const std::string &name, float* mat3) const;
		// ------------------------------------------------------------------------
		virtual void setMat4x4(const std::string &name, float* mat4) const;
	};

}
#endif
