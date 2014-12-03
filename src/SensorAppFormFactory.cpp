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

#include "SensorAppFormFactory.h"
#include "SensorAppMainForm.h"
#include "SensorsAppAccelForm.h"
#include "SensorsAppAccelForm.h"
#include "SensorsAppMagneticForm.h"
#include "SensorsAppProximityForm.h"
#include "SensorsAppLightForm.h"
#include "SensorsAppGyroForm.h"
#include "SensorsAppRemoteGyroForm.h"
#include "SensorsAppTiltForm.h"
#include "SensorsAppOrientationForm.h"
#include "SensorsAppUserAccelForm.h"
#include "SensorsAppGravityForm.h"
#include "AppResourceId.h"

using namespace Tizen::Ui::Scenes;


SensorAppFormFactory::SensorAppFormFactory(void)
{
}

SensorAppFormFactory::~SensorAppFormFactory(void)
{
}

Tizen::Ui::Controls::Form*
SensorAppFormFactory::CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Form* pNewForm = null;

	if (formId == IDF_FORM)
	{
		SensorAppMainForm* pForm = new SensorAppMainForm();
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"GravitySensorForm")
	{
		SensorsAppGravityForm* pForm = new (std::nothrow) SensorsAppGravityForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"UserAccelForm")
	{
		SensorsAppUserAccelForm* pForm = new (std::nothrow) SensorsAppUserAccelForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"DeviceOrientationForm")
	{
		SensorsAppOrientationForm* pForm = new (std::nothrow) SensorsAppOrientationForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"LightSensorForm")
	{
		SensorsAppLightForm* pForm = new (std::nothrow) SensorsAppLightForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"GryroSensorForm")
	{
		SensorsAppGyroForm* pForm = new (std::nothrow) SensorsAppGyroForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"RemoteGyroSensorForm")
	{
		SensorsAppRemoteGyroForm* pForm = new (std::nothrow) SensorsAppRemoteGyroForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"AccelSensorForm")
	{
		SensorsAppAccelForm* pForm = new (std::nothrow)SensorsAppAccelForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"MagneticSensorForm")
	{
		SensorsAppMagneticForm* pForm = new (std::nothrow)SensorsAppMagneticForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"ProximitySensorForm")
	{
		SensorsAppProximityForm* pForm = new (std::nothrow) SensorsAppProximityForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == L"TiltSensorForm")
	{
		SensorsAppTiltForm* pForm = new (std::nothrow) SensorsAppTiltForm();
		TryReturn(pForm, null, "[%s] Form creation failed.", GetErrorMessage(E_OUT_OF_MEMORY));
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else
	{
		return null;
	}
	// TODO:
	// Add your form creation code here

	return pNewForm;
}
