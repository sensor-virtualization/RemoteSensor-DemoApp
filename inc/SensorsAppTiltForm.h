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

#ifndef SENSORSAPPTILTForm_H_
#define SENSORSAPPTILTForm_H_


#include <FBase.h>
#include <FUi.h>
#include <FMedia.h>
#include <FUix.h>

class SensorsAppTiltForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::Controls::IFormBackEventListener
 	, public Tizen::Ui::Scenes::ISceneEventListener
 	, public Tizen::Uix::Sensor::ISensorEventListener
{
public:
		SensorsAppTiltForm(void);
	virtual ~SensorsAppTiltForm(void);

	bool Initialize(void);
	bool RegisterSensor(void);
	bool UnRegisterSensor(void);
	void StartSensor(void);
	void StopSensor(void);


	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	virtual result OnDraw(void);
	virtual void OnDataReceived(Tizen::Uix::Sensor::SensorType sensorType, Tizen::Uix::Sensor::SensorData& sensorData, result r);
	Tizen::Ui::Controls::Label*	CreateLabel(Tizen::Graphics::Rectangle& rect, Tizen::Graphics::Color textcolor, Tizen::Graphics::Color background);
private:

private:
	Tizen::Uix::Sensor::SensorManager __sensorMgr;
	Tizen::Graphics::Canvas			  *__pCanvas;
	Tizen::Ui::Controls::Label* __pLabelX;
	Tizen::Ui::Controls::Label* __pLabelY;
	Tizen::Ui::Controls::Label* __pLabelZ;
	Tizen::Ui::Controls::ScrollPanel* __pScrollPanel;
	float __scaleValue;
};



#endif /* SENSORSAPPGRAVITYForm_H_ */
