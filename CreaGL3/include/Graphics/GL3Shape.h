/***************************************************/
/* Nom:	GL3Shape.h
/* Description: GL3Shape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Shape_H
#define _GL3Shape_H

#include "Graphics\Shape.h"

namespace crea
{
	struct VertexPosition
	{
		float x;
		float y;
		float z;
	};
	struct VertexColor
	{
		float r;
		float g;
		float b;
	};
	struct VertexUV
	{
		float u;
		float v;
	};
	struct VertexNormal
	{
		float x;
		float y;
		float z;
	};

	class GL3Shape : public Shape
	{
	protected:
		GL3Color m_color;
		unsigned int VAO, VBO, VCO, VDO, VNO, EBO;
		unsigned int m_nbVertices;
		unsigned int m_nbIndices;
		VertexPosition* m_pVerticesPositions;
		unsigned int* m_pIndices;
		VertexColor* m_pVerticesColors;
		VertexUV* m_pVerticesUV;
		VertexNormal* m_pVerticesNormal;
		bool m_bFlipHorizontal = false;
		bool m_bFlipVertical = false;

		bool m_updated = true;

		void send()
		{

			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(VAO);

			// Position buffer
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, m_nbVertices * sizeof(VertexPosition), m_pVerticesPositions, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nbIndices * sizeof(unsigned int), m_pIndices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// VertexColor buffer
			if (m_pVerticesColors)
			{
				glBindBuffer(GL_ARRAY_BUFFER, VCO);
				glBufferData(GL_ARRAY_BUFFER, m_nbVertices * sizeof(VertexColor), m_pVerticesColors, GL_STATIC_DRAW);

				// color attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(1);
			}

			// uv buffer
			if (m_pVerticesUV)
			{
				glBindBuffer(GL_ARRAY_BUFFER, VDO);
				glBufferData(GL_ARRAY_BUFFER, m_nbVertices * sizeof(VertexUV), m_pVerticesUV, GL_STATIC_DRAW);

				// texture coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(2);
			}

			// normals buffer
			if (m_pVerticesNormal)
			{
				glBindBuffer(GL_ARRAY_BUFFER, VNO);
				glBufferData(GL_ARRAY_BUFFER, m_nbVertices * sizeof(VertexNormal), m_pVerticesNormal, GL_STATIC_DRAW);

				// normal attribute
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(3);
			}

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

		}
	public:

		GL3Shape()
		{
			m_updated = true;
			m_nbVertices = 0;
			m_nbIndices = 0;
			m_pVerticesPositions = nullptr;
			m_pIndices = nullptr;
			m_pVerticesColors = nullptr;
			m_pVerticesNormal = nullptr;

			m_color.setValues(0, 0, 255, 255);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &VCO);
			glGenBuffers(1, &VDO);
			glGenBuffers(1, &VNO);
			glGenBuffers(1, &EBO);
		}

		virtual ~GL3Shape()
		{
			if (m_pVerticesColors)
			{
				delete m_pVerticesColors;
			}

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &VCO);
			glDeleteBuffers(1, &VDO);
			glDeleteBuffers(1, &VNO);
			glDeleteBuffers(1, &EBO);
		}

		void setVerticesPositions(VertexPosition _verticesPositions[], unsigned int _size)
		{
			assert(_size <= m_nbVertices);
			for (unsigned int i = 0; i < _size; i++)
			{
				m_pVerticesPositions[i] = _verticesPositions[i];
			}
			m_updated = true;
		}

		void setVerticesIndices(unsigned int _indices[], unsigned int _size)
		{
			assert(_size <= m_nbIndices);
			for (unsigned int i = 0; i < _size; i++)
			{
				m_pIndices[i] = _indices[i];
			}
			m_updated = true;
		}

		virtual void setColor(Color* _color)
		{
			GL3Color* pColor = (GL3Color*)_color;
			m_color = *pColor;

			if (m_nbVertices == 0)
				return;

			if (!m_pVerticesColors)
			{
				m_pVerticesColors = new VertexColor[m_nbVertices];
			}
			float r = m_color.getR();
			float g = m_color.getG();
			float b = m_color.getB();
			for (unsigned int i = 0; i < m_nbVertices; i++)
			{
				m_pVerticesColors[i].r = r;
				m_pVerticesColors[i].g = g;
				m_pVerticesColors[i].b = b;
			}
			m_updated = true;
		}

		void setVerticesColors(Color _colors[], unsigned int _size)
		{
			GL3Color* pColor = (GL3Color*) &(_colors[0]);
			m_color = *pColor;

			if (m_nbVertices == 0)
				return;

			if (!m_pVerticesColors)
			{
				m_pVerticesColors = new VertexColor[m_nbVertices];
			}

			for (unsigned int i = 0; i < m_nbVertices; i++)
			{
				pColor = (GL3Color*) &(_colors[i]);
				m_pVerticesColors[i].r = pColor->getR();
				m_pVerticesColors[i].g = pColor->getG();
				m_pVerticesColors[i].b = pColor->getB();
			}
			m_updated = true;
		}

		void setVerticesUV(VertexUV _uvs[], unsigned int _size)
		{
			if (m_nbVertices == 0)
				return;

			if (!m_pVerticesUV)
			{
				m_pVerticesUV = new VertexUV[m_nbVertices];
			}

			
			VertexUV uv;
			for (unsigned int i = 0; i < m_nbVertices; i++)
			{
				uv = _uvs[i];
				m_pVerticesUV[i].u = uv.u;
				m_pVerticesUV[i].v = uv.v;
			}
			m_updated = true;
		}

		void setVerticesNormals(VertexNormal _normals[], unsigned int _size)
		{
			if (m_nbVertices == 0)
				return;

			if (!m_pVerticesNormal)
			{
				m_pVerticesNormal = new VertexNormal[m_nbVertices];
			}

			VertexNormal n;
			for (unsigned int i = 0; i < m_nbVertices; i++)
			{
				n = _normals[i];
				m_pVerticesNormal[i].x = n.x;
				m_pVerticesNormal[i].y = n.y;
				m_pVerticesNormal[i].z = n.z;
			}
			m_updated = true;
		}

		virtual void draw()
		{
			if (m_updated)
			{
				send();
				m_updated = false;
			}
		}

		virtual void setOutlineColor(Color* _pColor)
		{
		}

		virtual void setOutlineThickness(float _fPixels)
		{
		}

		virtual void setPosition(float _x, float _y)
		{
		}

		virtual void setRotation(float _angle)
		{
		}

		virtual void setScale(float _x, float _y)
		{
		}

		virtual void setOrigin(float _x, float _y)
		{
		}
	};

	class GL3RectangleShape : public GL3Shape
	{
	protected:
		VertexPosition m_vertices[4];
		unsigned int m_indices[4];

		glm::vec2 position = glm::vec2(0.f, 0.f);
		glm::vec2 origin = glm::vec2(0.f, 0.f);
		glm::vec2 size = glm::vec2(1.f, 1.f);
		glm::vec2 scale = glm::vec2(1.f, 1.f);

		glm::vec2 textureSize = glm::vec2(64.f, 64.f);
		glm::vec2 displaySize = glm::vec2(128.f, 128.f);
		glm::vec2 windowSize = glm::vec2(1280.f, 800.f);

	public:

		GL3RectangleShape()
		{		
			//    1 ___ 3
			//     |\  |  
			//     | \ | 
			//    0|__\|2
			m_nbVertices = 4;
			m_pVerticesPositions = &m_vertices[0];
			setSize(1.f, 1.f);

			m_nbIndices = 4;
			m_pIndices = &m_indices[0];
			unsigned int i[] = { 0, 2, 1, 3 };
			setVerticesIndices(i, 4);

			// Color
			Color b(Color::blue);
			setColor(&b);

			// UV
			VertexUV uv[] = {
				{ 0.0f, 0.0f },// bottom left
				{ 0.0f, 1.0f },// top left 
				{ 1.0f, 0.0f },// bottom right
				{ 1.0f,  1.0f }// top right 
			};
			setVerticesUV(uv, 4);

		}

		virtual ~GL3RectangleShape()
		{
		}

		virtual void draw()
		{
			GL3Shape::draw();

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLE_STRIP, m_nbIndices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		void updateVertices()
		{
			float posX = 2 * (position.x - origin.x) / windowSize.x - 1.f;
			float offsetX = 2 * size.x * displaySize.x / windowSize.x;
			float posY = -2 * (position.y - origin.y) / windowSize.y + 1.f;
			float offsetY = - 2 * size.y * displaySize.y / windowSize.y;
			if (!m_bFlipHorizontal)
			{
				VertexPosition v[] = {
					{ posX, posY + offsetY }, // bottom left
					{ posX, posY },	// top left 
					{ posX + offsetX, posY + offsetY },	// bottom right
					{ posX + offsetX, posY },	// top right
				};
				setVerticesPositions(v, 4);
			}
			else
			{
				VertexPosition v[] = {
					{ posX + offsetX, posY + offsetY },	// bottom left
					{ posX + offsetX, posY },	// top left 
					{ posX, posY + offsetY }, // bottom right
					{ posX, posY },	// top right 
				};
				setVerticesPositions(v, 4);
			}
		}

		virtual void setSize(float _x, float _y)
		{
			size = glm::vec2(_x, _y);
			updateVertices();
		}

		virtual void setPosition(float _x, float _y)
		{
			position = glm::vec3(_x, _y, 0.f);
			updateVertices();
		}

		virtual void setScale(float _x, float _y)
		{
			if (scale != glm::vec2(_x, _y))
			{
				if (m_bFlipHorizontal && _x > 0.f
					|| !m_bFlipHorizontal && _x < 0.f) // Flip horizontal
				{
					
					m_bFlipHorizontal = !m_bFlipHorizontal;
				}

				scale = glm::vec2(_x, _y);
				updateVertices();
			}
		}

		virtual void setOrigin(float _x, float _y)
		{
			origin = glm::vec2(_x, _y);
			updateVertices();
		}

		void setTextureSize(int _x, int _y)
		{
			textureSize = glm::vec2(_x, _y);
		}

		void setDisplaySize(int _x, int _y)
		{
			displaySize = glm::vec2(_x, _y);
		}


		void setWindowSize(int _x, int _y)
		{
			windowSize = glm::vec2(_x, _y); 
		}	

		GL3RectangleShape& operator= (const GL3RectangleShape& _rs)
		{
			setColor((Color*)&_rs.m_color);

			position = _rs.position;
			origin = _rs.origin;
			size = _rs.size;
			scale = _rs.scale;

			textureSize = _rs.textureSize;
			displaySize = _rs.displaySize;
			windowSize = _rs.windowSize;

			updateVertices();

			return *this;
		}


};

	class GL3CircleShape : public GL3Shape
	{
		// todo: GL3CircleShape
	public:

		GL3CircleShape()
		{
		}

		~GL3CircleShape()
		{
		}

		virtual void setRadius(float _r)
		{
		}

		void setNbPoints(int _iNbPoints)
		{
		}

		void setSize(float _fSize, int _iNbSides = 20)
		{
		}

		void draw()
		{
		}

	};

	class GL3ArrowShape : public GL3Shape
	{
		// todo: GL3ArrowShape
	public:

		GL3ArrowShape()
		{
		}

		~GL3ArrowShape()
		{
		}

		virtual void draw()
		{
		}

		virtual void setSize(float _x, float _y)
		{
		}

		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd)
		{

		}

	};

	class GL3LineShape : public GL3Shape
	{
		// todo: GL3LineShape
	public:

		GL3LineShape()
		{
		}

		~GL3LineShape()
		{
		}

		virtual void draw()
		{

		}

		virtual void setSize(float _x, float _y)
		{
		}

		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd)
		{
		}

	};
} // namespace crea

#endif // _GL3Shape_H