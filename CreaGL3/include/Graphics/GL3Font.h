/***************************************************/
/* Nom:	GL3Font.h
/* Description: GL3Font
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Font_H
#define _GL3Font_H

#include "Graphics\Font.h"

namespace crea
{
	// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		unsigned int TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Horizontal offset to advance to next glyph
	};

	class GL3Font : public Font
	{
		std::map<char, Character> Characters;
		unsigned int VAO, VBO;
		Material* m_pMaterial;

	public:
		GL3Font() 
		{ 
			GameManager* pGM = GameManager::getSingleton();

			m_pMaterial = pGM->getMaterial("text.mat");
			IntRect r = pGM->getWindowRect();
			glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(r.getWidth()), -static_cast<GLfloat>(r.getHeight()), 0.0f);
			m_pMaterial->getShader()->use();
			m_pMaterial->getShader()->setMat4x4("projection", glm::value_ptr(projection));
		}
		
		virtual ~GL3Font() { }

		//void* getFont() { return m_pFont; }

		// Initialise le Font
		virtual bool loadFromFile(const string& _name)
		{
			// FreeType
			FT_Library ft;
			// All functions return a value different than 0 whenever an error occurred
			if (FT_Init_FreeType(&ft))
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

			// Load font as face
			FT_Face face;
			if (FT_New_Face(ft, _name.c_str(), 0, &face))
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

			// Set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, 48);

			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// Load first 128 characters of ASCII set
			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					(GLuint)face->glyph->advance.x
				};
				Characters.insert(std::pair<GLchar, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			// Destroy FreeType once we're finished
			FT_Done_Face(face);
			FT_Done_FreeType(ft);


			// Configure VAO/VBO for texture quads
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			return true;
		}

		void renderText(const std::string& text, float x, float y, float size, glm::vec3 color)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Activate corresponding render state	
			m_pMaterial->getShader()->use();
			m_pMaterial->getShader()->setVec3("textColor", glm::value_ptr(color));
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VAO);

			// todo: size in pixel so divide by? window height? (change this hardcode)
			float scalex = size / 52.8f; // todo: hardcoded, find out why 50 (to look like sfml...)
			float scaley = scalex * 1.3f;

			// Iterate through all characters
			std::string::const_iterator c;
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = Characters[*c];

				GLfloat xpos = x + ch.Bearing.x * scalex;
				GLfloat ypos = -size-2 + y - (ch.Size.y - ch.Bearing.y) * scaley;

				GLfloat w = ch.Size.x * scalex;
				GLfloat h = ch.Size.y * scaley;
				// Update VBO for each character
				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
				};
				// Render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				// Update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// Render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				x += (ch.Advance >> 6) * scalex; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			}
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);

			glDisable(GL_BLEND);
		}
	};

} // namespace crea

#endif // _GL3Font_H
