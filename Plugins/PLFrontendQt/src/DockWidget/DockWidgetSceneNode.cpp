/*********************************************************\
 *  File: DockWidgetSceneNode.cpp                        *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/qtreeview.h>
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <PLCore/Base/Class.h>
#include <PLEngine/Application/EngineApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneNodeInfoModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetSceneNode)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneNode::DockWidgetSceneNode(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidgetScene(pQMainWindow, pDockWidgetManager),
	SlotOnDestroy(this),
	m_pSceneNodeInfoModel(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		pQDockWidget->setWidget(pQTreeView);
		m_pSceneNodeInfoModel = new DataModels::SceneNodeInfoModel(pQDockWidget);
		pQTreeView->setModel(m_pSceneNodeInfoModel);
		pQTreeView->expandToDepth(0);

		// Set a default start node to have a decent standard behaviour
		SceneNode *pSceneNode = nullptr;
		{
			CoreApplication *pApplication = CoreApplication::GetApplication();
			if (pApplication && pApplication->IsInstanceOf("PLEngine::EngineApplication"))
				pSceneNode = reinterpret_cast<SceneNode*>(static_cast<PLEngine::EngineApplication*>(pApplication)->GetScene());
			SelectObject(pSceneNode);
		}

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::BottomDockWidgetArea, pQDockWidget);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneNode::~DockWidgetSceneNode()
{
}

/**
*  @brief
*    Selects the given object
*/
void DockWidgetSceneNode::SelectObject(Object *pObject)
{
	// Is there a scene node info model instance?
	if (m_pSceneNodeInfoModel) {
		// We only know "PLScene::SceneNode"
		SceneNode *pSceneNode = nullptr;
		if (pObject && pObject->IsInstanceOf("PLScene::SceneNode"))
			pSceneNode = static_cast<SceneNode*>(pObject);

		// Disconnect event handler
		if (m_pSceneNodeInfoModel->GetSceneNode())
			m_pSceneNodeInfoModel->GetSceneNode()->SignalDestroy.Disconnect(SlotOnDestroy);

		// Set scene node
		m_pSceneNodeInfoModel->SetSceneNode(pSceneNode);

		// Connect event handler
		if (pSceneNode)
			pSceneNode->SignalDestroy.Connect(SlotOnDestroy);

		// Get encapsulated Qt dock widget
		QDockWidget *pQDockWidget = GetQDockWidget();
		if (pQDockWidget) {
			// Set window title
			QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
			if (pSceneNode) { 
				sQStringWindowTitle += ": ";
				sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + pSceneNode->GetAbsoluteName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
			}
			pQDockWidget->setWindowTitle(sQStringWindowTitle);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node assigned with this dock widget was destroyed
*/
void DockWidgetSceneNode::OnDestroy()
{
	// Argh! Mayday! We lost our scene node!
	// -> Now no object is currently selected
	SelectObject(nullptr);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
