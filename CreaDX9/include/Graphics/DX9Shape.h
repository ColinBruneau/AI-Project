/***************************************************/
/* Nom:	DX9Shape.h
/* Description: DX9Shape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Shape_H
#define _DX9Shape_H

#include "Graphics\Shape.h"

namespace crea
{
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
	// A structure for our custom vertex type
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw; // The transformed position for the vertex
		DWORD color;        // The vertex color
	};
#define D3DCOLOR_ISVISIBLE(color) ((color>>24)&0xff)

	class DX9Shape : public Shape
	{
	protected:
		D3DXVECTOR2 * m_pOrigin;
		float m_fRotation;
		D3DXVECTOR2 *m_pScale;
		D3DXVECTOR2 m_position;
		D3DCOLOR m_color;
		D3DCOLOR m_outlineColor;
		float m_outlinePixels; 
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		bool m_bUpdateVertices;
		bool m_bUseColor;
		bool m_bUseOutline;

	public:

		DX9Shape() 
		{  
			m_pOrigin = nullptr;
			m_fRotation = 0.f;
			m_pScale = nullptr;
			m_position = D3DXVECTOR2(0.0f, 0.0f);
			m_color = D3DCOLOR_XRGB(255, 255, 255);
			m_outlineColor = D3DCOLOR_XRGB(255, 255, 255);
			m_outlinePixels = 1;
			m_pD3DDevice = nullptr;
			m_pD3DDevice = DX9Facade::Instance().m_pDevice;
			m_bUpdateVertices = true;
			m_bUseColor = false;
			m_bUseOutline = false;
		}

		virtual ~DX9Shape() 
		{ 
			if (m_pOrigin)
				delete m_pOrigin;
			if (m_pScale)
				delete m_pScale;
		}

		void setOrigin(float _x, float _y)
		{
			if (!m_pOrigin)
			{
				m_pOrigin = new D3DXVECTOR2;
			}
			*m_pOrigin = D3DXVECTOR2(_x, _y);
		}

		void setRotation(float _angle)
		{
			m_fRotation = _angle;
		}

		void setScale(float _x, float _y)
		{
			if (!m_pScale)
			{
				m_pScale = new D3DXVECTOR2;
			}
			*m_pScale = D3DXVECTOR2(_x, _y);
		}

		virtual void draw() { }
		
		virtual void setColor(Color* _pColor) 
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_color = pColor->getColor();
			m_bUpdateVertices = true;
			m_bUseColor = true;
		}

		virtual void setOutlineColor(Color* _pColor)
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_outlineColor = pColor->getColor();
			
			m_bUpdateVertices = true;
			m_bUseOutline = true;
		}

		virtual void setOutlineThickness(float _fPixels) 
		{
			// todo: use m_outlinePixels
			m_outlinePixels = _fPixels;
			m_bUpdateVertices = true;
		}

		virtual void setPosition(float _x, float _y) 
		{ 
			m_position = D3DXVECTOR2(_x, _y);
			m_bUpdateVertices = true;
		}

	};

	class DX9RectangleShape : public DX9Shape
	{
	protected:

		CUSTOMVERTEX m_vertices[9];// 4 + 5 to for linestrip to close the quad
		D3DXVECTOR2 m_points[4];

		LPDIRECT3DVERTEXBUFFER9		m_pVB; // Vertex buffer

	public:

		DX9RectangleShape()
		{
			m_pVB = nullptr;
			if (FAILED(m_pD3DDevice->CreateVertexBuffer(9 * sizeof(CUSTOMVERTEX),
				0, D3DFVF_CUSTOMVERTEX,
				D3DPOOL_DEFAULT, &m_pVB, NULL)))
			{
				return;
			}
			setSize(100.f, 100.f);
		}

		virtual ~DX9RectangleShape() 
		{
			//release le vertex buffer
			if (m_pVB)
				m_pVB->Release();
		}

		virtual void draw()
		{
			if (m_bUpdateVertices)
			{
				m_bUpdateVertices = false;

				// Build our matrix to rotate, scale and position our sprite
				D3DXMATRIX mat;

				// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
				D3DXMatrixTransformation2D(&mat, m_pOrigin, 0.f, m_pScale, m_pOrigin, m_fRotation, &m_position);

				// Fill vertex array with transformed points and color
				D3DXVECTOR4 vout;
				for (int i = 0; i < 4; i++)
				{
					D3DXVec2Transform(&vout, &m_points[i], &mat);
					m_vertices[i].x = vout.x;
					m_vertices[i].y = vout.y;
					m_vertices[i].z = 0.0f;
					m_vertices[i].rhw = 1.0f;
					m_vertices[i].color = m_color;
				}

				if (D3DCOLOR_ISVISIBLE(m_outlineColor))
				{
					for (int i = 4; i < 9; i++)
					{
						m_vertices[i] = m_vertices[i - 4];
						m_vertices[i].color = m_outlineColor;
					}
				}

				// Copy vertex array to vertex buffer
				VOID* pVertices;
				if (FAILED(m_pVB->Lock(0, sizeof(m_vertices), (void**)&pVertices, 0)))
					return;
				memcpy(pVertices, m_vertices, sizeof(m_vertices));
				m_pVB->Unlock();
			}

			// Alpha
			// alpha * sourceColor + dest Color * (1-alpha)
			m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			m_pD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_DESTBLENDALPHA);

			// Draw
			m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
			m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			if (m_bUseColor)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
			}

			// Outline
			if (m_bUseOutline)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 4, 4);
			}
		}

		virtual void setSize(float _x, float _y)
		{
			m_points[0] = D3DXVECTOR2(0.0f, 0.0f);
			m_points[1] = D3DXVECTOR2(_x, 0.0f);
			m_points[2] = D3DXVECTOR2(_x, _y);
			m_points[3] = D3DXVECTOR2(0.0f, _y);
			m_bUpdateVertices = true;
		}
	};

	class DX9CircleShape : public DX9Shape
	{
		CUSTOMVERTEX* m_vertices;
		D3DXVECTOR2* m_points;
		int m_iNbPoints;
		int m_iNbTriangles;

		LPDIRECT3DVERTEXBUFFER9		m_pVB; // Vertex buffer

	public:

		DX9CircleShape()
		{
			m_points = nullptr;
			m_vertices = nullptr;
			m_pVB = nullptr;
			setSize(100.f);
		}

		~DX9CircleShape()
		{
			if (m_points)
				delete[] m_points;

			if (m_vertices)
				delete[] m_vertices;

			//release le vertex buffer
			m_pVB->Release();
		}

		virtual void setRadius(float _r)
		{
			setSize(_r);
		}

		void setNbPoints(int _iNbPoints)
		{
			if (_iNbPoints == m_iNbPoints)
			{
				return;
			}

			if (m_points)
				delete[] m_points;

			if (m_vertices)
				delete[] m_vertices;

			//release le vertex buffer
			if (m_pVB)
				m_pVB->Release();

			m_iNbPoints = _iNbPoints;
			m_points = new D3DXVECTOR2[m_iNbPoints];
			m_vertices = new CUSTOMVERTEX[2 * m_iNbPoints];

			if (FAILED(m_pD3DDevice->CreateVertexBuffer(2 * m_iNbPoints * sizeof(CUSTOMVERTEX),
				0, D3DFVF_CUSTOMVERTEX,
				D3DPOOL_DEFAULT, &m_pVB, NULL)))
			{
				m_iNbPoints = 0;
				return;
			}

		}

		void setSize(float _fSize, int _iNbSides = 20)
		{
			m_iNbTriangles = _iNbSides;

			setNbPoints(_iNbSides + 2);

			// Set vertices 
			// Origin +
			//      5   6
			//             
			//   4    0    1
			//             
			//      3   2 
			float theta = 2 * 3.14f / m_iNbTriangles;

			// First is center
			m_points[0] = D3DXVECTOR2(_fSize, _fSize) + D3DXVECTOR2(0.f, 0.f);

			// then around
			D3DXVECTOR2 p;
			for (int i = 0; i <= m_iNbTriangles; ++i)
			{
				m_points[i + 1] = D3DXVECTOR2(_fSize, _fSize) + D3DXVECTOR2(_fSize*cos(i*theta), _fSize*sin(i*theta));
			}
			m_bUpdateVertices = true;
		}

		void draw()
		{
			if (m_bUpdateVertices)
			{
				m_bUpdateVertices = false;

				// Build our matrix to rotate, scale and position our sprite
				D3DXMATRIX mat;

				// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
				D3DXMatrixTransformation2D(&mat, m_pOrigin, 0.f, m_pScale, m_pOrigin, m_fRotation, &m_position);

				// Fill vertex array with transformed points and color
				D3DXVECTOR4 vout;
				for (int i = 0; i <= m_iNbPoints; i++)
				{
					D3DXVec2Transform(&vout, &m_points[i], &mat);
					m_vertices[i].x = vout.x;
					m_vertices[i].y = vout.y;
					m_vertices[i].z = 0.0f;
					m_vertices[i].rhw = 1.0f;
					m_vertices[i].color = m_color;
				}
				if (D3DCOLOR_ISVISIBLE(m_outlineColor))
				{
					for (int i = m_iNbPoints + 1; i < 2 * m_iNbPoints; i++)
					{
						m_vertices[i] = m_vertices[i - m_iNbPoints];
						m_vertices[i].color = m_outlineColor;
					}
				}

				// Copy vertex array to vertex buffer
				VOID* pVertices;
				if (FAILED(m_pVB->Lock(0, 2 * m_iNbPoints * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
					return;
				memcpy(pVertices, m_vertices, 2 * m_iNbPoints * sizeof(CUSTOMVERTEX));
				m_pVB->Unlock();
			}

			// Alpha
			// alpha * sourceColor + dest Color * (1-alpha)
			m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			m_pD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_DESTBLENDALPHA);

			// Draw
			m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
			m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			if (m_bUseColor)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_iNbTriangles);
			}

			// Outline
			if (m_bUseOutline)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, m_iNbPoints+1, m_iNbPoints-2);
			}
		}

	};

	class DX9ArrowShape : public DX9Shape
	{
		CUSTOMVERTEX m_vertices[7];// 3 + 4 for linestrip to close the triangle
		D3DXVECTOR2 m_points[3];

		LPDIRECT3DVERTEXBUFFER9		m_pVB; // Vertex buffer	public:

	public:

		DX9ArrowShape()
		{
			m_pVB = nullptr;
			if (FAILED(m_pD3DDevice->CreateVertexBuffer(7 * sizeof(CUSTOMVERTEX),
				0, D3DFVF_CUSTOMVERTEX,
				D3DPOOL_DEFAULT, &m_pVB, NULL)))
			{
				return;
			}

			m_points[0] = D3DXVECTOR2(0.0f, 0.5f);
			m_points[1] = D3DXVECTOR2(0.0f, -0.5f);
			m_points[2] = D3DXVECTOR2(1.0f, 0.0f);
		}

		~DX9ArrowShape()
		{
			//release le vertex buffer
			if (m_pVB)
				m_pVB->Release();
		}

		virtual void draw()
		{
			if (m_bUpdateVertices)
			{
				m_bUpdateVertices = false;

				// Build our matrix to rotate, scale and position our sprite
				D3DXMATRIX mat;

				// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
				D3DXMatrixTransformation2D(&mat, m_pOrigin, 0.f, m_pScale, m_pOrigin, m_fRotation, &m_position);

				// Fill vertex array with transformed points and color
				D3DXVECTOR4 vout;
				for (int i = 0; i < 3; i++)
				{
					D3DXVec2Transform(&vout, &m_points[i], &mat);
					m_vertices[i].x = vout.x;
					m_vertices[i].y = vout.y;
					m_vertices[i].z = 0.0f;
					m_vertices[i].rhw = 1.0f;
					m_vertices[i].color = m_color;
				}

				if (D3DCOLOR_ISVISIBLE(m_outlineColor))
				{
					for (int i = 3; i < 7; i++)
					{
						m_vertices[i] = m_vertices[i - 3];
						m_vertices[i].color = m_outlineColor;
					}
				}

				// Copy vertex array to vertex buffer
				VOID* pVertices;
				if (FAILED(m_pVB->Lock(0, sizeof(m_vertices), (void**)&pVertices, 0)))
					return;
				memcpy(pVertices, m_vertices, sizeof(m_vertices));
				m_pVB->Unlock();
			}

			// Alpha
			// alpha * sourceColor + dest Color * (1-alpha)
			m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			m_pD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_DESTBLENDALPHA);

			// Draw
			m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
			m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			if (m_bUseColor)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 3);
			}

			// Outline
			if (m_bUseOutline)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 3, 3);
			}
		}

		virtual void setSize(float _x, float _y)
		{
			setScale(_x, _y);
			m_bUpdateVertices = true;
		}

		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd)
		{
			float dx = _xEnd - _xStart;
			float dy = _yEnd - _yStart;
			Vector2f v(dx, dy);
			Vector2f right(1.0f, 0.f);
			float fAngle = right.angle(v);
			fAngle = dy > 0.f ? fAngle : -fAngle;
			setPosition(_xStart, _yStart);
			m_pScale->x = v.length();
			setRotation(fAngle);
			m_bUpdateVertices = true;
		}

	};

	class DX9LineShape : public DX9Shape
	{
		CUSTOMVERTEX m_vertices[9];// 4 + 5 for linestrip to close the rectangle
		D3DXVECTOR2 m_points[4];

		LPDIRECT3DVERTEXBUFFER9		m_pVB; // Vertex buffer	public:

	public:

		DX9LineShape()
		{
			m_pVB = nullptr;
			if (FAILED(m_pD3DDevice->CreateVertexBuffer(9 * sizeof(CUSTOMVERTEX),
				0, D3DFVF_CUSTOMVERTEX,
				D3DPOOL_DEFAULT, &m_pVB, NULL)))
			{
				return;
			}

			m_points[0] = D3DXVECTOR2(0.0f, 0.5f);
			m_points[1] = D3DXVECTOR2(0.0f, -0.5f);
			m_points[2] = D3DXVECTOR2(1.0f, -0.5f);
			m_points[3] = D3DXVECTOR2(1.0f, 0.5f);
		}

		~DX9LineShape()
		{
			//release le vertex buffer
			if (m_pVB)
				m_pVB->Release();
		}

		virtual void draw()
		{
			if (m_bUpdateVertices)
			{
				m_bUpdateVertices = false;

				// Build our matrix to rotate, scale and position our sprite
				D3DXMATRIX mat;

				// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
				D3DXMatrixTransformation2D(&mat, m_pOrigin, 0.f, m_pScale, m_pOrigin, m_fRotation, &m_position);

				// Fill vertex array with transformed points and color
				D3DXVECTOR4 vout;
				for (int i = 0; i < 4; i++)
				{
					D3DXVec2Transform(&vout, &m_points[i], &mat);
					m_vertices[i].x = vout.x;
					m_vertices[i].y = vout.y;
					m_vertices[i].z = 0.0f;
					m_vertices[i].rhw = 1.0f;
					m_vertices[i].color = m_color;
				}

				if (D3DCOLOR_ISVISIBLE(m_outlineColor))
				{
					for (int i = 4; i < 9; i++)
					{
						m_vertices[i] = m_vertices[i - 4];
						m_vertices[i].color = m_outlineColor;
					}
				}

				// Copy vertex array to vertex buffer
				VOID* pVertices;
				if (FAILED(m_pVB->Lock(0, sizeof(m_vertices), (void**)&pVertices, 0)))
					return;
				memcpy(pVertices, m_vertices, sizeof(m_vertices));
				m_pVB->Unlock();
			}

			// Alpha
			// alpha * sourceColor + dest Color * (1-alpha)
			m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			m_pD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_DESTBLENDALPHA);

			// Draw
			m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
			m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			if (m_bUseColor)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 4);
			}

			// Outline
			if (m_bUseOutline)
			{
				m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 4, 4);
			}
		}

		virtual void setSize(float _x, float _y)
		{
			setScale(_x, _y);
			m_bUpdateVertices = true;
		}

		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd)
		{
			float dx = _xEnd - _xStart;
			float dy = _yEnd - _yStart;
			Vector2f v(dx, dy);
			Vector2f right(1.0f, 0.f);
			float fAngle = right.angle(v);
			fAngle = dy > 0.f ? fAngle : -fAngle;
			setPosition(_xStart, _yStart);
			m_pScale->x = v.length();
			setRotation(fAngle);
			m_bUpdateVertices = true;
		}

	};
} // namespace crea

#endif // _DX9Shape_H