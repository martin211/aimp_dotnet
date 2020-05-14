#include "Stdafx.h"
#include "AimpServiceAlbumArtCache.h"

using namespace AIMP::SDK;

AimpServiceAlbumArtCache::AimpServiceAlbumArtCache(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceAlbumArtCache>(core)
{ }

AimpActionResult^ AimpServiceAlbumArtCache::Flush(String^ album, String^ artist)
{
    if (String::IsNullOrEmpty(album))
    {
        ARGUMENT_NULL("album", "Parameter album cannot be empty");
    }

    if (String::IsNullOrEmpty(artist))
    {
        ARGUMENT_NULL("artist", "Parameter artist cannot be empty");
    }

    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            auto al = AimpConverter::ToAimpString(album);
            auto ar = AimpConverter::ToAimpString(artist);
            result = CheckResult(service->Flush(al, ar));
            ReleaseObject(al);
            ReleaseObject(ar);
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return GetResult(result);
}

AimpActionResult^ AimpServiceAlbumArtCache::Flush2(String^ fileUri)
{
    if (String::IsNullOrEmpty(fileUri))
    {
        ARGUMENT_NULL("fileUri", "Parameter fileUri cannot be empty");
    }

    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            auto uri = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->Flush2(uri));
            ReleaseObject(uri);
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return GetResult(result);
}

AimpActionResult^ AimpServiceAlbumArtCache::FlushAll()
{
    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            result = CheckResult(service->FlushAll());
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return GetResult(result);
}

IAIMPServiceAlbumArtCache* AimpServiceAlbumArtCache::GetAimpService()
{
    IAIMPServiceAlbumArtCache* service = nullptr;
    GetService(IID_IAIMPServiceAlbumArtCache, &service);
    return service;
}

