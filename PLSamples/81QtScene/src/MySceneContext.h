/*/*********************************************************\
 *  File: MySceneContext.h                                 *
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


#ifndef __PLSAMPLE_81_QTSCENE_MYSCENECONTEXT_H__
#define __PLSAMPLE_81_QTSCENE_MYSCENECONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLQt/QPLSceneContext.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene context
*/
class MySceneContext : public PLQt::QPLSceneContext {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		MySceneContext();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MySceneContext();


	//[-------------------------------------------------------]
	//[ Protected virtual PLQt::QPLSceneContext functions     ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnCreateScene(PLScene::SceneContainer &cContainer);


};


#endif // __PLSAMPLE_81_QTSCENE_MYSCENECONTEXT_H__