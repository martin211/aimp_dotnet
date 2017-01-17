#pragma once
#include "..\AimpObject.h"
#include "..\ManagedAimpCore.h"
#include "AimpFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpVirtualFile : public AimpObject<IAIMPVirtualFile>, public IAimpVirtualFile
        {
        public:
            AimpVirtualFile(IAIMPVirtualFile *aimpObject) : AimpObject(aimpObject)
            {}

            virtual property int IndexInSet
            {
                int get()
                {
                    return PropertyListExtension::GetInt32(_aimpObject, AIMP_VIRTUALFILE_PROPID_INDEXINSET);
                }
                void set(int value)
                {
                    PropertyListExtension::SetInt32(_aimpObject, AIMP_VIRTUALFILE_PROPID_INDEXINSET, value);
                }
            }

            virtual property double ClipStart
            {
                double get()
                {
                    return PropertyListExtension::GetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPSTART);
                }
                void set(double value)
                {
                    PropertyListExtension::SetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPSTART, value);
                }
            }

            virtual property double ClipFinish
            {
                double get()
                {
                    return PropertyListExtension::GetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPFINISH);
                }
                void set(double value)
                {
                    PropertyListExtension::SetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPFINISH, value);
                }
            }

            virtual property String ^AudioSourceFile
            {
                String ^get()
                {
                    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE);
                }
                void set(String ^value)
                {
                    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE, value);
                }
            }

            virtual property String ^FileFormat
            {
                String ^get()
                {
                    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT);
                }
                void set(String ^value)
                {
                    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT, value);
                }
            }

            virtual property String ^FileUri
            {
                String ^get()
                {
                    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI);
                }
                void set(String ^value)
                {
                    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI, value);
                }
            }

            virtual AimpActionResult CreateStream(System::IO::Stream ^%stream)
            {
                stream = nullptr;
                return AimpActionResult::Ok;
            }

            virtual AimpActionResult GetFileInfo(IAimpFileInfo ^%fileInfo)
            {
                IAIMPFileInfo *fi = NULL;
                AimpActionResult result = CheckResult(_aimpObject->GetFileInfo(fi));
                if (result == AimpActionResult::Ok)
                {
                    fileInfo = gcnew AimpFileInfo(fi);
                }

                return result;
            }

            virtual bool IsExists()
            {
                return _aimpObject->IsExists();
            }

            virtual AimpActionResult IsInSameStream(IAimpVirtualFile ^virtualFile)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual AimpActionResult Synchronize()
            {
                return CheckResult(_aimpObject->Synchronize());
            }
        };
    }
}
