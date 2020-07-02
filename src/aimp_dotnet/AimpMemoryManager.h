// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include <map>

class AimpMemoryManager
{
public:
    struct ObjectInfo
    {
        void* object;
        bool disposed;
    };
private:
    static AimpMemoryManager* instance;
protected:
    AimpMemoryManager();
public:
    std::map<int, ObjectInfo*> objects;
    static AimpMemoryManager& getInstance();

    void AddObject(int key, void* obj);

    void Release(int key);

    void ReleaseAll();
};
