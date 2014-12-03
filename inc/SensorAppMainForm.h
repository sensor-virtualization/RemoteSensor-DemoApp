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

#ifndef _SENSORAPP_MAIN_FORM_H_
#define _SENSORAPP_MAIN_FORM_H_

#include <FBase.h>
#include <FUi.h>


class SensorAppMainForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
 	, public Tizen::Ui::Scenes::ISceneEventListener
	, public Tizen::Ui::Controls::IListViewItemEventListener
	, public Tizen::Ui::Controls::IListViewItemProvider
	, public Tizen::Ui::Controls::IFastScrollListener
{
public:
	SensorAppMainForm(void);
	virtual ~SensorAppMainForm(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);
// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction);

	//IListViewItemProvider
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);
	virtual int GetItemCount(void);

	//IFastScrollListener
	virtual void OnFastScrollIndexSelected(Tizen::Ui::Control& source, Tizen::Base::String& index);
	static const int LABEL_HEIGHT = 112;

	protected:
		Tizen::Ui::Controls::ListView* _pList;
};

#endif	//_SENSORAPP_MAIN_FORM_H_
