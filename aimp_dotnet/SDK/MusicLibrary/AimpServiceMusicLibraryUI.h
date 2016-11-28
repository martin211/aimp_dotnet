#pragma once
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
            explicit AimpServiceMusicLibraryUI(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMusicLibraryUI>(core)
            {}

            virtual AimpActionResult GetFiles(FilesType flags, IAimpFileList^% list)
            {
                list = nullptr;
                IAIMPServiceMusicLibraryUI* service = NULL;
                AimpActionResult result = AimpActionResult::Fail;

                try
                {
                    result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
                    if (result == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            IAIMPMLFileList *l = NULL;
                            result = CheckResult(service->GetFiles((int)flags, l));

                            if (result == AimpActionResult::Ok && l != NULL)
                            {
                                list = gcnew AimpFileList(l);
                            }
                        }
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }
                }

                return result;
            }

            virtual AimpActionResult GetGroupingFilter(IAimpDataFilter^% filter)
            {
                filter = nullptr;
                AimpActionResult result = AimpActionResult::Fail;
                IAIMPServiceMusicLibraryUI* service = NULL;

                try
                {
                    result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
                    if (result == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            IAIMPMLDataFilter *f = NULL;
                            result = CheckResult(service->GetGroupingFilter(&f));

                            if (result == AimpActionResult::Ok && f != NULL)
                            {
                                filter = gcnew AimpDataFilter(f);
                            }
                        }
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }
                }

                return result;
            }

            virtual AimpActionResult GetGroupingFilterPath(String^% path)
            {
                path = String::Empty;
                IAIMPServiceMusicLibraryUI* service = NULL;
                AimpActionResult result = AimpActionResult::Fail;

                try
                {
                    result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
                    if (result == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            IAIMPString *str = NULL;
                            result = CheckResult(service->GetGroupingFilterPath(&str));

                            if (result == AimpActionResult::Ok && str != NULL)
                            {
                                path = AimpExtension::GetString(str);
                            }
                        }
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }
                }

                return result;
            }

            virtual AimpActionResult SetGroupingFilterPath(String^ path)
            {
                IAIMPServiceMusicLibraryUI* service = NULL;
                AimpActionResult result = AimpActionResult::Fail;
                IAIMPString* strPath = NULL;

                try
                {
                    result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
                    if (result == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            strPath = AimpExtension::GetAimpString(path);
                            result = CheckResult(service->SetGroupingFilterPath(strPath));
                        }
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }

                    if (strPath != NULL)
                    {
                        strPath->Release();
                        strPath = NULL;
                    }
                }

                return result;
            }
        };
    }
}
