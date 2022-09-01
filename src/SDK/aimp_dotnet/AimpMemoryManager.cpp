//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

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

void AimpMemoryManager::AddObject(int key, void* obj, std::string name)
{
    const auto info = new ObjectInfo();
    info->object = obj;
    info->disposed = false;
    info->name = name;
    instance->objects[key] = info;
    static_cast<IUnknown*>(obj)->AddRef();
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
                catch (std::exception ex) {
                }
            }
            obj->disposed = true;
        }
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

