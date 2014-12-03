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

#include "SensorApp.h"
#include "SensorAppFrame.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


SensorAppApp::SensorAppApp(void)
{
}

SensorAppApp::~SensorAppApp(void)
{
}

UiApp*
SensorAppApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new SensorAppApp();
}

bool
SensorAppApp::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize Frame and App specific data.
	// The App's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the App will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// TODO:
	// Add your initialization code here
	return true;
}

bool
SensorAppApp::OnAppInitialized(void)
{
	// TODO:
	// Add your initialization code here.

	// Create a Frame
	SensorAppFrame* pSensorAppFrame = new SensorAppFrame();
	pSensorAppFrame->Construct();
	pSensorAppFrame->SetName(L"SensorApp");
	AddFrame(*pSensorAppFrame);

	return true;
}

bool
SensorAppApp::OnAppWillTerminate(void)
{
	// TODO:
	// Add your code for actions prior to termination here.
	return true;
}

bool
SensorAppApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this App for termination.
	// The App's permanent data and context can be saved via appRegistry.
	return true;
}

void
SensorAppApp::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
SensorAppApp::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
SensorAppApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
SensorAppApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
SensorAppApp::OnScreenOn(void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
SensorAppApp::OnScreenOff(void)
{
	// TODO:
	// Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device
	// to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a
	// callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
