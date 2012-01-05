/*********************************************************\
 *  File: DockWidgetSceneNode.h                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_SCENENODE_H__
#define __PLFRONTENDQT_DOCKWIDGET_SCENENODE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidgetScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QMainWindow;
QT_END_NAMESPACE
namespace PLScene {
	class SceneNode;
}
namespace PLFrontendQt {
	namespace DataModels {
		class SceneNodeInfoModel;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node Qt dock widget class
*
*  @note
*    - Similar to "PLFrontend::DockWidgetObject", but specialized in scene nodes
*    - By default, the "PLEngine::EngineApplication::GetScene()" scene node is used, but only
*      if "PLCore::CoreApplication::GetApplication()" is an "PLEngine::EngineApplication"-instance
*/
class DockWidgetSceneNode : public DockWidgetScene {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetSceneNode, "PLFrontendQt", PLFrontendQt::DockWidgetScene, "Scene node Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Scene Node")
		pl_properties_end
		#ifdef PLFRONTENDQT_EXPORTS	// The following is only required when compiling PLFrontendQt
			// Methods
			pl_method_1(SelectObject,	pl_ret_type(void),	PLCore::Object*,	"Selects the given object. Object to select as first parameter.",	"")
		#endif
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
		// Slots
		pl_slot_0(OnDestroy,	"Called when the scene node assigned with this dock widget was destroyed",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pQMainWindow
		*    Pointer to Qt main window, can be a null pointer (in this case you're responsible for destroying this instance)
		*  @param[in] pDockWidgetManager
		*    Optional pointer to the dock widget manager this dock widget should be registered to, can be a null pointer
		*/
		PLFRONTENDQT_API DockWidgetSceneNode(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetSceneNode();

		/**
		*  @brief
		*    Selects the given object
		*
		*  @param[in] pObject
		*    Object to select, can be a null pointer
		*/
		PLFRONTENDQT_API void SelectObject(PLCore::Object *pObject);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node assigned with this dock widget was destroyed
		*/
		void OnDestroy();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DataModels::SceneNodeInfoModel *m_pSceneNodeInfoModel;	/**< Scene node info model, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_SCENENODE_H__
