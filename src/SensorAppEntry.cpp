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

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


//
// The entry function of Tizen application called by the operating system.
//
_EXPORT_ int
OspMain(int argc, char* pArgv[])
{
	AppLog("Application started.");
	ArrayList args(SingleObjectDeleter);
	args.Construct();
	for (int i = 0; i < argc; i++)
	{
		args.Add(new (std::nothrow) String(pArgv[i]));
	}

	result r = Tizen::App::UiApp::Execute(SensorAppApp::CreateInstance, &args);
	TryLog(r == E_SUCCESS, "[%s] Application execution failed", GetErrorMessage(r));
	AppLog("Application finished.");

	return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
