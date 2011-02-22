/*********************************************************\
 *  File: SPK_PLPointRenderer.cpp                        *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Tools.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include <PLScene/Scene/SNCamera.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLPointRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Private definitions                                   ]
//[-------------------------------------------------------]
const float		  SPK_PLPointRenderer::PointSizeCurrent	= 32.0f;
const float		  SPK_PLPointRenderer::PointSizeMin		= 1.0f;
const float		  SPK_PLPointRenderer::PointSizeMax		= 1024.0f;
const std::string SPK_PLPointRenderer::PLBufferName("SPK_PLPointRenderer_Buffer");


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
SPK_PLPointRenderer *SPK_PLPointRenderer::Create(PLRenderer::Renderer &cRenderer, float fSize)
{
	SPK_PLPointRenderer *pSPK_PLPointRenderer = new SPK_PLPointRenderer(cRenderer, fSize);
	registerObject(pSPK_PLPointRenderer);
	return pSPK_PLPointRenderer;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLPointRenderer::SPK_PLPointRenderer(PLRenderer::Renderer &cRenderer, float fSize) : SPK_PLRenderer(cRenderer), SPK::PointRendererInterface(SPK::POINT_SQUARE, fSize),
	m_pSPK_PLBuffer(nullptr),
	m_pTextureHandler(new TextureHandler()),
	m_nTextureBlending(FixedFunctions::TextureEnvironment::Modulate),
	m_bWorldSize(false),
	m_fPixelPerUnit(-1.0f)
{
}

/**
*  @brief
*    Destructor of SPK_PLPointRenderer
*/
SPK_PLPointRenderer::~SPK_PLPointRenderer()
{
	delete m_pTextureHandler;
}

/**
*  @brief
*    Tells whether world size is enabled or not in this SPK_PLPointRenderer
*/
bool SPK_PLPointRenderer::IsWorldSizeEnabled() const
{
	return m_bWorldSize;
}

/**
*  @brief
*   Sets the way size of points is computed in this SPK_PLPointRenderer
*/
bool SPK_PLPointRenderer::EnableWorldSize(bool bWorldSizeEnabled)
{
	// We can only use world size if point parameters are
	m_bWorldSize = (bWorldSizeEnabled && GetPLRenderer().GetCapabilities().bPointParameters);
	return m_bWorldSize;
}

/**
*  @brief
*    Computes a conversion ratio between pixels and universe units
*/
void SPK_PLPointRenderer::SetPixelPerUnit(float fFovY, int nScreenHeight)
{
	if (fFovY < 0.0f || nScreenHeight < 0) {
		m_fPixelPerUnit = -1.0f;
	} else {
		// The pixel per unit is computed for a distance from the camera of nScreenHeight
		m_fPixelPerUnit = nScreenHeight/(2.0f*Math::Tan(fFovY*0.5f));
	}
}

/**
*  @brief
*    Sets the texture of this SPK_PLPointRenderer
*/
Texture *SPK_PLPointRenderer::GetTexture() const
{
	return m_pTextureHandler->GetResource();
}

/**
*  @brief
*    Gets the texture of this SPK_PLPointRenderer
*/
void SPK_PLPointRenderer::SetTexture(Texture *pTexture)
{
	m_pTextureHandler->SetResource(pTexture);
}

/**
*  @brief
*    Gets the texture blending function of this SPK_PLPointRenderer
*/
FixedFunctions::TextureEnvironment::Enum SPK_PLPointRenderer::GetTextureBlending() const
{
	return m_nTextureBlending;
}

