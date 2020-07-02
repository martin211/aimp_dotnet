// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlaylistPreimageListener.h"

using namespace AIMP::SDK;

AimpPlaylistPreimageListener::
AimpPlaylistPreimageListener(IAIMPPlaylistPreimageListener* aimpObject) : AimpObject(aimpObject)
{
}

void AimpPlaylistPreimageListener::DataChanged::add(AimpPlaylistPreimageListenerHandler^ onEvent)
{
    if (_dataChangedHandler == nullptr)
    {
        _dataChangedHandler = static_cast<AimpPlaylistPreimageListenerHandler^>(Delegate::Combine(
            _dataChangedHandler, onEvent));
    }
}

void AimpPlaylistPreimageListener::DataChanged::remove(AimpPlaylistPreimageListenerHandler^ onEvent)
{
    if (_dataChangedHandler != nullptr)
    {
        _dataChangedHandler = static_cast<AimpPlaylistPreimageListenerHandler^>(Delegate::Remove(
            _dataChangedHandler, onEvent));
    }
}

void AimpPlaylistPreimageListener::DataChanged::raise()
{
    if (_dataChangedHandler != nullptr)
    {
        _dataChangedHandler();
    }
}

void AimpPlaylistPreimageListener::SettingsChanged::add(AimpPlaylistPreimageListenerHandler^ onEvent)
{
    if (_settingsChangedHandler == nullptr)
    {
        _settingsChangedHandler = static_cast<AimpPlaylistPreimageListenerHandler^>(Delegate::Combine(
            _settingsChangedHandler, onEvent));
    }
}

void AimpPlaylistPreimageListener::SettingsChanged::remove(AimpPlaylistPreimageListenerHandler^ onEvent)
{
    if (_settingsChangedHandler != nullptr)
    {
        _settingsChangedHandler = static_cast<AimpPlaylistPreimageListenerHandler^>(Delegate::Remove(
            _settingsChangedHandler, onEvent));
    }
}

void AimpPlaylistPreimageListener::SettingsChanged::raise()
{
    if (_settingsChangedHandler != nullptr)
    {
        _settingsChangedHandler();
    }
}
