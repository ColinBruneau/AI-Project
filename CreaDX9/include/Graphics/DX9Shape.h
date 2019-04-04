/***************************************************/
/* Nom:	DX9Shape.h
/* Description: DX9Shape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Shape_H
#define _DX9Shape_H

#include "Graphics\IShape.h"

namespace crea
{
#define D3DFVF_QUADCUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	class DX9Shape : public IShape
	{
	protected:
		D3DXVECTOR2 * m_pCenter;
		float m_fRotation;
		D3DXVECTOR2 *m_pScaleCenter;
		D3DXVECTOR2 *m_pScale;
		D3DXVECTOR2 m_position;
		D3DCOLOR m_color;
		D3DCOLOR m_outlineColor;
		float m_outlinePixels; 
		LPDIRECT3DDEVICE9 m_pD3DDevice;

	public:

		DX9Shape() 
		{  
			m_pCenter = nullptr; 
			m_fRotation = 0.f;
			m_pScaleCenter = nullptr;
			m_pScale = nullptr;
			m_position = D3DXVECTOR2(0.0f, 0.0f);
			m_color = D3DCOLOR_XRGB(255, 255, 255);
			m_outlineColor = D3DCOLOR_XRGB(255, 255, 255);
			m_outlinePixels = 1;
			m_pD3DDevice = nullptr;
		}

		virtual ~DX9Shape() { }

		virtual void draw() { }
		
		virtual void setColor(IColor* _pColor) 
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_color = pColor->getColor();
		}

		virtual void setOutlineColor(IColor* _pColor)
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_outlineColor = pColor->getColor();
		}

		virtual void setOutlineThickness(float _fPixels) 
		{ 
			m_outlinePixels = _fPixels;
		}

		virtual void setPosition(float _x, float _y) 
		{ 
			m_position = D3DXVECTOR2(_x, _y);
		}

	};

	class DX9RectangleShape : public IRectangleShape
	{
	protected:
		D3DXVECTOR2 * m_pCenter;
		float m_fRotation;
		D3DXVECTOR2 *m_pScaleCenter;
		D3DXVECTOR2 *m_pScale;
		D3DXVECTOR2 m_position;
		D3DCOLOR m_color;
		D3DCOLOR m_outlineColor;
		float m_outlinePixels;
		LPDIRECT3DDEVICE9 m_pD3DDevice;

		// A structure for our custom vertex type
		struct CUSTOMVERTEX
		{
			FLOAT x, y, z, rhw; // The transformed position for the vertex
			DWORD color;        // The vertex color
		};
		CUSTOMVERTEX m_vertices[4];
		D3DXVECTOR2 m_points[4];

		LPDIRECT3DVERTEXBUFFER9		m_pVB; // Vertex buffer

	public:

		DX9RectangleShape() 
		{
			m_pCenter = nullptr;
			m_fRotation = 0.f;
			m_pScaleCenter = nullptr;
			m_pScale = nullptr;
			m_position = D3DXVECTOR2(0.0f, 0.0f);
			m_color = D3DCOLOR_XRGB(255, 255, 255);
			m_outlineColor = D3DCOLOR_XRGB(255, 255, 255);
			m_outlinePixels = 1;

			m_pVB = nullptr;
			m_pD3DDevice = DX9Facade::Instance().m_pDevice;
			if (FAILED(m_pD3DDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
				0, D3DFVF_QUADCUSTOMVERTEX,
				D3DPOOL_DEFAULT, &m_pVB, NULL)))
			{
				return;
			}
		}

		virtual ~DX9RectangleShape() { }

		virtual void draw()
		{		
			// Build our matrix to rotate, scale and position our sprite
			D3DXMATRIX mat;

			// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
			D3DXMatrixTransformation2D(&mat, m_pScaleCenter, 0.f, m_pScale, m_pCenter, m_fRotation, &m_position);

			// todo: use m_outlineColor and m_outlinePixels
			// for now patch using a transparent version of the outline color...
			m_color = (D3DCOLOR)((((50) & 0xff) << 24) | (m_outlineColor & 0xffffff));

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

			// Copy vertex array to vertex buffer
			VOID* pVertices;
			if (FAILED(m_pVB->Lock(0, sizeof(m_vertices), (void**)&pVertices, 0)))
				return;
			memcpy(pVertices, m_vertices, sizeof(m_vertices));
			m_pVB->Unlock();

			// Alpha
			// alpha * sourceColor + dest Color * (1-alpha)
			m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			m_pD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_DESTBLENDALPHA);

			// Draw
			m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
			m_pD3DDevice->SetFVF(D3DFVF_QUADCUSTOMVERTEX);
			m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			
		}

		virtual void setColor(IColor* _pColor)
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_color = pColor->getColor();
		}

		virtual void setOutlineColor(IColor* _pColor)
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_outlineColor = pColor->getColor();
		}

		virtual void setOutlineThickness(float _fPixels)
		{
			m_outlinePixels = _fPixels;
		}

		virtual void setPosition(float _x, float _y)
		{
			m_position = D3DXVECTOR2(_x, _y);
		}

		virtual void setSize(float _x, float _y)
		{
			m_points[0] = D3DXVECTOR2(0.0f, _y);
			m_points[1] = D3DXVECTOR2(0.0f, 0.0f);
			m_points[2] = D3DXVECTOR2(_x, _y);
			m_points[3] = D3DXVECTOR2(_x, 0.0f);
		}

	};
} // namespace crea

#endif // _DX9Shape_H