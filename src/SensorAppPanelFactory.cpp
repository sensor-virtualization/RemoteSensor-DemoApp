//
// Tizen C++ SDK
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "SensorAppPanelFactory.h"
#include <FUi.h>

using namespace Tizen::Ui::Scenes;


SensorAppPanelFactory::SensorAppPanelFactory(void)
{
}

SensorAppPanelFactory::~SensorAppPanelFactory(void)
{
}

Tizen::Ui::Controls::Panel*
SensorAppPanelFactory::CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Panel* pNewPanel = null;

	// TODO:
	// Add your panel creation code here
	return pNewPanel;
}
