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
#include "SensorsAppAccelForm.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Uix::Sensor;
using namespace Tizen::Graphics;

static const int ELLIPSE_RADIUS = 25;
static const int ELLIPSE_RADIUS_STEP_VALUE = 15;
static const int RECT_STEP_VALUE = 15;

static const int NegBaseX = 345;
static const int NegBaseY = 400;
static const int PosBaseX = 345;
static const int PosBaseY = 350;

SensorsAppAccelForm::SensorsAppAccelForm(void)
	: __sensorMgr()
{

}

SensorsAppAccelForm::~SensorsAppAccelForm(void)
{

}

bool
SensorsAppAccelForm::Initialize(void)
{
	int ScreenHeight;
	// Set Form properties
	Form::Construct(FORM_STYLE_HEADER|FORM_STYLE_INDICATOR);
	Header* pHeader = this->GetHeader();
	SetName(L"Acceleration");
	pHeader->SetTitleText(L"Acceleration");

	this->SetFormBackEventListener(this);

	Tizen::System::SystemInfo::GetValue("http://tizen.org/feature/screen.height",ScreenHeight);
	__scaleValue = 1;
	if(ScreenHeight == 800)
	{
		__scaleValue = 1.6;
	}
	return true;
}

result
SensorsAppAccelForm::OnInitializing(void)
{
	__sensorMgr.Construct();

	/* Check for the Sensors is supported in the current device or not */
	if (!__sensorMgr.IsAvailable(SENSOR_TYPE_ACCELERATION))
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

	Rectangle RectRange(Point(0, 15), Dimension(250, 50/ __scaleValue));
	_pLabel = CreateLabel(RectRange, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Value Range: -2 ~ +2");
	_pLabel->SetTextConfig(20, LABEL_TEXT_STYLE_BOLD);
	_pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	__pScrollPanel->AddControl(_pLabel);

	Rectangle RectX(Point(125, 80 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(RectX, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_RED));
	__pScrollPanel->AddControl(_pLabel);
	Rectangle RectXV(Point(400, 80 / __scaleValue), Dimension(210, 50 / __scaleValue));
	__pLabelX = CreateLabel(RectXV, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREY));
	__pScrollPanel->AddControl(*__pLabelX);
	Rectangle Rectx(Point(315, 80 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(Rectx, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"X:");
	__pScrollPanel->AddControl(*_pLabel);

	Rectangle RectY(Point(125, 160 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(RectY, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLUE));
	__pScrollPanel->AddControl(*_pLabel);
	Rectangle RectYV(Point(400, 160 / __scaleValue), Dimension(210, 50 / __scaleValue));
	__pLabelY = CreateLabel(RectYV, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREY));
	__pScrollPanel->AddControl(*__pLabelY);
	Rectangle Recty(Point(315, 160 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(Recty, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Y:");
	__pScrollPanel->AddControl(*_pLabel);

	Rectangle RectZ(Point(125, 240 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(RectZ, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREEN));
	__pScrollPanel->AddControl(*_pLabel);
	Rectangle RectZV(Point(400, 240 / __scaleValue), Dimension(210, 50 / __scaleValue));
	__pLabelZ = CreateLabel(RectZV, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_GREY));
	__pScrollPanel->AddControl(*__pLabelZ);
	Rectangle Rectz(Point(315, 240 / __scaleValue), Dimension(75, 50 / __scaleValue));
	_pLabel = CreateLabel(Rectz, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_WHITE));
	_pLabel->SetText(L"Z:");
	__pScrollPanel->AddControl(*_pLabel);

   /* Create all the labels to display the values */
	AddControl(*__pScrollPanel);
	return E_SUCCESS;
}

Tizen::Ui::Controls::Label*
SensorsAppAccelForm::CreateLabel(Rectangle& rect, Color textcolor, Color background)
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
SensorsAppAccelForm::OnTerminating(void)
{
	StopSensor();
	return E_SUCCESS;
}

void
SensorsAppAccelForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	AppAssert(pSceneManager->GoBackward(BackwardSceneTransition(MainScene)) == E_SUCCESS);
}

void
SensorsAppAccelForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
										  const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	AppLog("OnSceneActivatedN activated");
	StartSensor();
}

void
SensorsAppAccelForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
										   const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	AppLog("OnSceneActivatedN deactivated");
	StopSensor();
}

result
SensorsAppAccelForm::OnDraw(void)
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
SensorsAppAccelForm::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{
	float x = 0.0 , y = 0.0, z = 0.0;
	String strX, strY, strZ;
	__pCanvas->Clear();
	TryReturnVoid(!IsFailed(r), "[%s] Invalid sensor data.", GetErrorMessage(r));

	AccelerationSensorData& data = static_cast<AccelerationSensorData&>(sensorData);
	AppLog("AccelerationSensorData    x = %5.4f , y = %5.4f,  z = %5.4f ", data.x,data.y,data.z);

	strX.Append (data.x);
	strX.SetLength(strX.GetLength());
	__pLabelX->SetText(strX + "  ");
	strY.Append (data.y);
	strY.SetLength(strY.GetLength());
	__pLabelY->SetText(strY + "  ");
	strZ.Append (data.z);
	strZ.SetLength(strZ.GetLength());
	__pLabelZ->SetText(strZ + "  ");

	x = data.x * 10;
	y = data.y * 10;
	z = data.z * 10;

	/* Draw x values */
	if(y < 0)
	{
		Rectangle XRect(Point(GetClientAreaBounds().x + PosBaseX + 5, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * abs(y))), Dimension(20, (RECT_STEP_VALUE * abs(y))));
		__pCanvas->FillRectangle(Color::GetColor(COLOR_ID_BLUE), XRect);

		__pCanvas->FillTriangle(Color::GetColor(COLOR_ID_BLUE), Point(GetClientAreaBounds().x + PosBaseX - 10, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * abs(y))),
			Point(GetClientAreaBounds().x + PosBaseX + 15, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * abs(y)) - 20),
			Point(GetClientAreaBounds().x + PosBaseX + 40, GetClientAreaBounds().y + PosBaseY - (RECT_STEP_VALUE * abs(y))));
	}
	else
	{
		Rectangle XRect(Point(GetClientAreaBounds().x + NegBaseX + 5, GetClientAreaBounds().y + NegBaseY), Dimension(20, (RECT_STEP_VALUE * abs(y))));
		__pCanvas->FillRectangle(Color::GetColor(COLOR_ID_BLUE), XRect);

		__pCanvas->FillTriangle(Color::GetColor(COLOR_ID_BLUE), Point(GetClientAreaBounds().x + PosBaseX - 10, GetClientAreaBounds().y + NegBaseY + (RECT_STEP_VALUE * abs(y))),
					Point(GetClientAreaBounds().x + NegBaseX + 15, GetClientAreaBounds().y + NegBaseY + 20 + (RECT_STEP_VALUE * abs(y))),
					Point(GetClientAreaBounds().x + NegBaseX + 40, GetClientAreaBounds().y + NegBaseY + (RECT_STEP_VALUE * abs(y))));
	}
	/* Draw y values */
	if(x < 0)
	{
		Rectangle YRect(Point(GetClientAreaBounds().x + PosBaseX + 40, GetClientAreaBounds().y + 360 + 5), Dimension((RECT_STEP_VALUE * abs(x)), 20));
		__pCanvas->FillRectangle(Color::GetColor(COLOR_ID_RED), YRect);

		__pCanvas->FillTriangle(Color::GetColor(COLOR_ID_RED), Point(GetClientAreaBounds().x + PosBaseX + 40 + (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + NegBaseY - 50),
				Point(GetClientAreaBounds().x + PosBaseX + 40 + (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + NegBaseY),
				Point(GetClientAreaBounds().x + PosBaseX + 60 + (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + NegBaseY - 25));
	}
	else
	{
		Rectangle YRect(Point(GetClientAreaBounds().x + PosBaseX - 10 - (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + 360 + 5), Dimension((RECT_STEP_VALUE * abs(x)), 20));
		__pCanvas->FillRectangle(Color::GetColor(COLOR_ID_RED), YRect);

		__pCanvas->FillTriangle(Color::GetColor(COLOR_ID_RED), Point(GetClientAreaBounds().x + PosBaseX - 10 - (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + NegBaseY - 50),
				Point(GetClientAreaBounds().x + PosBaseX - 10 - (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + NegBaseY),
				Point(GetClientAreaBounds().x + (PosBaseX - 30) - (RECT_STEP_VALUE * abs(x)), GetClientAreaBounds().y + NegBaseY - 25));
	}

	Font font;
	r = font.Construct(FONT_STYLE_BOLD, 44);
	__pCanvas->SetFont(font);
	__pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_BLACK));

	/*Draw Z values */
	if(z >= 0)
	{
		__pCanvas->DrawText(Point(GetClientAreaBounds().x + PosBaseX + 2, GetClientAreaBounds().y + 349), L"+", 2);
	}
	else
	{
		__pCanvas->DrawText(Point(GetClientAreaBounds().x + PosBaseX + 6, GetClientAreaBounds().y + 350), L"-", 2);
	}

	/* Draw the Z value with circle */
	__pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREEN));
	Point point(GetClientAreaBounds().x + PosBaseX + 15, GetClientAreaBounds().y + (NegBaseY - 50) + 25);
	int Raduis = ELLIPSE_RADIUS + (ELLIPSE_RADIUS_STEP_VALUE * abs(z));
	Rectangle rcCircle(Point(point.x - Raduis, point.y - Raduis), Dimension(Raduis * 2, Raduis * 2));
	__pCanvas->SetLineWidth(4);
	__pCanvas->DrawEllipse(rcCircle);

	Invalidate(true);
}

void
SensorsAppAccelForm::StartSensor(void)
{
	long interval = 0L;

	AppLog("Activating ...");

	__sensorMgr.GetMinInterval(SENSOR_TYPE_ACCELERATION, interval);

	if (interval < 50)
	{
		interval = 50;
	}
	__sensorMgr.AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, interval, true);
}

void
SensorsAppAccelForm::StopSensor(void)
{

	AppLog("Deactivating SensorsAppAccelForm...");
	__sensorMgr.RemoveSensorListener(*this);
}




