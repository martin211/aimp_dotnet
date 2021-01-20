// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpMemoryManager.h"

AimpMemoryManager* AimpMemoryManager::instance = 0;

AimpMemoryManager::AimpMemoryManager() {}

AimpMemoryManager& AimpMemoryManager::getInstance()
{
    if (!instance)
    {
        instance = new AimpMemoryManager();
    }
    return *instance;
}

void AimpMemoryManager::AddObject(int key, void* obj)
{
    const auto info = new ObjectInfo();
    info->object = obj;
    info->disposed = false;
    instance->objects[key] = info;
    //static_cast<IUnknown*>(obj)->AddRef();

    // TODO: #18
#ifdef DEBUG
    System::Diagnostics::Debug::WriteLine("Register key: " + key);
    const auto st = gcnew System::Diagnostics::StackTrace(true);
    const auto sb = gcnew System::Text::StringBuilder("Stack trace:");
    for (int i = 0; i < st->FrameCount; ++i) {
        sb->AppendLine(st->GetFrame(i)->GetMethod()->ToString());
    }
    System::Diagnostics::Debug::WriteLine(sb->ToString());
#endif
}

void AimpMemoryManager::Release(int key)
{
    const auto obj = instance->objects[key];

    try
    {
        if (obj != nullptr && !obj->disposed) {
            if (obj->object != nullptr) {
                try {
                    const auto o = static_cast<IUnknown*>(obj->object);
                    o->Release();
                }
                catch (...) {
                }
            }
            obj->disposed = true;
        }
#ifdef DEBUG
        else
        {
            System::Diagnostics::Debug::WriteLine("KEY not found");
        }
#endif
    }
    catch (...)
    {
    }
 }

void AimpMemoryManager::ReleaseAll()
{
    for (auto obj = instance->objects.begin(); obj != instance->objects.end(); ++obj)
    {
        if (obj->second != nullptr && !obj->second->disposed)
        {
            if (obj->second->object != nullptr) {
                try
                {
                    static_cast<IUnknown*>(obj->second->object)->Release();
                }
                catch (...)
                {

                }
            }
            obj->second->disposed = true;
        }
    }
}

