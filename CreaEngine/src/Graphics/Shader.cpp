#include "stdafx.h"
#include "Graphics\Shader.h"

namespace crea
{
	Shader::Shader()
	{
	}

	Shader::~Shader()
	{
	}

	bool Shader::loadFromFile(const string& _name)
	{
		return true;
	}

	void Shader::use()
	{
	}

	void Shader::unuse()
	{
	}

	// utility uniform functions
	// ------------------------------------------------------------------------
	void Shader::setBool(const std::string &name, bool value) const
	{
	}
	// ------------------------------------------------------------------------
	void Shader::setInt(const std::string &name, int value) const
	{
	}
	// ------------------------------------------------------------------------
	void Shader::setFloat(const std::string &name, float value) const
	{
	}
	// ------------------------------------------------------------------------
	void Shader::setVec3(const std::string &name, float* vec3) const
	{
	}
	// ------------------------------------------------------------------------
	void Shader::setMat3(const std::string &name, float* mat3) const
	{
	}
	// ------------------------------------------------------------------------
	void Shader::setMat4x4(const std::string &name, float* mat4) const
	{
	}
} // namespace Crea