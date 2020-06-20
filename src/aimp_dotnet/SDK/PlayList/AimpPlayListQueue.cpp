// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlayListQueue.h"

AimpPlaylistQueue::AimpPlaylistQueue(IAIMPPlaylistQueue* queue, IAIMPPlaylistQueue2* queue2) : AimpObject(queue)
{
    _listner = new AimpPlaylistQueueListener(this);
    HRESULT res = queue2->ListenerAdd(_listner);
    //System::Diagnostics::Debug::WriteLine(res);
    //_queue2 = queue2;
}

//AimpPlaylistQueue::AimpPlaylistQueue(ManagedAimpCore^ core) : BaseAimpService<IAIMPPlaylistQueue>(core)
//{
//    IAIMPPlaylistQueue* service = nullptr;
//    GetService(IID_IAIMPPlaylistQueue, &service);
//    if (service != nullptr)
//    {
//        _service = service;
//        IAIMPPropertyList* prop = nullptr;
//        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
//        _properties = prop;
//    }
//    IAIMPPlaylistQueue2* service2 = nullptr;
//    GetService(IID_IAIMPPlaylistQueue2, &service);
//    if (service2 != nullptr)
//    {
//        _listner = new AimpPlaylistQueueListener(this);
//        service2->ListenerAdd(_listner);
//    }
//}

bool AimpPlaylistQueue::IsSuspended::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&properties));
        return PropertyListExtension::GetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED);
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
        }
    }
}

void AimpPlaylistQueue::IsSuspended::set(bool value)
{
    IAIMPPropertyList* properties = nullptr;
    InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&properties));
    PropertyListExtension::SetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED, value);
    properties->Release();
}

VoidResult AimpPlaylistQueue::Add(IAimpPlaylistItem^ item, bool insertAtBeginning)
{
    const auto internalObj = static_cast<AimpPlaylistItem^>(item)->InternalAimpObject;
    if (internalObj == nullptr)
    {
        NULL_REFERENCE()
    }

    return VOID_RESULT(CheckResult(InternalAimpObject->Add(internalObj, insertAtBeginning)));
}

VoidResult AimpPlaylistQueue::AddList(Generic::IList<IAimpPlaylistItem^>^ items, bool insertAtBeginning)
{
    ActionResultType result = ActionResultType::Fail;
    if (items->Count > 0)
    {
        IAIMPObjectList* list = nullptr;
        result = CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list)));
        if (result == ActionResultType::OK && list != nullptr)
        {
            for (int i = 0; i < items->Count; i++)
            {
                result = CheckResult(list->Add(static_cast<AimpPlaylistItem^>(items[i])->InternalAimpObject));

                if (result != ActionResultType::OK)
                {
                    return VOID_RESULT(result);
                }
            }

            result = CheckResult(InternalAimpObject->AddList(list, insertAtBeginning));
        }
    }

    return VOID_RESULT(result);
}

int AimpPlaylistQueue::GetItemCount()
{
    return InternalAimpObject->GetItemCount();
}

VoidResult AimpPlaylistQueue::Delete(IAimpPlaylist^ playList)
{
    return VOID_RESULT(CheckResult(InternalAimpObject->Delete2(static_cast<AimpPlayList^>(playList)->InternalAimpObject)));
}

VoidResult AimpPlaylistQueue::Delete(IAimpPlaylistItem^ item)
{
    return VOID_RESULT(CheckResult(InternalAimpObject->Delete(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject)));
}

VoidResult AimpPlaylistQueue::Move(IAimpPlaylistItem^ item, int index)
{
    return VOID_RESULT(CheckResult(InternalAimpObject->Move(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject, index)));
}

VoidResult AimpPlaylistQueue::Move(int index, int targetIndex)
{
    return VOID_RESULT(CheckResult(InternalAimpObject->Move2(index, targetIndex)));
}

AimpActionResult<IAimpPlaylistItem^>^ AimpPlaylistQueue::GetItem(int index)
{
    void** itm = nullptr;
    IAIMPPlaylistItem* it = nullptr;
    IAimpPlaylistItem^ item = nullptr;

    ActionResultType res = CheckResult(InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, itm));

    if (res == ActionResultType::OK && itm != nullptr)
    {
        item = gcnew AimpPlaylistItem(it);
    }

    return gcnew AimpActionResult<IAimpPlaylistItem^>(res, item);
}


void AimpPlaylistQueue::ContentChanged::add(AimpPlaylistQueueListenerHandler^ onEvent)
{
    if (_contentChanged == nullptr)
    {
        _contentChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Combine(_contentChanged, onEvent));
    }
}

void AimpPlaylistQueue::ContentChanged::remove(AimpPlaylistQueueListenerHandler^ onEvent)
{
    if (_contentChanged != nullptr)
    {
        _contentChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Remove(_contentChanged, onEvent));
    }
}

void AimpPlaylistQueue::ContentChanged::raise(IAimpPlaylistQueue^ sender)
{
    if (_contentChanged != nullptr)
    {
        _contentChanged(sender);
    }
}


void AimpPlaylistQueue::StateChanged::add(AimpPlaylistQueueListenerHandler^ onEvent)
{
    if (_stateChanged == nullptr)
    {
        _stateChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Combine(_stateChanged, onEvent));
    }
}

void AimpPlaylistQueue::StateChanged::remove(AimpPlaylistQueueListenerHandler^ onEvent)
{
    if (_stateChanged != nullptr)
    {
        _stateChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Remove(_stateChanged, onEvent));
    }
}

void AimpPlaylistQueue::StateChanged::raise(IAimpPlaylistQueue^ sender)
{
    if (_stateChanged != nullptr)
    {
        _stateChanged(sender);
    }
}

//IAIMPPlaylistQueue* AimpPlaylistQueue::GetAimpService()
//{
//    IAIMPPlaylistQueue* service = nullptr;
//    GetService(IID_IAIMPPlaylistQueue, &service);
//    return service;
//}
