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

#include <new>
#include <FApp.h>
#include <FIo.h>
#include <FSystem.h>
#include "SensorsAppProximityForm.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Uix::Sensor;
using namespace Tizen::Graphics;

SensorsAppProximityForm::SensorsAppProximityForm(void)
	: __sensorMgr()
{

}

SensorsAppProximityForm::~SensorsAppProximityForm(void)
{

}

bool
SensorsAppProximityForm::Initialize(void)
{
	// Set Form properties
	Form::Construct(FORM_STYLE_HEADER|FORM_STYLE_INDICATOR);
	Header* pHeader = this->GetHeader();
	SetName(L"ProximitySensorForm");
	pHeader->SetTitleText(L"Proximity");

	this->SetFormBackEventListener(this);

	return true;
}

result
SensorsAppProximityForm::OnInitializing(void)
{
	__sensorMgr.Construct();

	/* Check for the Sensors is supported in the current device or not */
	if (!__sensorMgr.IsAvailable(SENSOR_TYPE_PROXIMITY))
	{
		SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);
		AppAssert(pSceneManager->GoBackward(BackwardSceneTransition(MainScene)) == E_SUCCESS);

		return E_FAILURE;
	}

	/* Initialise Canvas */
	__pCanvas = new (std::nothrow) Canvas();
	result r = __pCanvas->Construct(GetBounds());
	if(r == E_SUCCESS)
	{
		__pCanvas->SetBackgroundColor(Color::GetColor(COLOR_ID_WHITE));
		__pCanvas->Clear();
		Invalidate(false);
	}
	Tizen::Ui::Controls::Label* _pLabelText;

	Rectangle RectCaption(Point(GetClientAreaBounds().x + 100, GetClientAreaBounds().y + 200), Dimension(500, 50));
	_pLabelText = new Label();
	_pLabelText->Construct(RectCaption, L"Proximity");
	_pLabelText->SetTextConfig(44, LABEL_TEXT_STYLE_BOLD);
	_pLabelText->SetTextColor(Color::GetColor(COLOR_ID_BLACK));
	_pLabelText->SetBackgroundColor(Color::GetColor(COLOR_ID_WHITE));
	_pLabelText->SetTextHorizontalAlignment(ALIGNMENT_CENTER);
	AddControl(_pLabelText);

	Rectangle RectValue(Point(GetClientAreaBounds().x + 300, GetClientAreaBounds().y + 300), Dimension(150, 50));
	__pLabel = new Label();
	__pLabel->Construct(RectValue, L"");
	__pLabel->SetTextConfig(44, LABEL_TEXT_STYLE_BOLD);
	__pLabel->SetTextColor(Color::GetColor(COLOR_ID_BLACK));
	__pLabel->SetBackgroundColor(Color::GetColor(COLOR_ID_GREY));
	__pLabel->SetTextHorizontalAlignment(ALIGNMENT_CENTER);
	AddControl(*__pLabel);

	return E_SUCCESS;
}

result
SensorsAppProximityForm::OnTerminating(void)
{
	StopSensor();
	return E_SUCCESS;
}

void
SensorsAppProximityForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	AppAssert(pSceneManager->GoBackward(BackwardSceneTransition(MainScene)) == E_SUCCESS);
}

void
SensorsAppProximityForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
										  const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	AppLog("OnSceneActivatedN activated");
	StartSensor();
}

void
SensorsAppProximityForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
										   const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	AppLog("OnSceneActivatedN deactivated");
	StopSensor();
}

result
SensorsAppProximityForm::OnDraw(void)
{

	Canvas* pCanvas = GetCanvasN();

	if (pCanvas != null)
	{
		pCanvas->Clear();
		pCanvas->Copy(Point(GetClientAreaBounds().x, GetClientAreaBounds().y),*__pCanvas, GetClientAreaBounds());
		delete pCanvas;
	}

	// Do not call Show(). It will be called automatically after OnDraw() callback.
	return E_SUCCESS;
}

void
SensorsAppProximityForm::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{
	__pCanvas->Clear();
	TryReturnVoid(!IsFailed(r), "[%s] Invalid sensor data.", GetErrorMessage(r));

	ProximitySensorData& data = static_cast<ProximitySensorData&>(sensorData);

	String ProximityDist;
	bool ObjDetected =	data.IsObjectDetected();

	if(ObjDetected==true)
	{
		ProximityDist = "True";
	}
	else
	{
		ProximityDist = "False";
	}

	__pLabel->SetText(ProximityDist);

	Invalidate(true);
}

void
SensorsAppProximityForm::StartSensor(void)
{
	long interval = 0L;

	AppLog("Activating ...");

	__sensorMgr.GetMinInterval(SENSOR_TYPE_PROXIMITY, interval);
	if (interval < 50)
	{
		interval = 50;
	}

	__sensorMgr.AddSensorListener(*this, SENSOR_TYPE_PROXIMITY, interval, true);
}

void
SensorsAppProximityForm::StopSensor(void)
{

	AppLog("Deactivating SensorsAppProximityForm...");
	__sensorMgr.RemoveSensorListener(*this);
}




