#include "Stdafx.h"
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

			void AimpPlayList::Add(System::String^ fileUrl, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition)
			{
				AIMP36SDK::IAIMPString *url = ObjectHelper::MakeAimpString(AIMP::SDK360::ManagedAimpCore::GetAimpCore(), fileUrl);
				CheckResult(InternalAimpObject->Add(url, (DWORD)flags, (int)filePosition));
			}

			void AimpPlayList::AddList(System::Collections::Generic::IList<AIMP::SDK::Services::PlayListManager::IAimpFileInfo^>^ fileUrlList, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::AddList(System::Collections::Generic::IList<System::String^>^ fileUrlList, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition)
			{
				throw gcnew NotImplementedException();
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

			void AimpPlayList::Sort(Func<IAimpPlayListItem^, IAimpPlayListItem^, String^, PlayListSortComapreResult>^ compareFunc, String ^userData)
			{
				_compareFunc = compareFunc;
				_sortCallback = gcnew OnSortCallback(this, &AIMP::SDK::PlayList::AimpPlayList::OnSortReceive);
				IntPtr functionHandle = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_sortCallback);
				pin_ptr<const WCHAR> strData = PtrToStringChars(userData);
				PWCHAR s = (PWCHAR)strData;
				InternalAimpObject->Sort3((AIMP36SDK::TAIMPPlaylistCompareProc(_stdcall*))functionHandle.ToPointer(), reinterpret_cast<void*>(&s));
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



			//void AimpPlayList::Activated::add(EventHandler ^onEvent)
			//{
			//	throw gcnew NotImplementedException();
			//}

			//void AimpPlayList::Activated::remove(EventHandler ^onEvent)
			//{
			//	throw gcnew NotImplementedException();
			//}

			//void AimpPlayList::Activated::raise(Object ^sender, EventArgs ^args)
			//{
			//	throw gcnew NotImplementedException();
			//}


			//void AimpPlayList::Removed::add(EventHandler ^onEvent)
			//{
			//	throw gcnew NotImplementedException();
			//}

			//void AimpPlayList::Removed::remove(EventHandler ^onEvent)
			//{
			//	throw gcnew NotImplementedException();
			//}

			//void AimpPlayList::Removed::raise(Object ^sender, EventArgs ^args)
			//{
			//	throw gcnew NotImplementedException();
			//}



			//void AimpPlayList::Changed::add(EventHandler<AimpPlayListChangedArgs^> ^onEvent)
			//{
			//	throw gcnew NotImplementedException();
			//}

			//void AimpPlayList::Changed::remove(EventHandler<AimpPlayListChangedArgs^> ^onEvent)
			//{
			//	throw gcnew NotImplementedException();
			//}

			//void AimpPlayList::Changed::raise(Object ^sender, AimpPlayListChangedArgs ^args)
			//{
			//	throw gcnew NotImplementedException();
			//}


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
		}
	}
};