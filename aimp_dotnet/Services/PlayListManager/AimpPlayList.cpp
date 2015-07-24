﻿#include "Stdafx.h"
#include "AimpPlayList.h"
#include "AimpPlayListGroup.h"
#include "AimpFileInfo.h"
#include "..\..\ManagedAimpCore.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
			AimpPlayList::AimpPlayList(AIMP36SDK::IAIMPPlaylist *aimpPlayList) : AimpObject(aimpPlayList)
			{
				GetPropertyList();
			}

			AimpPlayList::AimpPlayList()
			{
				AIMP36SDK::IAIMPPlaylist *playList = (AIMP36SDK::IAIMPPlaylist*)AIMP::SDK360::ManagedAimpCore::QueryInterface(AIMP36SDK::IID_IAIMPPlaylist);
				GetPropertyList();
			}

			AimpPlayList::~AimpPlayList()
			{
				InternalAimpObject->ListenerRemove(_listner);
				_listner->Release();
				delete _listner;
			}

			String ^AimpPlayList::Id::get()
			{				
				return ObjectHelper::GetString(_properties, AIMP_PLAYLIST_PROPID_ID);
			}

			String ^AimpPlayList::Name::get()
			{
				return ObjectHelper::GetString(_properties, AIMP_PLAYLIST_PROPID_NAME);
			}

			void AimpPlayList::Name::set(String ^value)
			{
				ObjectHelper::SetString(_properties, AIMP_PLAYLIST_PROPID_NAME, value);
			}

			bool AimpPlayList::ReadOnly::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_READONLY);
			}

			void AimpPlayList::ReadOnly::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_READONLY, value);
			}

			Object ^AimpPlayList::FocusedObject::get()
			{
				return nullptr;
			}

			void AimpPlayList::FocusedObject::set(Object ^value)
			{}


			bool AimpPlayList::GrouppingOvveriden::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN);
			}

			void AimpPlayList::GrouppingOvveriden::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN, value);
			}


			bool AimpPlayList::Groupping::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_GROUPPING);
			}

			void AimpPlayList::Groupping::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_GROUPPING, value);
			}


			String ^AimpPlayList::GrouppingTemplate::get()
			{
				return ObjectHelper::GetString(_properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE);
			}

			void AimpPlayList::GrouppingTemplate::set(String ^value)
			{
				ObjectHelper::SetString(_properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE, value);
			}


			bool AimpPlayList::GrouppingAutomerging::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING);
			}

			void AimpPlayList::GrouppingAutomerging::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING, value);
			}


			bool AimpPlayList::FormatingOverride::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN);
			}

			void AimpPlayList::FormatingOverride::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN, value);
			}


			String ^AimpPlayList::FirstLineTemplate::get()
			{
				return ObjectHelper::GetString(_properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE);
			}

			void AimpPlayList::FirstLineTemplate::set(String ^value)
			{
				ObjectHelper::SetString(_properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE, value);
			}


			String ^AimpPlayList::SecondLineTemplate::get()
			{
				return ObjectHelper::GetString(_properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE);
			}

			void AimpPlayList::SecondLineTemplate::set(String ^value)
			{
				ObjectHelper::SetString(_properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE, value);
			}


			bool AimpPlayList::ViewOverride::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN);
			}

			void AimpPlayList::ViewOverride::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN, value);
			}


			bool AimpPlayList::ShowDuration::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION);
			}

			void AimpPlayList::ShowDuration::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION, value);
			}


			bool AimpPlayList::ShowExpandButtons::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS);
			}

			void AimpPlayList::ShowExpandButtons::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS, value);
			}


			bool AimpPlayList::ShowMarks::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS);
			}

			void AimpPlayList::ShowMarks::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS, value);
			}


			bool AimpPlayList::ShowNumbers::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS);
			}

			void AimpPlayList::ShowNumbers::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS, value);
			}


			bool AimpPlayList::ShowAbsoluteNumbers::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE);
			}

			void AimpPlayList::ShowAbsoluteNumbers::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE, value);
			}


			bool AimpPlayList::ShowSecondLine::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE);
			}

			void AimpPlayList::ShowSecondLine::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE, value);
			}


			bool AimpPlayList::ShowSwitches::get()
			{
				return ObjectHelper::GetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES);
			}

			void AimpPlayList::ShowSwitches::set(bool value)
			{
				ObjectHelper::SetBool(_properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES, value);
			}


			int AimpPlayList::SelectedIndex::get()
			{
				return ObjectHelper::GetInt32(_properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX);
			}

			void AimpPlayList::SelectedIndex::set(int value)
			{
				ObjectHelper::SetInt32(_properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX, value);
			}


			int AimpPlayList::PlaybackCursor::get()
			{
				return ObjectHelper::GetInt32(_properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR);
			}

			void AimpPlayList::PlaybackCursor::set(int value)
			{
				ObjectHelper::SetInt32(_properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR, value);
			}


			int AimpPlayList::PlayingIndex::get()
			{
				return ObjectHelper::GetInt32(_properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX);
			}

			void AimpPlayList::PlayingIndex::set(int value)
			{
				ObjectHelper::SetInt32(_properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX, value);
			}


			double AimpPlayList::Duration::get()
			{
				return ObjectHelper::GetFloat(_properties, AIMP_PLAYLIST_PROPID_DURATION);
			}


			double AimpPlayList::Size::get()
			{
				return ObjectHelper::GetFloat(_properties, AIMP_PLAYLIST_PROPID_SIZE);
			}


			String ^AimpPlayList::PreImage::get()
			{
				return ObjectHelper::GetString(_properties, AIMP_PLAYLIST_PROPID_PREIMAGE);
			}

			void AimpPlayList::PreImage::set(String ^value)
			{
				ObjectHelper::SetString(_properties, AIMP_PLAYLIST_PROPID_PREIMAGE, value);
			}


			void AimpPlayList::Add(AIMP::SDK::Services::PlayListManager::IAimpFileInfo^ fileInfo, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition)
			{
				if (InternalAimpObject->Add(((AimpFileInfo^)fileInfo)->InternalAimpObject, (DWORD)flags, (int)filePosition) != S_OK)
				{
					throw gcnew ApplicationException("Unable to add new file to play list");
				}
			}

			void AimpPlayList::Add(String^ fileUrl, PlayListFlags flags, PlayListFilePosition filePosition)
			{
				AIMP36SDK::IAIMPString *url = ObjectHelper::MakeAimpString(AIMP::SDK360::ManagedAimpCore::GetAimpCore(), fileUrl);
				CheckResult(InternalAimpObject->Add(url, (DWORD)flags, (int)filePosition));
			}

			void AimpPlayList::AddList(System::Collections::Generic::IList<IAimpFileInfo^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition)
			{
				if (fileUrlList->Count > 0)
				{
					AIMP36SDK::IAIMPObjectList *list;
					AIMP::SDK360::ManagedAimpCore::GetAimpCore()->CreateObject(AIMP36SDK::IID_IAIMPObjectList, (void**)&list);
					for each (AimpFileInfo ^file in fileUrlList)
					{
						list->Add(file->InternalAimpObject);
					}

					CheckResult(InternalAimpObject->AddList(list, (DWORD) flags, (int) filePosition));
				}
			}

			void AimpPlayList::AddList(IList<String^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition)
			{
				if (fileUrlList->Count > 0)
				{
					AIMP36SDK::IAIMPObjectList *list;
					AIMP::SDK360::ManagedAimpCore::GetAimpCore()->CreateObject(AIMP36SDK::IID_IAIMPObjectList, (void**) &list);
					for each (String ^file in fileUrlList)
					{						
						list->Add(ObjectHelper::MakeAimpString(AIMP::SDK360::ManagedAimpCore::GetAimpCore(), file));
					}

					CheckResult(InternalAimpObject->AddList(list, (DWORD) flags, (int) filePosition));
				}
			}

			void AimpPlayList::Delete(IAimpPlayListItem ^item)
			{
				CheckResult(InternalAimpObject->Delete(((AimpPlayListItem^)item)->InternalAimpObject));
			}

			void AimpPlayList::Delete(int index)
			{
				CheckResult(InternalAimpObject->Delete2(index));
			}

			void AimpPlayList::DeleteAll()
			{
				CheckResult(InternalAimpObject->DeleteAll());				
			}

			void AimpPlayList::Sort(AIMP::SDK::Services::PlayListManager::PlayListSort sort)
			{
				CheckResult(InternalAimpObject->Sort((int)sort));
			}

			void AimpPlayList::Sort(Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ compareFunc)
			{
				_compareFunc = compareFunc;
				_sortCallback = gcnew OnSortCallback(this, &AIMP::SDK::PlayList::AimpPlayList::OnSortReceive);
				IntPtr functionHandle = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_sortCallback);
				InternalAimpObject->Sort3((AIMP36SDK::TAIMPPlaylistCompareProc(_stdcall*))functionHandle.ToPointer(), NULL);
			}

			void AimpPlayList::BeginUpdate()
			{
				InternalAimpObject->BeginUpdate();
			}

			void AimpPlayList::EndUpdate()
			{
				InternalAimpObject->EndUpdate();
			}

			void AimpPlayList::Close(AIMP::SDK::Services::PlayListManager::PlayListCloseFlag closeFlag)
			{
				InternalAimpObject->Close((DWORD)closeFlag);
			}

			System::Collections::Generic::IList<String^> ^AimpPlayList::GetFiles(PlayListGetFilesFlag filesFlag)
			{
				AIMP36SDK::IAIMPObjectList *collection;
				InternalAimpObject->GetFiles((DWORD)filesFlag, &collection);
				
				System::Collections::Generic::IList<String^> ^result = gcnew System::Collections::Generic::List<String^>();

				for (int i = 0; i < collection->GetCount(); i++)
				{
					IAIMPString *str;
					if (collection->GetObject(i, IID_IAIMPString, (void**)&str) == S_OK)
					{
						result->Add(ObjectHelper::GetString(str));
						str->Release();
					}					
				}

				return result;
			}

			void AimpPlayList::ReloadFromPreimage()
			{
				InternalAimpObject->ReloadFromPreimage();				
			}

			void AimpPlayList::ReloadInfo(bool fullReload)
			{
				InternalAimpObject->ReloadInfo(fullReload);
			}

			IAimpPlayListItem ^AimpPlayList::GetItem(int index)
			{
				IAimpPlayListItem ^result = nullptr;
				IAIMPPlaylistItem *item;

				if (InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, (void**) &item) == S_OK)
				{
					 result = gcnew AimpPlayListItem(item);
				}

				return result;
			}

			int AimpPlayList::GetItemCount()
			{
				return InternalAimpObject->GetItemCount();
			}

			IAimpPlayListGroup ^AimpPlayList::GetGroup(int index)
			{
				IAimpPlayListGroup ^result = nullptr;
				IAIMPPlaylistGroup *group;

				if (InternalAimpObject->GetGroup(index, IID_IAIMPPlaylistGroup, (void**)&group))
				{
					result = gcnew AimpPlayListGroup(group);
				}

				return result;
			}

			int AimpPlayList::GetGroupCount()
			{
				return InternalAimpObject->GetGroupCount();
			}


			void ActivatedCallback(gcroot<AimpPlayList^> This)
			{
				This->Activated(This);
			}

			void AimpPlayList::Activated::add(AIMP::Services::PlayListManager::PlayListHandler ^onEvent)
			{
				RegisterListner();
				if (_onActivated == nullptr)
				{
					_activatedCallback = new AIMP::ConnectionCallback;
					*_activatedCallback = _listner->RegisterActivatedCallback(boost::bind(ActivatedCallback, gcroot<AimpPlayList^>(this)));
					_onActivated = onEvent;
				}
			}

			void AimpPlayList::Activated::remove(AIMP::Services::PlayListManager::PlayListHandler ^onEvent)
			{
				_onActivated == nullptr;
				_listner->UregisterActivatedCallback(_activatedCallback);
			}

			void AimpPlayList::Activated::raise(IAimpPlayList ^sender)
			{
				AIMP::Services::PlayListManager::PlayListHandler ^tmp = this->_onActivated;
				if (tmp != nullptr)
				{
					_onActivated(sender);
				}
			}

			void RemovedCallback(gcroot<AimpPlayList^> This)
			{
				This->Activated(This);
			}

			void AimpPlayList::Removed::add(AIMP::Services::PlayListManager::PlayListHandler ^onEvent)
			{
				RegisterListner();
				if (_onRemoved == nullptr)
				{
					_removedCallBack = new AIMP::ConnectionCallback;
					*_removedCallBack = _listner->RegisterRemovedCallback(boost::bind(RemovedCallback, gcroot<AimpPlayList^>(this)));
					_onRemoved = onEvent;
				}
			}

			void AimpPlayList::Removed::remove(AIMP::Services::PlayListManager::PlayListHandler ^onEvent)
			{
				_onRemoved == nullptr;
				_listner->UnregisterRemoveCallback(_removedCallBack);
			}

			void AimpPlayList::Removed::raise(IAimpPlayList ^sender)
			{
				AIMP::Services::PlayListManager::PlayListHandler ^tmp = this->_onRemoved;
				if (tmp != nullptr)
				{
					_onRemoved(sender);
				}
			}


			void ChangedCallback(gcroot<AimpPlayList^> This, int notifyType)
			{
				This->Changed(This, (PlayListNotifyType)notifyType);
			}

			void AimpPlayList::Changed::add(PlayListChangedHandler ^onEvent)
			{
				RegisterListner();
				if (_onChanged == nullptr)
				{
					_changedCallBack = new AIMP::ConnectionCallback;
					*_changedCallBack = _listner->RegisterChangedCallback(boost::bind(ChangedCallback, gcroot<AimpPlayList^>(this), _1));
					_onChanged = onEvent;
				}
			}

			void AimpPlayList::Changed::remove(PlayListChangedHandler ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Changed::raise(IAimpPlayList^ sender, PlayListNotifyType notifyType)
			{
				AIMP::Services::PlayListManager::PlayListChangedHandler ^tmp = this->_onChanged;
				if (tmp != nullptr)
				{
					_onChanged(sender, notifyType);
				}
			}


			void AimpPlayList::GetPropertyList()
			{
				AIMP36SDK::IAIMPPropertyList *properties;
				InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
				_properties = properties;
			}

			void AimpPlayList::CheckResult(HRESULT result)
			{
				switch (result)
				{
					case E_ACCESSDENIED:
						throw gcnew System::InvalidOperationException("Cross-thread operation not valid");
					case E_HANDLE:
						throw gcnew System::InvalidOperationException("Object already disposed");
					case E_INVALIDARG:
						throw gcnew System::ArgumentException("Invalid argument");
					case E_NOTIMPL:
						throw gcnew System::NotImplementedException();
					case E_UNEXPECTED:
						throw gcnew System::ApplicationException("Unexpected error");
				}
			}

			void AimpPlayList::RegisterListner()
			{
				if (_listner == nullptr)
				{
					_listner = new AimpPlaylistListener();
					InternalAimpObject->ListenerAdd(_listner);
					_listner->AddRef();
				}
			}
		}
	}
};