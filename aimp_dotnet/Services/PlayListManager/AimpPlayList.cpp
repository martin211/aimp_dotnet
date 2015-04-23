#include "Stdafx.h"
#include "AimpPlayList.h"

namespace AIMP
{
	namespace SDK
	{
		namespace PlayList
		{
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
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Add(System::String^ fileUrl, AIMP::SDK::Services::PlayListManager::PlayListFlags flags, AIMP::SDK::Services::PlayListManager::PlayListFilePosition filePosition)
			{
				throw gcnew NotImplementedException();
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
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Delete(int index)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::DeleteAll()
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Sort(AIMP::SDK::Services::PlayListManager::PlayListSort sort)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::BeginUpdate()
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::EndUpdate()
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Close(AIMP::SDK::Services::PlayListManager::PlayListCloseFlag closeFlag)
			{
				throw gcnew NotImplementedException();
			}

			System::Collections::Generic::IList<AIMP::SDK::Services::PlayListManager::IAimpFileInfo^>^ AimpPlayList::GetFiles(AIMP::SDK::Services::PlayListManager::PlayListGetFilesFlag filesFlag)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::ReloadFromPreimage()
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::ReloadInfo(bool fullReload)
			{
				throw gcnew NotImplementedException();
			}

			IAimpPlayListItem ^AimpPlayList::GetItem(int index)
			{
				throw gcnew NotImplementedException();
			}

			int AimpPlayList::GetItemCount()
			{
				throw gcnew NotImplementedException();
			}

			IAimpPlayListGroup ^AimpPlayList::GetGroup(int index)
			{
				throw gcnew NotImplementedException();
			}

			int AimpPlayList::GetGroupCount()
			{
				throw gcnew NotImplementedException();
			}



			void AimpPlayList::Activated::add(EventHandler ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Activated::remove(EventHandler ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Activated::raise(Object ^sender, EventArgs ^args)
			{
				throw gcnew NotImplementedException();
			}


			void AimpPlayList::Removed::add(EventHandler ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Removed::remove(EventHandler ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Removed::raise(Object ^sender, EventArgs ^args)
			{
				throw gcnew NotImplementedException();
			}



			void AimpPlayList::Changed::add(EventHandler<AimpPlayListChangedArgs^> ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Changed::remove(EventHandler<AimpPlayListChangedArgs^> ^onEvent)
			{
				throw gcnew NotImplementedException();
			}

			void AimpPlayList::Changed::raise(Object ^sender, AimpPlayListChangedArgs ^args)
			{
				throw gcnew NotImplementedException();
			}
		}
	}
};