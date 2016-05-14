#include "..\..\Stdafx.h"
#include "AimpPlayList.h"
#include "AimpPlayListGroup.h"
#include "AimpFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        AimpActionResult AimpPlayList::GetProperties(IAIMPPropertyList** properties)
        {
            IAIMPPropertyList *prop = NULL;
            AimpActionResult result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&prop));
            *properties = prop;
            return result;
        }

        AimpPlayList::AimpPlayList(IAIMPPlaylist *aimpPlayList) : AimpObject(aimpPlayList)
        {
        }

        AimpPlayList::AimpPlayList(IAimpPlayList ^item)
        {
            _aimpObject = AimpExtension::MakeObject<IAIMPPlaylist>(IID_IAIMPPlaylist);
            Name = item->Name;
            ReadOnly = item->ReadOnly;
            FocusedObject = item->FocusedObject;
            //GrouppingOvveriden = item->GrouppingOvveriden;
            Groupping = item->Groupping;
            GrouppingTemplate = item->GrouppingTemplate;
            GrouppingAutomerging = item->GrouppingAutomerging;
            FormatingOverride = item->FormatingOverride;
            FormatingLine1Template = item->FormatingLine1Template;
            FormatingLine2Template = item->FormatingLine2Template;
            ViewOverride = item->ViewOverride;
            ViewDuration = item->ViewDuration;
            ViewExpandButtons = item->ViewExpandButtons;
            ViewMarks = item->ViewMarks;
            ViewNumbers = item->ViewNumbers;
            ViewAbsoluteNumbers = item->ViewAbsoluteNumbers;
            ViewSecondLine = item->ViewSecondLine;
            ViewSwitches = item->ViewSwitches;
            FocusIndex = item->FocusIndex;
            PlaybackCursor = item->PlaybackCursor;
            PlayingIndex = item->PlayingIndex;
            PreImage = item->PreImage;
        }

        AimpPlayList::~AimpPlayList()
        {
            this->!AimpPlayList();
        }

        AimpPlayList::!AimpPlayList()
        {
            Release();
        }

        void AimpPlayList::Release()
        {
            if (_disposed)
                return;

            System::Diagnostics::Debug::WriteLine("Dispose play list");

            _disposed = true;

            if (InternalAimpObject != NULL)
            {
                _aimpObject->Release();
                _aimpObject = NULL;
            }
        }

        String ^AimpPlayList::Id::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
                }

                return nullptr;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        String ^AimpPlayList::Name::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
                }

                return nullptr;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::Name::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_NAME, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        bool AimpPlayList::ReadOnly::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_READONLY);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ReadOnly::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_READONLY, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        Object ^AimpPlayList::FocusedObject::get()
        {
            // todo
            return nullptr;
        }

        void AimpPlayList::FocusedObject::set(Object ^value)
        {
        // todo
        }


        bool AimpPlayList::GrouppingOverriden::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::GrouppingOverriden::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::Groupping::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::Groupping::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING, value);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        String ^AimpPlayList::GrouppingTemplate::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE);

                return nullptr;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::GrouppingTemplate::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::GrouppingAutomerging::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::GrouppingAutomerging::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::FormatingOverride::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::FormatingOverride::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        String ^AimpPlayList::FormatingLine1Template::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE);

                return nullptr;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::FormatingLine1Template::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        String ^AimpPlayList::FormatingLine2Template::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE);

                return nullptr;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::FormatingLine2Template::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewOverride::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewOverride::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewDuration::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewDuration::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_DURATION, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewExpandButtons::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewExpandButtons::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewMarks::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewMarks::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_MARKS, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewNumbers::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewNumbers::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewAbsoluteNumbers::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewAbsoluteNumbers::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewSecondLine::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewSecondLine::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        bool AimpPlayList::ViewSwitches::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES);

                return false;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::ViewSwitches::set(bool value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetBool(properties, AIMP_PLAYLIST_PROPID_VIEW_SWITCHES, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        int AimpPlayList::FocusIndex::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX);

                return 0;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::FocusIndex::set(int value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_FOCUSINDEX, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        int AimpPlayList::PlaybackCursor::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR);

                return 0;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::PlaybackCursor::set(int value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        int AimpPlayList::PlayingIndex::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX);

                return 0;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::PlayingIndex::set(int value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetInt32(properties, AIMP_PLAYLIST_PROPID_PLAYINGINDEX, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        double AimpPlayList::Duration::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                     return PropertyListExtension::GetFloat(properties, AIMP_PLAYLIST_PROPID_DURATION);

                return 0;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        double AimpPlayList::Size::get()
        {
            IAIMPPropertyList *properties = NULL;
            double size = 0;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::GetFloat(properties, AIMP_PLAYLIST_PROPID_SIZE, *&size);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }

            return size;
        }


        String ^AimpPlayList::PreImage::get()
        {
            IAIMPPropertyList *properties = NULL;

            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    return PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_PREIMAGE);

                return nullptr;
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }

        void AimpPlayList::PreImage::set(String ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                    PropertyListExtension::SetString(properties, AIMP_PLAYLIST_PROPID_PREIMAGE, value);
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }


        AimpActionResult AimpPlayList::Add(IAimpFileInfo^ fileInfo, PlayListFlags flags, PlayListFilePosition filePosition)
        {
            AimpFileInfo ^file = CreateFileInfo(fileInfo);
            AimpActionResult result = CheckResult(InternalAimpObject->Add(file->InternalAimpObject, (DWORD)((int)flags), (int)filePosition));
            file->InternalAimpObject->Release();
            return result;
        }

        AimpActionResult AimpPlayList::Add(String^ fileUrl, PlayListFlags flags, PlayListFilePosition filePosition)
        {
            IAIMPString *url = AimpExtension::GetAimpString(fileUrl);
            AimpActionResult res = CheckResult(InternalAimpObject->Add(url, (DWORD)flags, (int)filePosition));
            url->Release();
            url = NULL;
            return res;
        }

        AimpActionResult AimpPlayList::AddList(System::Collections::Generic::IList<IAimpFileInfo^>^ files, PlayListFlags flags, PlayListFilePosition filePosition)
        {
            AimpActionResult res = AimpActionResult::Fail;

            if (files->Count > 0)
            {
                IAIMPObjectList *list;
                ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, (void**)&list);

                if (list != NULL)
                {
                    for (int i = 0; i < files->Count; i++)
                    {
                        AimpFileInfo ^file = CreateFileInfo(files[i]);
                        list->Add(file->InternalAimpObject);
                        file->InternalAimpObject->Release();
                    }

                    res = CheckResult(InternalAimpObject->AddList(list, (DWORD)flags, (int)filePosition));

                    list->Release();
                    list = NULL;
                }
            }

            return res;
        }

        AimpActionResult AimpPlayList::AddList(IList<String^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition)
        {
            AimpActionResult res = AimpActionResult::Fail;

            if (fileUrlList->Count > 0)
            {
                IAIMPObjectList *list;
                ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, (void**)&list);

                if (list != NULL)
                {
                    for (int i = 0; i < fileUrlList->Count; i++)
                    {
                        IAIMPString *str = AimpExtension::GetAimpString(fileUrlList[i]);
                        list->Add(str);
                        str->Release();
                        str = NULL;
                    }

                    list->Release();
                    list = NULL;
                }

                res = CheckResult(InternalAimpObject->AddList(list, (DWORD)flags, (int)filePosition));
            }

            return res;
        }

        AimpActionResult AimpPlayList::Delete(IAimpPlayListItem ^item)
        {
            return CheckResult(InternalAimpObject->Delete(((AimpPlayListItem^)item)->InternalAimpObject));
        }

        AimpActionResult AimpPlayList::Delete(int index)
        {
            return CheckResult(InternalAimpObject->Delete2(index));
        }

        AimpActionResult AimpPlayList::DeleteAll()
        {
            return CheckResult(InternalAimpObject->DeleteAll());
        }

        AimpActionResult AimpPlayList::Sort(PlayListSort sort)
        {
            return CheckResult(InternalAimpObject->Sort((int)sort));
        }

        AimpActionResult AimpPlayList::Sort(Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ compareFunc)
        {
            _compareFunc = compareFunc;
            _sortCallback = gcnew OnSortCallback(this, &AimpPlayList::OnSortReceive);
            IntPtr functionHandle = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_sortCallback);
            return CheckResult(InternalAimpObject->Sort3((TAIMPPlaylistCompareProc(_stdcall*))functionHandle.ToPointer(), NULL));
        }

        AimpActionResult AimpPlayList::BeginUpdate()
        {
            return CheckResult(InternalAimpObject->BeginUpdate());
        }

        AimpActionResult AimpPlayList::EndUpdate()
        {
            return CheckResult(InternalAimpObject->EndUpdate());
        }

        AimpActionResult AimpPlayList::Close(PlayListCloseFlag closeFlag)
        {
            if (_listner != NULL)
            {
                InternalAimpObject->ListenerRemove(_listner);
                _listner->Release();
                _listner = NULL;
            }

            AimpActionResult result = CheckResult(InternalAimpObject->Close((DWORD)closeFlag));
            this->!AimpPlayList();
            return result;
        }

        System::Collections::Generic::IList<String^> ^AimpPlayList::GetFiles(PlayListGetFilesFlag filesFlag)
        {
            IAIMPObjectList *collection;
            InternalAimpObject->GetFiles((DWORD)filesFlag, &collection);

            System::Collections::Generic::IList<String^> ^result = gcnew System::Collections::Generic::List<String^>();

            for (int i = 0; i < collection->GetCount(); i++)
            {
                IAIMPString *str;
                if (collection->GetObject(i, IID_IAIMPString, (void**)&str) == S_OK)
                {
                    result->Add(AimpExtension::GetString(str));
                    str->Release();
                    str = NULL;
                }
            }

            return result;
        }

        AimpActionResult AimpPlayList::ReloadFromPreimage()
        {
            return CheckResult(InternalAimpObject->ReloadFromPreimage());
        }

        AimpActionResult AimpPlayList::ReloadInfo(bool fullReload)
        {
            return CheckResult(InternalAimpObject->ReloadInfo(fullReload));
        }

        IAimpPlayListItem ^AimpPlayList::GetItem(int index)
        {
            IAimpPlayListItem ^result = nullptr;
            IAIMPPlaylistItem *item;

            if (InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, (void**)&item) == S_OK)
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
            IAIMPPlaylistGroup *group = NULL;

            try
            {
                if (CheckResult(InternalAimpObject->GetGroup(index, IID_IAIMPPlaylistGroup, (void**)&group)) == AimpActionResult::Ok)
                {
                    result = gcnew AimpPlayListGroup(group);
                }

                return nullptr;
            }
            finally
            {
                if (group != NULL)
                {
                    group->Release();
                    group = NULL;
                }
            }

            return result;
        }

        int AimpPlayList::GetGroupCount()
        {
            return InternalAimpObject->GetGroupCount();
        }

        void AimpPlayList::RegisterListner()
        {
            if (_listner == nullptr)
            {
                _listner = new AimpPlaylistListener(this);
                InternalAimpObject->ListenerAdd(_listner);
                _listner->AddRef();
            }
        }

        void AimpPlayList::Activated::add(AimpPlayListHandler ^onEvent)
        {
            RegisterListner();
            bool tmp = _onActivated == nullptr;
            if (tmp)
            {
                _onActivated = (AimpPlayListHandler^)Delegate::Combine(_onActivated, onEvent);
            }
        }

        void AimpPlayList::Activated::remove(AimpPlayListHandler ^onEvent)
        {
            bool tmp = _onActivated != nullptr;
            if (tmp)
            {
                _onActivated = (AimpPlayListHandler^)Delegate::Remove(_onActivated, onEvent);
            }
        }

        void AimpPlayList::Activated::raise(IAimpPlayList ^sender)
        {
            AimpPlayListHandler ^tmp = this->_onActivated;
            if (tmp != nullptr)
            {
                _onActivated(sender);
            }
        }



        void AimpPlayList::Removed::add(AimpPlayListHandler ^onEvent)
        {
            RegisterListner();
            bool tmp = _onRemoved != nullptr;
            if (tmp)
            {
                _onRemoved = (AimpPlayListHandler^)Delegate::Combine(_onRemoved, onEvent);
            }
        }

        void AimpPlayList::Removed::remove(AimpPlayListHandler ^onEvent)
        {
            bool tmp = _onRemoved != nullptr;
            if (tmp)
            {
                _onRemoved = (AimpPlayListHandler^)Delegate::Remove(_onRemoved, onEvent);
            }
        }

        void AimpPlayList::Removed::raise(IAimpPlayList ^sender)
        {
            AimpPlayListHandler ^tmp = this->_onRemoved;
            if (tmp != nullptr)
            {
                _onRemoved(sender);
            }
        }



        void AimpPlayList::Changed::add(PlayListChangedHandler ^onEvent)
        {
            RegisterListner();
            if (_onChanged == nullptr)
            {
                _onChanged = (PlayListChangedHandler^)Delegate::Combine(_onChanged, onEvent);
            }
        }

        void AimpPlayList::Changed::remove(PlayListChangedHandler ^onEvent)
        {
            bool tmp = _onChanged != nullptr;
            if (tmp)
            {
                _onChanged = (PlayListChangedHandler^)Delegate::Remove(_onChanged, onEvent);
            }
        }

        void AimpPlayList::Changed::raise(IAimpPlayList^ sender, PlayListNotifyType notifyType)
        {
            AIMP::PlayList::PlayListChangedHandler ^tmp = this->_onChanged;
            if (tmp != nullptr)
            {
                _onChanged(sender, notifyType);
            }
        }

        AimpFileInfo ^AimpPlayList::CreateFileInfo(IAimpFileInfo ^fi)
        {
            AimpFileInfo ^result = gcnew AimpFileInfo();

            result->Album = fi->Album;
            result->AlbumArt = fi->AlbumArt;
            result->AlbumArtist = fi->AlbumArtist;
            result->Artist = fi->Artist;
            result->BitDepth = fi->BitDepth;
            result->BitRate = fi->BitRate;
            result->BPM= fi->BPM;
            result->Channels = fi->Channels;
            result->Codec = fi->Codec;
            result->Comment = fi->Comment;
            result->Composer = fi->Composer;
            result->CopyRight = fi->CopyRight;
            result->CUESheet = fi->CUESheet;
            result->CustomData = fi->CustomData;
            result->Date = fi->Date;
            result->DiskNumber = fi->DiskNumber;
            result->DiskTotal = fi->DiskTotal;
            result->Duration = fi->Duration;
            result->FileName = fi->FileName;
            result->FileSize = fi->FileSize;
            result->Gain = fi->Gain;
            result->Genre = fi->Genre;
            //result->LastPlayedDate = fi->LastPlayedDate;
            result->Lyrics = fi->Lyrics;
            result->Mark = fi->Mark;
            result->Peak = fi->Peak;
            //result->PlayCount = fi->PlayCount;
            result->Publisher = fi->Publisher;
            result->SampleRate = fi->SampleRate;
            result->SampleRate = fi->StateRating;
            result->StatMark = fi->StatMark;
            result->Title = fi->Title;
            result->TrackGain = fi->TrackGain;
            result->TrackNumber = fi->TrackNumber;
            result->TrackPeak = fi->TrackPeak;
            result->TrackTotal = fi->TrackTotal;

            return result;
        }



        void AimpPlayList::ScanningBegin::add(AimpPlayListHandler ^onEvent)
        {
            if (this->_scanningBeginHandler == nullptr)
            {
                _scanningBeginHandler = (AimpPlayListHandler^)Delegate::Combine(_onChanged, onEvent);
            }
        }

        void AimpPlayList::ScanningBegin::remove(AimpPlayListHandler ^onEvent)
        {
            if (this->_scanningBeginHandler != nullptr)
            {
                _scanningBeginHandler = (AimpPlayListHandler^)Delegate::Remove(_onChanged, onEvent);
            }
        }

        void AimpPlayList::ScanningBegin::raise(IAimpPlayList ^sender)
        {
            if (this->_scanningBeginHandler != nullptr)
            {
                _scanningBeginHandler(sender);
            }
        }



        void AimpPlayList::ScanningProgress::add(AimpPlayListHandler<ScanningProgressEventArgs^> ^onEvent)
        {
            if (this->_scanningProgressHandler == nullptr)
            {
                _scanningProgressHandler = (AimpPlayListHandler<ScanningProgressEventArgs^>^)Delegate::Combine(_onChanged, onEvent);
            }
        }

        void AimpPlayList::ScanningProgress::remove(AimpPlayListHandler<ScanningProgressEventArgs^> ^onEvent)
        {
            if (this->_scanningProgressHandler != nullptr)
            {
                _scanningProgressHandler = (AimpPlayListHandler<ScanningProgressEventArgs^>^)Delegate::Remove(_onChanged, onEvent);
            }
        }

        void AimpPlayList::ScanningProgress::raise(IAimpPlayList ^sender, ScanningProgressEventArgs^ args)
        {
            if (this->_scanningProgressHandler != nullptr)
            {
                _scanningProgressHandler(sender, args);
            }
        }



        void AimpPlayList::ScanningEnd::add(AimpPlayListHandler<ScanningEndEventArgs^> ^onEvent)
        {
            if (this->_scanningEndHandler == nullptr)
            {
                _scanningEndHandler = (AimpPlayListHandler<ScanningEndEventArgs^>^)Delegate::Combine(_onChanged, onEvent);
            }
        }

        void AimpPlayList::ScanningEnd::remove(AimpPlayListHandler<ScanningEndEventArgs^> ^onEvent)
        {
            if (this->_scanningEndHandler != nullptr)
            {
                _scanningEndHandler = (AimpPlayListHandler<ScanningEndEventArgs^>^)Delegate::Remove(_onChanged, onEvent);
            }
        }

        void AimpPlayList::ScanningEnd::raise(IAimpPlayList ^sender, ScanningEndEventArgs^ args)
        {
            if (this->_scanningEndHandler != nullptr)
            {
                _scanningEndHandler(sender, args);
            }
        }
    }
};