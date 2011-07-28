/*********************************************************\
 *  File: MeshCreatorQuad.h                              *
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


#ifndef __PLMESH_MESHCREATOR_QUAD_H__
#define __PLMESH_MESHCREATOR_QUAD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLMesh/Creator/MeshCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Quad mesh creator class
*/
class MeshCreatorQuad : public MeshCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshCreatorQuad, "PLMesh", PLMesh::MeshCreator, "Quad mesh creator class")
		// Attributes
		pl_attribute(V1,		PLMath::Vector3,	PLMath::Vector3(-0.5f, -0.5f, 0.0f),	ReadWrite,	DirectValue,	"Vertex 1",			"")
		pl_attribute(V2,		PLMath::Vector3,	PLMath::Vector3( 0.5f, -0.5f, 0.0f),	ReadWrite,	DirectValue,	"Vertex 2",			"")
		pl_attribute(V3,		PLMath::Vector3,	PLMath::Vector3( 0.5f,  0.5f, 0.0f),	ReadWrite,	DirectValue,	"Vertex 3",			"")
		pl_attribute(V4,		PLMath::Vector3,	PLMath::Vector3(-0.5f,  0.5f, 0.0f),	ReadWrite,	DirectValue,	"Vertex 4",			"")
		pl_attribute(Offset,	PLMath::Vector3,	PLMath::Vector3( 0.0f,  0.0f, 0.0f),	ReadWrite,	DirectValue,	"Offset to center",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshCreatorQuad();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshCreatorQuad();


	//[-------------------------------------------------------]
	//[ Private virtual MeshCreator functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual Mesh *Create(Mesh &cMesh, PLCore::uint32 nLODLevel = 0, bool bStatic = true) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHCREATOR_QUAD_H__
