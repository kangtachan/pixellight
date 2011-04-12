/*********************************************************\
 *  File: Application.h                                  *
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


#ifndef __PLDEMO_LIBROCKET_APPLICATION_H__
#define __PLDEMO_LIBROCKET_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEngine/Application/BasicSceneApplication.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace Rocket {
	namespace Core {
		class Context;
		class FileInterface;
		class RenderInterface;
		class SystemInterface;
	}
}
namespace libRocket_PL {
	class MessageFilterRocket;
}
namespace PLMath {
	class Vector2i;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
class Application : public PLEngine::BasicSceneApplication {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Application();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Application();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the size was changed
		*
		*  @param[in] vSize
		*    New size
		*/
		void NotifySize(const PLMath::Vector2i &vSize);

		/**
		*  @brief
		*    Called when a key is pressed down
		*
		*  @param[in] nKey
		*    Pressed key
		*  @param[in] nModifiers
		*    Modifier keys pressed
		*/
		void NotifyKeyDown(PLGeneral::uint32 nKey, PLGeneral::uint32 nModifiers);


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ConsoleApplication functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnDeInit();
		virtual void OnInit();


	//[-------------------------------------------------------]
	//[ Private virtual PLGui::GuiApplication functions       ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateMainWindow();


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::BasicSceneApplication functions ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateScene(PLScene::SceneContainer &cContainer);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes libRocket
		*/
		void InitRocket();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<const PLMath::Vector2i&>			   EventHandlerSize;
		PLCore::EventHandler<PLGeneral::uint32, PLGeneral::uint32> EventHandlerKeyDown;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Rocket::Core::Context				*m_pRocketContext;			/**< libRocket context, can be a null pointer */
		Rocket::Core::RenderInterface		*m_pRocketRenderInterface;	/**< libRocket render interface, can be a null pointer */
		Rocket::Core::SystemInterface		*m_pRocketSystemInterface;	/**< libRocket system interface, can be a null pointer */
		Rocket::Core::FileInterface			*m_pRocketFileInterface;	/**< libRocket file interface, can be a null pointer */
		libRocket_PL::MessageFilterRocket	*m_pMessageFilterRocket;	/**< Message filter that feeds PLGui messages into libRocket, can be a null pointer */


};


#endif // __PLDEMO_LIBROCKET_APPLICATION_H__
