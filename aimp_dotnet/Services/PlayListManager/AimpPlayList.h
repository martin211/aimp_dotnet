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
			using namespace System::Collections::Generic;

			using namespace AIMP::SDK::Services::PlayListManager;
			

			/// <summary>
			/// 
			/// </summary>
			public ref class AimpPlayList : public AimpObject<AIMP36SDK::IAIMPPlaylist>, public IAimpPlayList
			{
			private:
				AIMP36SDK::IAIMPPropertyList *_properties;

			public:
				explicit AimpPlayList(AIMP36SDK::IAIMPPlaylist *aimpPlayList);
				
				AimpPlayList();				

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

				virtual property bool GrouppingOvveriden
				{
					bool get();
					void set(bool value);
				}

				virtual property bool Groupping
				{
					bool get();
					void set(bool value);
				}

				virtual property String ^GrouppingTemplate
				{
					String ^get();
					void set(String ^value);
				}

				virtual property bool GrouppingAutomerging
				{
					bool get();
					void set(bool value);
				}

				virtual property bool FormatingOverride
				{
					bool get();
					void set(bool value);
				}

				virtual property String ^FirstLineTemplate
				{
					String ^get();
					void set(String ^value);
				}

				virtual property String ^SecondLineTemplate
				{
					String ^get();
					void set(String ^value);
				}

				virtual property bool ViewOverride
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowDuration
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowExpandButtons
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowMarks
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowNumbers
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowAbsoluteNumbers
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowSecondLine
				{
					bool get();
					void set(bool value);
				}

				virtual property bool ShowSwitches
				{
					bool get();
					void set(bool value);
				}

				virtual property int SelectedIndex
				{
					int get();
					void set(int value);
				}

				virtual property int PlaybackCursor
				{
					int get();
					void set(int value);
				}

				virtual property int PlayingIndex
				{
					int get();
					void set(int value);
				}

				virtual property double Duration
				{
					double get();
				}

				virtual property double Size
				{
					double get();
				}

				virtual property String ^PreImage
				{
					String ^get();
					void set(String ^value);
				}

			public:
				virtual void Add(AIMP::SDK::Services::PlayListManager::IAimpFileInfo^ fileInfo, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);

				virtual void Add(System::String^ fileUrl, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);
				
				virtual void AddList(System::Collections::Generic::IList<AIMP::SDK::Services::PlayListManager::IAimpFileInfo^>^ fileUrlList, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);

				virtual void AddList(System::Collections::Generic::IList<System::String^>^ fileUrlList, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);

				virtual void Delete(IAimpPlayListItem ^item);

				virtual void Delete(int index);

				virtual void DeleteAll();

				virtual void Sort(AIMP::SDK::Services::PlayListManager::PlayListSort sort);

				virtual void BeginUpdate();

				virtual void EndUpdate();

				virtual void Close(AIMP::SDK::Services::PlayListManager::PlayListCloseFlag closeFlag);

				virtual System::Collections::Generic::IList<String^>^ GetFiles(PlayListGetFilesFlag filesFlag);

				virtual void ReloadFromPreimage();

				virtual void ReloadInfo(bool fullReload);

				virtual IAimpPlayListItem ^GetItem(int index);

				virtual int GetItemCount();

				virtual IAimpPlayListGroup ^GetGroup(int index);

				virtual int GetGroupCount();

				virtual event EventHandler ^Activated
				{
					void add(EventHandler ^onEvent);
					void remove(EventHandler ^onEvent);
					void raise(Object ^sender, EventArgs ^args);
				}

				virtual event EventHandler ^Removed
				{
					void add(EventHandler ^onEvent);
					void remove(EventHandler ^onEvent);
					void raise(Object ^sender, EventArgs ^args);
				}

				virtual event EventHandler<AimpPlayListChangedArgs^> ^Changed
				{
					void add(EventHandler<AimpPlayListChangedArgs^> ^onEvent);
					void remove(EventHandler<AimpPlayListChangedArgs^> ^onEvent);
					void raise(Object ^sender, AimpPlayListChangedArgs ^args);
				}

			private:
				void GetPropertyList();
			};
		}
	}
}