/**
*  @brief
*    Sets the texture blending function of this SPK_PLPointRenderer
*/
void SPK_PLPointRenderer::SetTextureBlending(FixedFunctions::TextureEnvironment::Enum nTextureBlending)
{
	m_nTextureBlending = nTextureBlending;
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLPointRenderer::render(const SPK::Group &group)
{
	// Is there a valid m_pSPK_PLBuffer instance?
	if (m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
		VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Vertex buffer data
			const uint32 nVertexSize = pVertexBuffer->GetVertexSize();
			float *pfPosition = static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));

			// Fill the vertex buffer with the current data
			for (size_t i=0; i<group.getNbParticles(); i++) {
				// Get the particle
				const SPK::Particle &cParticle = group.getParticle(i);

				// Copy over the particle position into the vertex data
				pfPosition[0] = cParticle.position().x;
				pfPosition[1] = cParticle.position().y;
				pfPosition[2] = cParticle.position().z;
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!

				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(i, Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), group.getModel()->isEnabled(SPK::PARAM_ALPHA) ? cParticle.getParamCurrentValue(SPK::PARAM_ALPHA) : 1.0f));
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}

		// Setup render states
		InitBlending();
		InitRenderingHints();
		switch(type) {
			case SPK::POINT_SQUARE:
				GetPLRenderer().SetTextureBuffer();
				GetPLRenderer().SetRenderState(RenderState::PointSpriteEnable, false);
				// [TODO] Currently, GL_POINT_SMOOTH is not supported by PLRenderer
				// glDisable(GL_POINT_SMOOTH);
				break;

			case SPK::POINT_SPRITE:
				m_pTextureHandler->Bind();
				GetPLRenderer().SetRenderState(RenderState::PointSpriteEnable, true);

				{ // Get the fixed functions interface
					FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
					if (pFixedFunctions)
						pFixedFunctions->SetTextureStageState(0, FixedFunctions::TextureStage::ColorTexEnv, GetTextureBlending());
				}
				break;

			case SPK::POINT_CIRCLE:
				GetPLRenderer().SetTextureBuffer();
				GetPLRenderer().SetRenderState(RenderState::PointSpriteEnable, false);
				// [TODO] Currently, GL_POINT_SMOOTH is not supported by PLRenderer
				// glEnable(GL_POINT_SMOOTH);
				break;
		}
		if (m_bWorldSize) {
			EnablePointParameter(size, true);
		} else {
			GetPLRenderer().SetRenderState(RenderState::PointScaleEnable, false);
			GetPLRenderer().SetRenderState(RenderState::PointSize,		  Tools::FloatToUInt32(size));
		}

		// Get the fixed functions interface
		FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
		if (pFixedFunctions) {
			// Make the vertex buffer to the current renderer vertex buffer
			pFixedFunctions->SetVertexBuffer(pVertexBuffer);

			// Draw
			GetPLRenderer().DrawPrimitives(Primitive::PointList, 0, group.getNbParticles());
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SPK::PointRendererInterface functions  ]
//[-------------------------------------------------------]
bool SPK_PLPointRenderer::setType(SPK::PointType type)
{
	// We can only use point sprites if it is available
	if ((type != SPK::POINT_SPRITE) || GetPLRenderer().GetCapabilities().bPointSprite) {
		// *thumbs up* - all is fine
		this->type = type;

		// Done
		return true;
	} else {
		// *thumbs down* - the renderer is not capable of everything we need
		return false;
	}
}


//[-------------------------------------------------------]
//[ Public virtual SPK::BufferHandler functions           ]
//[-------------------------------------------------------]
void SPK_PLPointRenderer::createBuffers(const SPK::Group &group)
{
	// Create the SPK_PLBuffer instance
	m_pSPK_PLBuffer = static_cast<SPK_PLBuffer*>(group.createBuffer(PLBufferName, PLBufferCreator(GetPLRenderer(), 1, 0, SPK::TEXTURE_NONE), 0U, false));
}

void SPK_PLPointRenderer::destroyBuffers(const SPK::Group &group)
{
	group.destroyBuffer(PLBufferName);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Enables the use of point parameters
*/
void SPK_PLPointRenderer::EnablePointParameter(float fSize, bool bDistance) const
{
	float fPixelPerUnit = m_fPixelPerUnit;
	if (fPixelPerUnit < 0.0f) {
		// The pixel per unit is computed for a distance from the camera of nScreenHeight
		const float fScreenHeight = GetPLRenderer().GetViewport().GetHeight();
		const float fFovY = SNCamera::GetCamera() ? static_cast<float>(SNCamera::GetCamera()->GetFOV()*Math::DegToRad) : 45.0f;
		fPixelPerUnit = fScreenHeight/(2.0f*Math::Tan(fFovY*0.5f));
	}

	// Derived size = size*sqrt(1/(A + B*distance + C*distance�))
	if (bDistance) {
		const float fSqrtC = PointSizeCurrent/(fSize*fPixelPerUnit);
		GetPLRenderer().SetRenderState(RenderState::PointScaleA, Tools::FloatToUInt32(0.0f));			// A = 0
		GetPLRenderer().SetRenderState(RenderState::PointScaleB, Tools::FloatToUInt32(0.0f));			// B = 0
		GetPLRenderer().SetRenderState(RenderState::PointScaleC, Tools::FloatToUInt32(fSqrtC*fSqrtC));	// C = (PointSizeCurrent/(size*fPixelPerUnit))�
	} else {
		const float fSqrtA = PointSizeCurrent/fSize;
		GetPLRenderer().SetRenderState(RenderState::PointScaleA, Tools::FloatToUInt32(fSqrtA*fSqrtA));	// A = (PointSizeCurrent/size)�
		GetPLRenderer().SetRenderState(RenderState::PointScaleB, Tools::FloatToUInt32(0.0f));			// B = 0
		GetPLRenderer().SetRenderState(RenderState::PointScaleC, Tools::FloatToUInt32(0.0f));			// C = 0
	}

	// Set point size and the minimum/maximum point size
	GetPLRenderer().SetRenderState(RenderState::PointSize,		  Tools::FloatToUInt32(PointSizeCurrent));
	GetPLRenderer().SetRenderState(RenderState::PointSizeMin,	  Tools::FloatToUInt32(PointSizeMin));
	GetPLRenderer().SetRenderState(RenderState::PointSizeMax,	  Tools::FloatToUInt32(PointSizeMax));
	GetPLRenderer().SetRenderState(RenderState::PointScaleEnable, true);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL