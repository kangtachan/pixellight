/*********************************************************\
 *  File: SRPDirectionalLightingShadersMaterial.h        *
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


#ifndef __PLCOMPOSITING_GENERAL_DIRECTIONALLIGHTING_MATERIAL_H__
#define __PLCOMPOSITING_GENERAL_DIRECTIONALLIGHTING_MATERIAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Material;
	class Renderer;
	class Parameter;
	class RenderStates;
	class TextureBuffer;
	class ProgramUniform;
	class ProgramAttribute;
	class ProgramGenerator;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    SRPDirectionalLightingShaders-material
*/
class SRPDirectionalLightingShadersMaterial {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Texture filtering modes
		*/
		enum ETextureFiltering {
			NoFiltering   = 0,	/**< No filtering */
			Bilinear      = 1,	/**< Bilinear */
			Anisotropic2  = 2,	/**< Anisotropic x2 */
			Anisotropic4  = 4,	/**< Anisotropic x4 */
			Anisotropic8  = 8,	/**< Anisotropic x8 */
			Anisotropic16 = 16	/**< Anisotropic x16 */
		};
		/**
		*  @brief
		*    Texture filtering modes
		*/
		pl_enum(ETextureFiltering)
			pl_enum_value(NoFiltering,		"No filtering")
			pl_enum_value(Bilinear,			"Bilinear")
			pl_enum_value(Anisotropic2,		"Anisotropic x2")
			pl_enum_value(Anisotropic4,		"Anisotropic x4")
			pl_enum_value(Anisotropic8,		"Anisotropic x8")
			pl_enum_value(Anisotropic16,	"Anisotropic x16")
		pl_enum_end

		/**
		*  @brief
		*    Environment flags
		*/
		enum EEnvironmentFlags {
			EnvironmentVertexNormal				= 1<<0,	/**< There are vertex normals available */
			EnvironmentVertexTexCoord0			= 1<<1,	/**< Texture coordinates at stage 0 are available */
			EnvironmentVertexTexCoord1			= 1<<2,	/**< Texture coordinates at stage 1 are available */
			EnvironmentNormalMappingPossible	= 1<<3,	/**< Normal mapping is possible (normal & tangent & binormal data available) */
			EnvironmentLightingEnabled			= 1<<4,	/**< Lighting enabled */
			EnvironmentGlowEnabled				= 1<<6,	/**< Glow enabled */
			EnvironmentDOFEnabled				= 1<<5	/**< DOF enabled */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			PLRenderer::ProgramAttribute *pVertexTexCoord0;
			PLRenderer::ProgramAttribute *pVertexTexCoord1;
			PLRenderer::ProgramAttribute *pVertexNormal;
			PLRenderer::ProgramAttribute *pVertexTangent;
			PLRenderer::ProgramAttribute *pVertexBinormal;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pNormalScale;
			PLRenderer::ProgramUniform *pObjectSpaceToViewSpaceMatrix;
			PLRenderer::ProgramUniform *pObjectSpaceToClipSpaceMatrix;
			PLRenderer::ProgramUniform *pEyePos;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pAmbientColor;
			PLRenderer::ProgramUniform *pDiffuseColor;
			PLRenderer::ProgramUniform *pDiffuseMap;
			PLRenderer::ProgramUniform *pAlphaReference;
			PLRenderer::ProgramUniform *pDiffuseRampMap;
			PLRenderer::ProgramUniform *pAmbientOcclusionMap;
			PLRenderer::ProgramUniform *pAmbientOcclusionFactor;
			PLRenderer::ProgramUniform *pLightMap;
			PLRenderer::ProgramUniform *pLightMapColor;
			PLRenderer::ProgramUniform *pEmissiveMap;
			PLRenderer::ProgramUniform *pEmissiveMapColor;
			PLRenderer::ProgramUniform *pReflectionColor;
			PLRenderer::ProgramUniform *pReflectivity;
			PLRenderer::ProgramUniform *pReflectivityMap;
			PLRenderer::ProgramUniform *pFresnelConstants;
			PLRenderer::ProgramUniform *pReflectionMap;
			PLRenderer::ProgramUniform *pViewSpaceToWorldSpace;
			PLRenderer::ProgramUniform *pNormalMap;
			PLRenderer::ProgramUniform *pNormalMapBumpiness;
			PLRenderer::ProgramUniform *pDetailNormalMap;
			PLRenderer::ProgramUniform *pDetailNormalMapBumpiness;
			PLRenderer::ProgramUniform *pDetailNormalMapUVScale;
			PLRenderer::ProgramUniform *pHeightMap;
			PLRenderer::ProgramUniform *pParallaxScaleBias;
			PLRenderer::ProgramUniform *pLightDirection;
			PLRenderer::ProgramUniform *pLightColor;
			PLRenderer::ProgramUniform *pSpecularColor;
			PLRenderer::ProgramUniform *pSpecularExponent;
			PLRenderer::ProgramUniform *pSpecularMap;
			PLRenderer::ProgramUniform *pSpecularRampMap;
			PLRenderer::ProgramUniform *pEdgeRampMap;
			PLRenderer::ProgramUniform *pGlow;
			PLRenderer::ProgramUniform *pGlowMap;
			PLRenderer::ProgramUniform *pDOFParams;
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderStates
		*    Used to 'translate' render state strings
		*  @param[in] cMaterial
		*    Owner material
		*  @param[in] cProgramGenerator
		*    Program generator
		*/
		SRPDirectionalLightingShadersMaterial(PLRenderer::RenderStates &cRenderStates, PLRenderer::Material &cMaterial, PLRenderer::ProgramGenerator &cProgramGenerator);

