// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlayListQueue.h"

AimpPlaylistQueue::AimpPlaylistQueue(IAIMPPlaylistQueue *queue, IAIMPPlaylistQueue2 *queue2) : AimpObject(queue)
{
    _listner = new AimpPlaylistQueueListener(this);
    HRESULT res = queue2->ListenerAdd(_listner);
    System::Diagnostics::Debug::WriteLine(res);
    _queue2 = queue2;
}

bool AimpPlaylistQueue::IsSuspended::get()
{
    IAIMPPropertyList *properties;
    _aimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    return PropertyListExtension::GetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED);
}

void AimpPlaylistQueue::IsSuspended::set(bool value)
{
    IAIMPPropertyList *properties;
    _aimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
    PropertyListExtension::SetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED, value);
}

AimpActionResult AimpPlaylistQueue::Add(IAimpPlaylistItem^ item, bool insertAtBeginning)
{
    return CheckResult(InternalAimpObject->Add(((AimpPlaylistItem^)item)->InternalAimpObject, insertAtBeginning));
}

AimpActionResult AimpPlaylistQueue::AddList(System::Collections::Generic::IList<IAimpPlaylistItem^>^ items, bool insertAtBeginning)
{
    AimpActionResult result = AimpActionResult::Fail;
    if (items->Count > 0)
    {
        IAIMPObjectList *list;
        ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, (void**)&list);
        if (list != NULL)
        {
            for (int i = 0; i < items->Count; i++)
            {
                AimpPlaylistItem ^newItem = gcnew AimpPlaylistItem(items[i]);
                result = CheckResult(list->Add(newItem->InternalAimpObject));

                if (result != AimpActionResult::Ok)
                {
                    return result;
                }
            }
        }
    }

    return result;
}

int AimpPlaylistQueue::GetItemCount()
{
    return _aimpObject->GetItemCount();
}

AimpActionResult AimpPlaylistQueue::Delete(IAimpPlaylist^ playList)
{
    return CheckResult(InternalAimpObject->Delete2(((AimpPlayList^)playList)->InternalAimpObject));
}

AimpActionResult AimpPlaylistQueue::Delete(IAimpPlaylistItem^ item)
{
    return CheckResult(InternalAimpObject->Delete(((AimpPlaylistItem^)item)->InternalAimpObject));
}

AimpActionResult AimpPlaylistQueue::Move(IAimpPlaylistItem^ item, int index)
{
    return CheckResult(InternalAimpObject->Move(((AimpPlaylistItem^)item)->InternalAimpObject, index));
}

AimpActionResult AimpPlaylistQueue::Move(int index, int targetIndex)
{
    return CheckResult(InternalAimpObject->Move2(index, targetIndex));
}

AimpActionResult AimpPlaylistQueue::GetItem(int index, IAimpPlaylistItem ^%item)
{
    void** itm = NULL;
    IAIMPPlaylistItem *it = nullptr;
    AimpActionResult res = CheckResult(InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, itm));

    if (res == AimpActionResult::Ok)
    {
        item = gcnew AimpPlaylistItem(it);
    }

    return res;
}


void AimpPlaylistQueue::ContentChanged::add(AimpPlaylistQueueListenerHandler ^onEvent)
{
    if (_contentChanged == nullptr)
    {
        _contentChanged = (AimpPlaylistQueueListenerHandler^)Delegate::Combine(_contentChanged, onEvent);
    }
}

void AimpPlaylistQueue::ContentChanged::remove(AimpPlaylistQueueListenerHandler ^onEvent)
{
    if (_contentChanged != nullptr)
    {
        _contentChanged = (AimpPlaylistQueueListenerHandler^)Delegate::Remove(_contentChanged, onEvent);
    }
}

void AimpPlaylistQueue::ContentChanged::raise(IAimpPlaylistQueue ^sender)
{
    if (_contentChanged != nullptr)
    {
        _contentChanged(sender);
    }
}


void AimpPlaylistQueue::StateChanged::add(AimpPlaylistQueueListenerHandler ^onEvent)
{
    if (_stateChanged == nullptr)
    {
        _stateChanged = (AimpPlaylistQueueListenerHandler^)Delegate::Combine(_stateChanged, onEvent);
    }
}

void AimpPlaylistQueue::StateChanged::remove(AimpPlaylistQueueListenerHandler ^onEvent)
{
    if (_stateChanged != nullptr)
    {
        _stateChanged = (AimpPlaylistQueueListenerHandler^)Delegate::Remove(_stateChanged, onEvent);
    }
}

void AimpPlaylistQueue::StateChanged::raise(IAimpPlaylistQueue ^sender)
{
    if (_stateChanged != nullptr)
    {
        _stateChanged(sender);
    }
}
