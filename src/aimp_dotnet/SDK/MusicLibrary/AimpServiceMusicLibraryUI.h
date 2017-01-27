/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
