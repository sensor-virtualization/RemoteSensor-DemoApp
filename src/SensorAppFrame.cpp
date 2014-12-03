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

#include "SensorAppFrame.h"
#include "SensorAppFormFactory.h"
#include "SensorAppPanelFactory.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

SensorAppFrame::SensorAppFrame(void)
{
}

SensorAppFrame::~SensorAppFrame(void)
{
}

result
SensorAppFrame::OnInitializing(void)
{
	// Prepare Scene management.
	SceneManager* pSceneManager = SceneManager::GetInstance();
	static SensorAppFormFactory formFactory;
	static SensorAppPanelFactory panelFactory;
	pSceneManager->RegisterFormFactory(formFactory);
	pSceneManager->RegisterPanelFactory(panelFactory);
	pSceneManager->RegisterScene(L"workflow");

	pSceneManager->RegisterScene(MainScene, L"MainForm", L"");
	pSceneManager->RegisterScene(L"GravityScene", L"GravitySensorForm", L"");
	pSceneManager->RegisterScene(L"UserAccelScene", L"UserAccelForm", L"");
	pSceneManager->RegisterScene(L"DeviceOrientationScene", L"DeviceOrientationForm", L"");
	pSceneManager->RegisterScene(L"LightSensorScene", L"LightSensorForm", L"");
	pSceneManager->RegisterScene(L"GryroScene", L"GryroSensorForm", L"");
	pSceneManager->RegisterScene(L"RemoteGyroSensorScene", L"RemoteGyroSensorForm", L"");
	pSceneManager->RegisterScene(L"AccelSensorScene", L"AccelSensorForm", L"");
	pSceneManager->RegisterScene(L"MagneticSensorScene", L"MagneticSensorForm", L"");
	pSceneManager->RegisterScene(L"ProximitySensorScene", L"ProximitySensorForm", L"");
	pSceneManager->RegisterScene(L"TiltSensorScene", L"TiltSensorForm", L"");


	// Go to the scene.
	result r = pSceneManager->GoForward(SceneTransitionId(ID_SCNT_MAINSCENE));

	// TODO: Add your initialization code here
	return r;
}

result
SensorAppFrame::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your termination code here
	return r;
}