		/**
		*  @brief
		*    Destructur
		*/
		~SRPDirectionalLightingShadersMaterial();

		/**
		*  @brief
		*    Makes this material to the currently used one
		*
		*  @param[in] nRendererFlags
		*    SRPDirectionalLightingShaders-flags to use
		*  @param[in] nEnvironmentFlags
		*    Environment flags to use (see EEnvironmentFlags)
		*  @param[in] nTextureFiltering
		*    Texture filtering
		*
		*  @return
		*    Generated program user data, do NOT delete the memory the pointer points to
		*/
		GeneratedProgramUserData *MakeMaterialCurrent(PLGeneral::uint32 nRendererFlags, PLGeneral::uint32 nEnvironmentFlags, ETextureFiltering nTextureFiltering);


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Vertex shader flags, flag names become to source code definitions
		*/
		enum EVertexShaderFlags {
			VS_TEXCOORD0				= 1<<0,	/**< Use texture coordinate 0 */
			VS_TEXCOORD1				= 1<<1,	/**< Use texture coordinate 1 */
			VS_NORMAL					= 1<<2,	/**< Use vertex normal */
				VS_TWOSIDEDLIGHTING		= 1<<3,	/**< Two sided lighting possible? (VS_NORMAL should be defined!) */
				VS_TANGENT_BINORMAL		= 1<<4,	/**< Use vertex tangent and binormal (VS_NORMAL should be defined!) */
					VS_PARALLAXMAPPING	= 1<<5,	/**< Perform parallax mapping (VS_NORMAL and VS_TANGENT_BINORMAL should be defined!) */
			VS_VIEWSPACEPOSITION		= 1<<6	/**< Calculate the view space position of the vertex (required for reflections and lighting) */
		};

		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_TEXCOORD0						= 1<<0,		/**< Use texture coordinate 0 */
			FS_TEXCOORD1						= 1<<1,		/**< Use texture coordinate 1 */
			FS_NORMAL							= 1<<2,		/**< Use vertex normal */
				FS_TANGENT_BINORMAL				= 1<<3,		/**< Use vertex tangent and binormal (FS_NORMAL should be defined!) */
					FS_PARALLAXMAPPING			= 1<<4,		/**< Perform parallax mapping (FS_NORMAL and FS_TANGENT_BINORMAL should be defined!) */
			FS_GAMMACORRECTION					= 1<<5,		/**< Use gamma correction (sRGB to linear space) */
			FS_DIFFUSEMAP						= 1<<6,		/**< Take diffuse map into account */
				FS_ALPHATEST					= 1<<7,		/**< Use alpha test to discard fragments (FS_DIFFUSEMAP should be defined!) */
			FS_DIFFUSERAMPMAP					= 1<<8,		/**< Use diffuse ramp map */
			FS_AMBIENTOCCLUSIONMAP				= 1<<9,		/**< Use ambient occlusion map */
			FS_LIGHTMAP							= 1<<10,	/**< Use light map */
			FS_EMISSIVEMAP						= 1<<11,	/**< Use emissive map */
			FS_REFLECTION						= 1<<12,	/**< Use reflection */
				FS_FRESNELREFLECTION			= 1<<13,	/**< Use fresnel reflection (FS_REFLECTION should be defined!) */
				FS_REFLECTIVITYMAP				= 1<<14,	/**< Use reflectivity map (FS_REFLECTION and FS_FRESNELREFLECTION or FS_2DREFLECTIONMAP or FS_CUBEREFLECTIONMAP should be defined!) */
				FS_2DREFLECTIONMAP				= 1<<15,	/**< Use 2D reflection mapping (FS_REFLECTION should be defined, can't be set together with FS_CUBEREFLECTIONMAP!) */
				FS_CUBEREFLECTIONMAP			= 1<<16,	/**< Use cube reflection mapping (FS_REFLECTION should be defined, can't be set together with FS_2DREFLECTIONMAP!) */
			FS_NORMALMAP						= 1<<17,	/**< Take normal map into account */
				FS_NORMALMAP_DXT5_XGXR			= 1<<18,	/**< DXT5 XGXR normal map (FS_NORMALMAP should be defined and FS_NORMALMAP_LATC2 not!) */
				FS_NORMALMAP_LATC2				= 1<<19,	/**< LATC2 normal map (FS_NORMALMAP should be defined and FS_NORMALMAP_DXT5_XGXR not!) */
				FS_DETAILNORMALMAP				= 1<<20,	/**< Take detail normal map into account (FS_NORMALMAP should be defined!) */
				FS_DETAILNORMALMAP_DXT5_XGXR	= 1<<21,	/**< DXT5 XGXR compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP should be defined and FS_DETAILNORMALMAP_LATC2 not!) */
				FS_DETAILNORMALMAP_LATC2		= 1<<22,	/**< LATC2 compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP should be defined and FS_DETAILNORMALMAP_DXT5_XGXR not!) */
			FS_LIGHTING							= 1<<23,	/**< Perform lighting */
				FS_SPECULAR						= 1<<24,	/**< Use specular (FS_LIGHTING should be set, too) */
					FS_SPECULARMAP				= 1<<25,	/**< Take specular map into account (FS_LIGHTING and FS_SPECULAR should be set, too) */
					FS_SPECULARRAMPMAP			= 1<<26,	/**< Take specular ramp map into account (FS_LIGHTING and FS_SPECULAR should be set, too) */
				FS_EDGERAMPMAP					= 1<<27,	/**< Use edge ramp map (FS_LIGHTING should be set, too) */
			FS_GLOW								= 1<<28,	/**< Use glow (FS_DOF is not allowed to be set as well) */
				FS_GLOWMAP						= 1<<29,	/**< Use glow map (FS_GLOW should be set, too) */
			FS_DOF								= 1<<30		/**< Use depth of field (FS_GLOW is not allowed to be set as well) */
		};


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		// Material parameter
		static const PLGeneral::String Glow;
		static const PLGeneral::String GlowMap;
		static const PLGeneral::String Opacity;
		static const PLGeneral::String SrcBlendFunc;
		static const PLGeneral::String DstBlendFunc;
		static const PLGeneral::String TwoSided;
		static const PLGeneral::String AlphaReference;
		static const PLGeneral::String DiffuseRampMap;
		static const PLGeneral::String IndexOfRefraction;
		static const PLGeneral::String FresnelReflectionPower;
		static const PLGeneral::String ReflectionColor;
		static const PLGeneral::String Reflectivity;
		static const PLGeneral::String NormalMapBumpiness;
		static const PLGeneral::String DetailNormalMap;
		static const PLGeneral::String DetailNormalMapBumpiness;
		static const PLGeneral::String DetailNormalMapUVScale;
		static const PLGeneral::String Parallax;
		static const PLGeneral::String SpecularColor;
		static const PLGeneral::String SpecularExponent;
		static const PLGeneral::String SpecularRampMap;
		static const PLGeneral::String EdgeRampMap;
		// Shader parameter
		static const PLGeneral::String DiffuseColor;
		static const PLGeneral::String LightMapColor;
		static const PLGeneral::String AmbientOcclusionFactor;
		static const PLGeneral::String EmissiveMapColor;
		static const PLGeneral::String VertexPosition;
		static const PLGeneral::String VertexTexCoord0;
		static const PLGeneral::String VertexTexCoord1;
		static const PLGeneral::String VertexNormal;
		static const PLGeneral::String VertexTangent;
		static const PLGeneral::String VertexBinormal;
		static const PLGeneral::String NormalScale;
		static const PLGeneral::String ObjectSpaceToViewSpaceMatrix;
		static const PLGeneral::String ObjectSpaceToClipSpaceMatrix;
		static const PLGeneral::String EyePos;
		static const PLGeneral::String AmbientColor;
		// static const PLGeneral::String AlphaReference;	// Already defined
		static const PLGeneral::String FresnelConstants;
		static const PLGeneral::String ViewSpaceToWorldSpace;
		static const PLGeneral::String ParallaxScaleBias;
		static const PLGeneral::String LightDirection;
		static const PLGeneral::String LightColor;
		// static const PLGeneral::String Glow;	// Already defined
		// static const PLGeneral::String GlowMap;	// Already defined
		static const PLGeneral::String DOFParams;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Synchronize this material cache with the owner
		*
		*  @param[in] nRendererFlags
		*    SRPDirectionalLightingShaders-flags to use
		*  @param[in] nEnvironmentFlags
		*    Environment flags to use (see EEnvironmentFlags)
		*/
		void Synchronize(PLGeneral::uint32 nRendererFlags, PLGeneral::uint32 nEnvironmentFlags);

