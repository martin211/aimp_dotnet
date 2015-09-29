#pragma once

#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"


namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			using namespace AIMP36SDK;
			using namespace AIMP::SDK::Services::PlayList;

			public ref class AimpPlayListGroup : public AimpObject<AIMP36SDK::IAIMPPlaylistGroup>, public IAimpPlayListGroup
			{
			private:
				IAimpPlayListItem ^_item;

			public:
				~AimpPlayListGroup()
				{
					_item = nullptr;
				}
				AimpPlayListGroup();

				explicit AimpPlayListGroup(AIMP36SDK::IAIMPPlaylistGroup *item);

				virtual property System::String^ Name
				{
					System::String^ get();
				}

				virtual property bool Expanded
				{
					bool get();
					void set(bool value);
				}

				virtual property double Duration
				{
					double get();
					void set(double value);
				}

				virtual property int Index
				{
					int get();
				}

				virtual property bool Selected
				{
					bool get();
					void set(bool value);
				}

				virtual property int Count
				{
					int get();
				}

				virtual IAimpPlayListItem ^GetItem(int index);
			};
		}
	}
}