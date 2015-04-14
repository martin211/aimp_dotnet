#pragma once

#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			using namespace System;
			using namespace AIMP36SDK;
			using namespace AIMP::SDK::Services::PlayListManager;


			public ref class PlayList : public AimpObject<AIMP36SDK::IAIMPPlaylist>, public IAimpPlayList
			{ 
			public: 
				virtual property String ^Id
				{
					String ^get();
				}

				virtual property String ^Name
				{
					String ^get();
					void set(String ^value);
				}

				virtual property bool ReadOnly
				{
					bool get();
					void set(bool value);
				}

				virtual property Object ^FocusedObject
				{
					Object ^get();
					void set(Object ^value);
				}
			};
		}
	}
}