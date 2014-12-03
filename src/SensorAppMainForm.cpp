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

#include <FApp.h>
#include "SensorAppMainForm.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


static const char *SensorStrings[10] = {"Acceleration", "Ambient Light", "Device Orientation", "Gravity", "Gyro", "RemoteGyro", "Magnetic", "Proximity", "Tilt",
					 "User Acceleration" };

static const char *SensorScene[10] ={"AccelSensorScene", "LightSensorScene", "DeviceOrientationScene", "GravityScene", "GryroScene", "RemoteGyroSensorScene", "MagneticSensorScene", "ProximitySensorScene", "TiltSensorScene",
			  "UserAccelScene" };


SensorAppMainForm::SensorAppMainForm(void)
{
}

SensorAppMainForm::~SensorAppMainForm(void)
{
}

bool
SensorAppMainForm::Initialize(void)
{

	Construct(IDF_FORM);

	return true;

}

result
SensorAppMainForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your initialization code here

	// Sets the Form back event listener.
	SetFormBackEventListener(this);

	_pList = static_cast< ListView* >(GetControl(IDC_LISTVIEW1));
	_pList->SetItemProvider(*this);
	_pList->AddFastScrollListener(*this);
	_pList->AddListViewItemEventListener(*this);
	_pList->SetTextOfEmptyList(L"");
	AddControl(_pList);

	return r;
}

result
SensorAppMainForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your termination code here
	return r;
}

void
SensorAppMainForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	return;
}

void
SensorAppMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

void
SensorAppMainForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
										  const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO:
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");
}

void
SensorAppMainForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
										   const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}

void
SensorAppMainForm::OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	SceneId SceneValue (SensorScene[index]);
	AppLog("Sensorscene values is %s", SensorScene[index]);

	AppAssert(pSceneManager->GoForward(ForwardSceneTransition(SceneValue)) == E_SUCCESS);

}

void
SensorAppMainForm::OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction)
{

}

void
SensorAppMainForm::OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state)
{

}

int
SensorAppMainForm::GetItemCount(void)
{
	return 9;
}

Tizen::Ui::Controls::ListItemBase*
SensorAppMainForm::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	SimpleItem* pItem = new (std::nothrow) SimpleItem();

	pItem->Construct(Tizen::Graphics::Dimension(itemWidth, LABEL_HEIGHT), style);

	Tizen::Base::String* key = new (String)(SensorStrings[index]);
	AppLog("CreateItem values is %s", SensorScene[index]);
	pItem->SetElement(*key, null);
	return pItem;
}

bool
SensorAppMainForm::DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}


void
SensorAppMainForm::OnFastScrollIndexSelected(Tizen::Ui::Control& source, Tizen::Base::String& index)
{

}

