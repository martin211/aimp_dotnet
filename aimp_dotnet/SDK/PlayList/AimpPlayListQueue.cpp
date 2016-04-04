#include "..\..\Stdafx.h"
#include "AimpPlayListQueue.h"

void ContentChangedCallBack(gcroot<AimpPlaylistQueue^> sender)
{
    sender->ContentChanged(sender, EventArgs::Empty);
}

void StateChangedCallback(gcroot<AimpPlaylistQueue^> sender)
{
    sender->StateChanged(sender, EventArgs::Empty);
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

AimpActionResult AimpPlaylistQueue::Add(IAimpPlayListItem^ item, bool insertAtBeginning)
{
    return CheckResult(InternalAimpObject->Add(((AimpPlayListItem^)item)->InternalAimpObject, insertAtBeginning));
}

AimpActionResult AimpPlaylistQueue::AddList(System::Collections::Generic::IList<IAimpPlayListItem^>^ items, bool insertAtBeginning)
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
                AimpPlayListItem ^newItem = gcnew AimpPlayListItem(items[i]);
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

AimpActionResult AimpPlaylistQueue::Delete(IAimpPlayList^ playList)
{
    return CheckResult(InternalAimpObject->Delete2(((AimpPlayList^)playList)->InternalAimpObject));
}

AimpActionResult AimpPlaylistQueue::Delete(IAimpPlayListItem^ item)
{
    return CheckResult(InternalAimpObject->Delete(((AimpPlayListItem^)item)->InternalAimpObject));
}

AimpActionResult AimpPlaylistQueue::Move(IAimpPlayListItem^ item, int index)
{
    return CheckResult(InternalAimpObject->Move(((AimpPlayListItem^)item)->InternalAimpObject, index));
}

AimpActionResult AimpPlaylistQueue::Move(int index, int targetIndex)
{
    return CheckResult(InternalAimpObject->Move2(index, targetIndex));
}

AimpActionResult AimpPlaylistQueue::GetItem(int index, IAimpPlayListItem ^%item)
{
    void** itm = NULL;
    IAIMPPlaylistItem *it = nullptr;
    AimpActionResult res = CheckResult(InternalAimpObject->GetItem(index, IID_IAIMPPlaylistItem, itm));

    if (res == AimpActionResult::Ok)
    {
        item = gcnew AimpPlayListItem(it);
    }

    return res;
}


void AimpPlaylistQueue::ContentChanged::add(EventHandler ^onEvent)
{
    if (_contentChanged == nullptr)
    {
        _contentChangedCallback = new AIMP::ConnectionCallback;
        *_contentChangedCallback = _listner->RegisterContentChangedCallback(boost::bind(ContentChangedCallBack, gcroot<AimpPlaylistQueue^>(this)));
        _contentChanged = (EventHandler^)Delegate::Combine(_contentChanged, onEvent);
    }
}

void AimpPlaylistQueue::ContentChanged::remove(EventHandler ^onEvent)
{
    if (_contentChanged != nullptr)
    {
        _listner->UnregisterContentChangedCallback(_contentChangedCallback);
        _contentChanged = (EventHandler^)Delegate::Remove(_contentChanged, onEvent);
    }
}

void AimpPlaylistQueue::ContentChanged::raise(Object ^sender, EventArgs ^args)
{
    if (_contentChanged != nullptr)
    {
        _contentChanged(sender, args);
    }
}


void AimpPlaylistQueue::StateChanged::add(EventHandler ^onEvent)
{
    if (_stateChanged == nullptr)
    {
        _stateChangedCallback = new AIMP::ConnectionCallback;
        *_stateChangedCallback = _listner->RegisterStateChangedCallback(boost::bind(StateChangedCallback, gcroot<AimpPlaylistQueue^>(this)));
        _stateChanged = (EventHandler^)Delegate::Combine(_stateChanged, onEvent);
    }
}

void AimpPlaylistQueue::StateChanged::remove(EventHandler ^onEvent)
{
    if (_stateChanged != nullptr)
    {
        _listner->UnregisterStateChangedCallback(_stateChangedCallback);
        _stateChanged = (EventHandler^)Delegate::Remove(_stateChanged, onEvent);
    }
}

void AimpPlaylistQueue::StateChanged::raise(Object ^sender, EventArgs ^args)
{
    if (_stateChanged != nullptr)
    {
        _stateChanged(sender, args);
    }
}
