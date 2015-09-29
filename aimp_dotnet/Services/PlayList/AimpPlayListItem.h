#pragma once

#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"
//#include "PlayListManager.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{

			using namespace System;

			using namespace AIMP36SDK;
			using namespace AIMP::SDK::Services;
			using namespace AIMP::SDK::Services::PlayList;

			public ref class AimpPlayListItem : public AimpObject<AIMP36SDK::IAIMPPlaylistItem>, public IAimpPlayListItem
			{
			private:
				IAimpPlayListGroup^ _group;

			internal:
				AimpPlayListItem(AIMP36SDK::IAIMPPlaylistItem *aimpItem) : AimpObject(aimpItem)
				{
				}
			public:
				AimpPlayListItem();

				~AimpPlayListItem()
				{
					_group = nullptr;
				}

				virtual property System::String^ DisplayText
				{
					System::String^ get();
					void set(System::String^ value);
				}

				virtual property System::String^ FileName
				{
					System::String^ get();
					void set(System::String ^value);
				}

				virtual property int Index
				{
					int get();
					void set(int value);
				}

				virtual property double Mark
				{
					double get();
					void set(double value);
				}

				virtual property int PlaybackIndex
				{
					int get();
				}

				virtual property bool PlaybackSwitch
				{
					bool get();
					void set(bool value);
				}

				virtual property bool Selected
				{
					bool get();
					void set(bool value);
				}

				virtual property IAimpFileInfo^ FileInfo
				{
					IAimpFileInfo^ get();
				}

				virtual property IAimpPlayListGroup^ Group
				{
					IAimpPlayListGroup^ get();
				}

				virtual property IAimpPlayList^ PlayList
				{
					IAimpPlayList^ get();
					void set(IAimpPlayList^ val);
				}

				virtual AimpActionResult ReloadInfo();
			};
		}
	}
}