#pragma once

#include "..\..\AIMP_SDK\AimpSDK.h"
#include "..\..\ObjectHelper.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{

			using namespace System;

			using namespace AIMPSDK;
			using namespace AIMP::SDK::Services;
			using namespace AIMP::SDK::Services::PlayList;

			public ref class AimpPlayListItem : public AimpObject<IAIMPPlaylistItem>, public IAimpPlayListItem
			{
			private:
				IAimpPlayListGroup^ _group;

			internal:
				AimpPlayListItem(IAIMPPlaylistItem *aimpItem) : AimpObject(aimpItem)
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