/**
* Header GL3Shader
*
* @author  cbruneau
* @since   15/01/2018
* @version 2.0
*/

#ifndef GL3Shader_H
#define GL3Shader_H

#include "Graphics\Shader.h"

namespace crea
{

	class GL3Shader : public Shader
	{

	public:
		// the program ID
		unsigned int shaderProgram;

		// constructor reads and builds the GL3Shader
		GL3Shader();
		~GL3Shader();

		virtual bool loadFromFile(const string& _name);
	
		// use the GL3Shader
		virtual void use();

		// unuse the GL3Shader
		virtual void unuse();

		// utility uniform functions
		// ------------------------------------------------------------------------
		virtual void setBool(const std::string &name, bool value) const;
		// ------------------------------------------------------------------------
		virtual void setInt(const std::string &name, int value) const;
		// ------------------------------------------------------------------------
		virtual void setFloat(const std::string &name, float value) const;
		// ------------------------------------------------------------------------
		virtual void setVec3(const std::string &name, float* vec3) const;
		// ------------------------------------------------------------------------
		virtual void setMat3(const std::string &name, float* mat3) const;
		// ------------------------------------------------------------------------
		virtual void setMat4x4(const std::string &name, float* mat4) const;
	};

}
#endif
