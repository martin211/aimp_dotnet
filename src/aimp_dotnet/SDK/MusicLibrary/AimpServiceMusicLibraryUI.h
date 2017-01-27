#pragma once
#include "..\BaseManager.h"
#include "AimpFileList.h"


namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary;

        public ref class AimpServiceMusicLibraryUI :
            public AimpBaseManager<IAIMPServiceMusicLibraryUI>,
            public IAimpServiceMusicLibraryUI
        {
        public:
            explicit AimpServiceMusicLibraryUI(ManagedAimpCore^ core);

            virtual AimpActionResult GetFiles(FilesType flags, IAimpFileList^% list);

            virtual AimpActionResult GetGroupingFilter(IAimpDataFilter^% filter);

            virtual AimpActionResult GetGroupingFilterPath(String^% path);

            virtual AimpActionResult SetGroupingFilterPath(String^ path);
        };
    }
}