		/**
		*  @brief
		*    Sets correct texture filtering modes
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] nStage
		*    Texture stage
		*  @param[in] nTextureFiltering
		*    Texture filtering
		*/
		void SetupTextureFiltering(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nStage, ETextureFiltering nTextureFiltering) const;

		/**
		*  @brief
		*    Called when a parameter has been changed (created, destroyed, value changed)
		*
		*  @param[in] cParameter
		*    The changed parameter
		*/
		void NotifyParameterChanged(PLRenderer::Parameter &cParameter);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLRenderer::Parameter&> EventHandlerParameterChanged;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// General
		PLRenderer::RenderStates			*m_pRenderStates;		/**< Used to 'translate' render state strings, always valid! */
		PLRenderer::Material				*m_pMaterial;			/**< Owner material, always valid! */
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, always valid! */
		PLGeneral::uint32					 m_nRendererFlags;		/**< Used SRPDirectionalLightingShaders-flags */
		PLGeneral::uint32					 m_nEnvironmentFlags;	/**< Used environment flags (see EEnvironmentFlags) */
		bool								 m_bSynchronized;		/**< Synchronized? */
		// Generated program
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */
		// Synchronized data
			// Glow
		float					   m_fGlow;
		PLRenderer::TextureBuffer *m_pGlowMap;
			// Opacity
		float					   m_fOpacity;
		PLGeneral::uint32		   m_nSrcBlendFunc;
		PLGeneral::uint32		   m_nDstBlendFunc;
			// Two sided
		bool					   m_bTwoSided;
			// Diffuse map and alpha reference
		PLGraphics::Color3		   m_cDiffuseColor;
		float					   m_fAlphaReference;
		PLRenderer::TextureBuffer *m_pDiffuseMap;
			// Diffuse ramp map
		PLRenderer::TextureBuffer *m_pDiffuseRampMap;
			// Ambient map and light map require texture coordinate set 1
		float					   m_fAmbientOcclusionFactor;
		PLRenderer::TextureBuffer *m_pAmbientOcclusionMap;
		PLGraphics::Color3		   m_cLightMapColor;
		PLRenderer::TextureBuffer *m_pLightMap;
			// Emissive map
		PLGraphics::Color3		   m_cEmissiveMapColor;
		PLRenderer::TextureBuffer *m_pEmissiveMap;
			// Index of refraction and fresnel reflection power
		float					   m_fIndexOfRefraction;
		float					   m_fFresnelReflectionPower;
			// (2D/cube) reflection map
		PLRenderer::TextureBuffer *m_pReflectionMap;
		bool					   m_b2DReflectionMap;
			// Figure out whether or not there's reflection on this material
		bool					   m_bReflection;
			// Reflection parameters
		PLRenderer::TextureBuffer *m_pReflectivityMap;
		float					   m_fReflectivity;
		PLGraphics::Color3		   m_cReflectionColor;
			// Normal map
		PLRenderer::TextureBuffer *m_pNormalMap;
		float					   m_fNormalMapBumpiness;
			// Detail normal map
		PLRenderer::TextureBuffer *m_pDetailNormalMap;
		float					   m_fDetailNormalMapBumpiness;
		PLMath::Vector2			   m_vDetailNormalMapUVScale;
			// Parallax mapping settings
		float					   m_fParallax;
		PLRenderer::TextureBuffer *m_pHeightMap;
			// Lighting and specular
		PLGraphics::Color3		   m_cSpecularColor;
		PLRenderer::TextureBuffer *m_pSpecularMap;
		float					   m_fSpecularExponent;
			// Specular ramp map
		PLRenderer::TextureBuffer *m_pSpecularRampMap;
			// Edge ramp map
		PLRenderer::TextureBuffer *m_pEdgeRampMap;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_GENERAL_DIRECTIONALLIGHTING_MATERIAL_H__
