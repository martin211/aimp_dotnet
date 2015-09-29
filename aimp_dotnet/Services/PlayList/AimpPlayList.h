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
			using namespace AIMP::SDK::Services::PlayList;
			
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
				AimpPlayListHandler ^_onActivated;
				AimpPlayListHandler ^_onRemoved;

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
				virtual AimpActionResult Add(IAimpFileInfo^ fileInfo, PlayListFlags flags, PlayListFilePosition filePosition);

				virtual AimpActionResult Add(System::String^ fileUrl, PlayListFlags flags, PlayListFilePosition filePosition);
				
				virtual AimpActionResult AddList(System::Collections::Generic::IList<IAimpFileInfo^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

				virtual AimpActionResult AddList(System::Collections::Generic::IList<System::String^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

				virtual AimpActionResult Delete(IAimpPlayListItem ^item);

				virtual AimpActionResult Delete(int index);

				virtual AimpActionResult DeleteAll();

				virtual AimpActionResult Sort(PlayListSort sort);

				virtual AimpActionResult Sort(System::Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ compareFunc);

				virtual AimpActionResult BeginUpdate();

				virtual AimpActionResult EndUpdate();

				virtual AimpActionResult Close(PlayListCloseFlag closeFlag);

				virtual System::Collections::Generic::IList<String^>^ GetFiles(PlayListGetFilesFlag filesFlag);

				virtual AimpActionResult ReloadFromPreimage();

				virtual AimpActionResult ReloadInfo(bool fullReload);

				virtual IAimpPlayListItem ^GetItem(int index);

				virtual int GetItemCount();

				virtual IAimpPlayListGroup ^GetGroup(int index);

				virtual int GetGroupCount();

				virtual event AimpPlayListHandler ^Activated
				{
					void add(AimpPlayListHandler ^onEvent);
					void remove(AimpPlayListHandler ^onEvent);
					void raise(IAimpPlayList ^sender);
				}

				virtual event AimpPlayListHandler ^Removed
				{
					void add(AimpPlayListHandler ^onEvent);
					void remove(AimpPlayListHandler ^onEvent);
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