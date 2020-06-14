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
}

void AimpMemoryManager::Release(int key)
{
    const auto obj = instance->objects[key];
    if (!obj->disposed) {
        static_cast<IUnknown*>(obj->object)->Release();
        obj->disposed = true;
    }
}

void AimpMemoryManager::ReleaseAll()
{
    for (auto obj = instance->objects.begin(); obj != instance->objects.end(); ++obj)
    {
        if (!obj->second->disposed)
        {
            static_cast<IUnknown*>(obj->second->object)->Release();
            obj->second->disposed = true;
        }
    }
}

