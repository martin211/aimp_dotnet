#pragma once
#include "..\..\AIMP_SDK\aimp3_60_sdk.h"
#include "..\..\ObjectHelper.h"

namespace AIMP
{
	typedef boost::signals::connection ConnectionCallback;
	typedef boost::signal<void(void)> VoidSignal;
	typedef boost::signal<void(int)> IntSignal;
	typedef boost::signal<void(void)>::slot_function_type VoidSignalCB;
	typedef boost::signal<void(int)>::slot_function_type DwordSignalCB;

	namespace SDK
	{
		namespace PlayList
		{
			using namespace System;
			using namespace System::Collections::Generic;

			using namespace AIMP::SDK::Services;
			using namespace AIMP::SDK::Services::PlayListManager;
			
			class AimpPlaylistListener : public IUnknownInterfaceImpl<AIMP36SDK::IAIMPPlaylistListener>
			{
			private:
				IntSignal _changed;
				VoidSignal _activated;
				VoidSignal _removed;

			public:
				ConnectionCallback RegisterActivatedCallback(VoidSignalCB subscriber)
				{
					return _activated.connect(subscriber);
				}

				ConnectionCallback RegisterRemovedCallback(VoidSignalCB subscriber)
				{
					return _removed.connect(subscriber);
				}

				ConnectionCallback RegisterChangedCallback(DwordSignalCB subscriber)
				{
					return _changed.connect(subscriber);
				}

				void UregisterActivatedCallback(ConnectionCallback *activatedCallback)
				{
					_activated.disconnect(activatedCallback);
				}

				void UnregisterRemoveCallback(ConnectionCallback *removedCallback)
				{
					_removed.disconnect(removedCallback);					
				}

				void UnregisterChangedCallback(ConnectionCallback *changedCallback)
				{
					_changed.disconnect(changedCallback);					
				}

				virtual void WINAPI Activated()
				{
					_activated();
				}

				virtual void WINAPI Changed(DWORD flags)
				{
					_changed(flags);
				}

				virtual void WINAPI Removed()
				{
					_removed();
				}

				virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
				{
					if (riid == AIMP36SDK::IID_IAIMPPlaylistListener)
					{
						*ppvObject = this;
						return S_OK;
					}

					ppvObject = NULL;
					return E_NOTIMPL;
				}
			};

			/// <summary>
			/// 
			/// </summary>
			public ref class AimpPlayList : public AimpObject<AIMP36SDK::IAIMPPlaylist>, public IAimpPlayList
			{
			private:
				AIMP36SDK::IAIMPPropertyList *_properties;
				Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ _compareFunc;
				PlayListChangedHandler ^_onChanged;
				AIMP::Services::PlayListManager::PlayListHandler ^_onActivated;
				AIMP::Services::PlayListManager::PlayListHandler ^_onRemoved;

				AimpPlaylistListener *_listner;
				ConnectionCallback *_activatedCallback;
				ConnectionCallback *_removedCallBack;
				ConnectionCallback *_changedCallBack;

			public:
				explicit AimpPlayList(AIMP36SDK::IAIMPPlaylist *aimpPlayList);
				
				AimpPlayList();

				~AimpPlayList();

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
				virtual ActionResult Add(AIMP::SDK::Services::PlayListManager::IAimpFileInfo^ fileInfo, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);

				virtual ActionResult Add(System::String^ fileUrl, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);
				
				virtual ActionResult AddList(System::Collections::Generic::IList<AIMP::SDK::Services::PlayListManager::IAimpFileInfo^>^ fileUrlList, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);

				virtual ActionResult AddList(System::Collections::Generic::IList<System::String^>^ fileUrlList, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition);

				virtual ActionResult Delete(IAimpPlayListItem ^item);

				virtual ActionResult Delete(int index);

				virtual ActionResult DeleteAll();

				virtual ActionResult Sort(AIMP::SDK::Services::PlayListManager::PlayListSort sort);

				virtual ActionResult Sort(System::Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ compareFunc);

				virtual ActionResult BeginUpdate();

				virtual ActionResult EndUpdate();

				virtual ActionResult Close(AIMP::SDK::Services::PlayListManager::PlayListCloseFlag closeFlag);

				virtual System::Collections::Generic::IList<String^>^ GetFiles(PlayListGetFilesFlag filesFlag);

				virtual ActionResult ReloadFromPreimage();

				virtual ActionResult ReloadInfo(bool fullReload);

				virtual IAimpPlayListItem ^GetItem(int index);

				virtual int GetItemCount();

				virtual IAimpPlayListGroup ^GetGroup(int index);

				virtual int GetGroupCount();

				virtual event AIMP::Services::PlayListManager::PlayListHandler ^Activated
				{
					void add(AIMP::Services::PlayListManager::PlayListHandler ^onEvent);
					void remove(AIMP::Services::PlayListManager::PlayListHandler ^onEvent);
					void raise(IAimpPlayList ^sender);
				}

				virtual event AIMP::Services::PlayListManager::PlayListHandler ^Removed
				{
					void add(AIMP::Services::PlayListManager::PlayListHandler ^onEvent);
					void remove(AIMP::Services::PlayListManager::PlayListHandler ^onEvent);
					void raise(IAimpPlayList ^sender);
				}

				virtual event PlayListChangedHandler ^Changed
				{
					void add(PlayListChangedHandler ^onEvent);
					void remove(PlayListChangedHandler ^onEvent);
					void raise(IAimpPlayList ^esnder, PlayListNotifyType notifyType);
				}

			private:
				void GetPropertyList();				
				void RegisterListner();

				delegate int OnSortCallback(AIMP36SDK::IAIMPPlaylistItem* item1, AIMP36SDK::IAIMPPlaylistItem* item2, void* userData);
				OnSortCallback^ _sortCallback;

				// TODO: Move it to the cpp file
				int OnSortReceive(AIMP36SDK::IAIMPPlaylistItem* item1, AIMP36SDK::IAIMPPlaylistItem* item2, void* userData)
				{
					System::Diagnostics::Debugger::Break();
					PWCHAR sp = (PWCHAR)userData;
					//delete sp;
					return (int)_compareFunc(gcnew AimpPlayListItem(item1), gcnew AimpPlayListItem(item2));
				}
			};
		}
	}
}