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
#include "SensorsAppOrientationForm.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Uix::Sensor;
using namespace Tizen::Graphics;

static const int ELLIPSE_RADIUS = 25;
static const int ELLIPSE_RADIUS_STEP_VALUE = 30;
static const int RECT_STEP_VALUE = 30;

static const int PosBaseX = 250;
static const int PosBaseY = 400;


SensorsAppOrientationForm::SensorsAppOrientationForm(void)
	: __sensorMgr()
{

}

SensorsAppOrientationForm::~SensorsAppOrientationForm(void)
{

}

bool
SensorsAppOrientationForm::Initialize(void)
{
	int ScreenHeight;

	// Set Form properties
	Form::Construct(FORM_STYLE_HEADER|FORM_STYLE_INDICATOR);
	Header* pHeader = this->GetHeader();
	SetName(L"DeviceOrientation");
	pHeader->SetTitleText(L"Device Orientation");

	Tizen::System::SystemInfo::GetValue("http://tizen.org/feature/screen.height",ScreenHeight);
	__scaleValue = 1;
	if(ScreenHeight == 800)
	{
		__scaleValue = 1.6;
	}
	this->SetFormBackEventListener(this);

	return true;
}

result
SensorsAppOrientationForm::OnInitializing(void)
{
	__sensorMgr.Construct();

	/* Check for the Sensors is supported in the current device or not */
	if (!__sensorMgr.IsAvailable(SENSOR_TYPE_DEVICE_ORIENTATION))
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

	/* Creates an instance of ScrollPanel */
	__pScrollPanel = new ScrollPanel();
	__pScrollPanel->Construct(Rectangle(GetClientAreaBounds().x + 10, GetClientAreaBounds().y + 530, 800, 350 / __scaleValue));

	/* Create all the labels to display the values */
	Tizen::Ui::Controls::Label* _pLabel;

	Rectangle RectRange(Point(0,  0), Dimension(300, 50/ __scaleValue));
	_pLabel = CreateLabel(RectRange, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Value Range: -360 ~ +360");
	_pLabel->SetTextConfig(20, LABEL_TEXT_STYLE_BOLD);
	_pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	__pScrollPanel->AddControl(_pLabel);

	Rectangle RectX(Point(100, 80 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(RectX, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_RED));
	__pScrollPanel->AddControl(_pLabel);
	Rectangle RectXV(Point(425, 80 / __scaleValue), Dimension(210, 50 / __scaleValue));
	__pLabelX = CreateLabel(RectXV, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREY));
	__pScrollPanel->AddControl(__pLabelX);
	Rectangle Rectx(Point(250, 80 / __scaleValue), Dimension(175, 50 / __scaleValue));
	_pLabel = CreateLabel(Rectx, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Pitch:");
	__pScrollPanel->AddControl(_pLabel);

	Rectangle RectY(Point(100, 160 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(RectY, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLUE));
	__pScrollPanel->AddControl(_pLabel);
	Rectangle RectYV(Point(425, 160 / __scaleValue), Dimension(210, 50 / __scaleValue));
	__pLabelY = CreateLabel(RectYV, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREY));
	__pScrollPanel->AddControl(__pLabelY);
	Rectangle Recty(Point(250, 160 / __scaleValue), Dimension(175, 50 / __scaleValue));
	_pLabel = CreateLabel(Recty, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Roll:");
	__pScrollPanel->AddControl(_pLabel);

	Rectangle RectZ(Point(100, 240 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(RectZ, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREEN));
	__pScrollPanel->AddControl(_pLabel);
	Rectangle RectZV(Point(425, 240 / __scaleValue), Dimension(210, 50 / __scaleValue));
	__pLabelZ = CreateLabel(RectZV, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREY));
	__pScrollPanel->AddControl(__pLabelZ);
	Rectangle Rectz(Point(250, 240 / __scaleValue), Dimension(175, 50 / __scaleValue));
	_pLabel = CreateLabel(Rectz, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Yaw:");
	__pScrollPanel->AddControl(_pLabel);
	/* Create all the labels to display the values */

	AddControl(__pScrollPanel);
	return E_SUCCESS;
}

Tizen::Ui::Controls::Label*
SensorsAppOrientationForm::CreateLabel(Rectangle& rect, Color textcolor, Color background)
{
	Tizen::Ui::Controls::Label* _pLabel;

	_pLabel = new Label();
	_pLabel->Construct(rect, L"");
	_pLabel->SetTextConfig(44 / __scaleValue, LABEL_TEXT_STYLE_BOLD);
	_pLabel->SetTextColor(textcolor);
	_pLabel->SetBackgroundColor(background);
	_pLabel->SetTextHorizontalAlignment(ALIGNMENT_RIGHT);
	//AddControl(*_pLabel);
	return _pLabel;
}
result
SensorsAppOrientationForm::OnTerminating(void)
{
	StopSensor();
	return E_SUCCESS;
}

void
SensorsAppOrientationForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	AppAssert(pSceneManager->GoBackward(BackwardSceneTransition(MainScene)) == E_SUCCESS);
}

void
SensorsAppOrientationForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
										  const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	AppLog("OnSceneActivatedN activated");
	StartSensor();
}

void
SensorsAppOrientationForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
										   const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	AppLog("OnSceneActivatedN deactivated");
	StopSensor();
}

result
SensorsAppOrientationForm::OnDraw(void)
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
SensorsAppOrientationForm::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{
	String strX, strY, strZ;

	__pCanvas->Clear();

	TryReturnVoid(!IsFailed(r), "[%s] Invalid sensor data.", GetErrorMessage(r));

	DeviceOrientationSensorData& data = static_cast<DeviceOrientationSensorData&>(sensorData);
	AppLog("DeviceOrientationSensorData   x = %5.4f , y = %5.4f,  z = %5.4f ", data.yaw,data.roll,data.pitch);

	strX.Append (data.pitch);
	strX.SetLength(strX.GetLength());
	__pLabelX->SetText(strX + "  ");
	strY.Append (data.roll);
	strY.SetLength(strY.GetLength());
	__pLabelY->SetText(strY + "  ");
	strZ.Append (data.yaw);
	strZ.SetLength(strZ.GetLength());
	__pLabelZ->SetText(strZ + "  ");

	Rectangle XRect(Point(GetClientAreaBounds().x + PosBaseX + 5, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * 7)), Dimension(20, (RECT_STEP_VALUE * 7)));
	__pCanvas->FillRectangle(Color::GetColor(COLOR_ID_BLUE), XRect);
	__pCanvas->FillTriangle(Color::GetColor(COLOR_ID_BLUE), Point(GetClientAreaBounds().x + PosBaseX - 10, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * 7)),
			Point(GetClientAreaBounds().x + PosBaseX + 15, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * 7) - 20),
			Point(GetClientAreaBounds().x + PosBaseX + 40, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * 7)));

	__pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREY));
	Rectangle RectArc(Point(GetClientAreaBounds().x + PosBaseX - 30, GetClientAreaBounds().y + 15), Dimension(125, 125));
	if(data.roll > 0)
	__pCanvas->DrawArc(RectArc, 0, data.roll, ARC_STYLE_FILLED_PIE);
	else
	__pCanvas->DrawArc(RectArc, data.roll, 0, ARC_STYLE_FILLED_PIE);


	Rectangle YRect(Point(GetClientAreaBounds().x + PosBaseX + 40, GetClientAreaBounds().y + PosBaseY), Dimension((RECT_STEP_VALUE * 7), 20));
	__pCanvas->FillRectangle(Color::GetColor(COLOR_ID_RED), YRect);
	__pCanvas->FillTriangle(Color::GetColor(COLOR_ID_RED), Point(GetClientAreaBounds().x + PosBaseX + 40 + (RECT_STEP_VALUE * 7), GetClientAreaBounds().y + 35 + PosBaseY - 50),
			Point(GetClientAreaBounds().x + PosBaseX + 40 + (RECT_STEP_VALUE * 7), GetClientAreaBounds().y + PosBaseY + 35),
			Point(GetClientAreaBounds().x + PosBaseX + 60 + (RECT_STEP_VALUE * 7), GetClientAreaBounds().y + 35 + PosBaseY - 25));

	__pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREY));
	Rectangle RectPitch(Point( (GetClientAreaBounds().x + PosBaseX + (RECT_STEP_VALUE * 9) + 10), GetClientAreaBounds().y + 350 ), Dimension(125, 125));
	if(data.pitch > 0)
	__pCanvas->DrawArc(RectPitch, 0, data.pitch, ARC_STYLE_FILLED_PIE);
	else
	__pCanvas->DrawArc(RectPitch, data.pitch, 0, ARC_STYLE_FILLED_PIE);

	/* Draw the Z value with circle */
	__pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREEN));
	Point point(GetClientAreaBounds().x + PosBaseX + 20, GetClientAreaBounds().y + PosBaseY + 03);
	int Raduis = ELLIPSE_RADIUS + (ELLIPSE_RADIUS_STEP_VALUE * abs(2));
	Rectangle rcCircle(Point(point.x - Raduis, point.y - Raduis), Dimension(Raduis * 2, Raduis * 2));
	__pCanvas->SetLineWidth(4);
	__pCanvas->DrawEllipse(rcCircle);

	__pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREY));
	Rectangle RectRoll( Point( (GetClientAreaBounds().x + PosBaseX - 180), GetClientAreaBounds().y + 450 + 15), Dimension(125, 125) );
	if(data.yaw > 0)
	__pCanvas->DrawArc(RectRoll, 0, data.yaw, ARC_STYLE_FILLED_PIE);
	else
	__pCanvas->DrawArc(RectRoll, data.yaw, 0, ARC_STYLE_FILLED_PIE);


	Invalidate(true);
}

void
SensorsAppOrientationForm::StartSensor(void)
{
	long interval = 0L;

	AppLog("Activating ...");

	__sensorMgr.GetMinInterval(SENSOR_TYPE_DEVICE_ORIENTATION, interval);
	if (interval < 50)
	{
		interval = 50;
	}

	__sensorMgr.AddSensorListener(*this, SENSOR_TYPE_DEVICE_ORIENTATION, interval, true);
}

void
SensorsAppOrientationForm::StopSensor(void)
{

	AppLog("Deactivating SensorsAppOrientationForm...");
	__sensorMgr.RemoveSensorListener(*this);
}




