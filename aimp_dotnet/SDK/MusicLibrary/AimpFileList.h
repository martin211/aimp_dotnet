#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary;

        public ref class AimpFileList :
            public AimpObject<IAIMPMLFileList>,
            public IAimpFileList
        {
        public:
            explicit AimpFileList(IAIMPMLFileList* aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult Add(Object^ id, String^ fileName)
            {
                return CheckResult(InternalAimpObject->Add(&AimpExtension::ToVariant(id), AimpExtension::GetAimpString(fileName)));
            }

            virtual AimpActionResult Clear()
            {
                return CheckResult(InternalAimpObject->Clear());
            }

            virtual AimpActionResult Delete(int index)
            {
                return CheckResult(InternalAimpObject->Delete(index));
            }

            virtual AimpActionResult Insert(int index, Object^ id, String^ fileName)
            {
                return CheckResult(InternalAimpObject->Insert(index, &AimpExtension::ToVariant(id), AimpExtension::GetAimpString(fileName)));
            }

            virtual int GetCount()
            {
                return InternalAimpObject->GetCount();
            }

            virtual AimpActionResult GetFileName(int index, String^% fileName)
            {
                IAIMPString* str = NULL;

                try
                {
                    AimpActionResult res = CheckResult(InternalAimpObject->GetFileName(index, &str));

                    if (res == AimpActionResult::Ok && str != NULL)
                    {
                        fileName = AimpExtension::GetString(str);
                    }

                    return res;
                }
                finally
                {
                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }
            }

            virtual AimpActionResult SetFileName(int index, String^ fileName)
            {
                return CheckResult(InternalAimpObject->SetFileName(index, AimpExtension::GetAimpString(fileName)));
            }

            virtual AimpActionResult GetId(int index, Object^% id)
            {
                VARIANT* idVar;

                try
                {
                    AimpActionResult res = CheckResult(InternalAimpObject->GetID(index, &idVar));

                    if (res == AimpActionResult::Ok)
                    {
                        id = AimpExtension::FromVaiant(idVar);
                    }

                    return res;
                }
                finally
                {
                    idVar = NULL;
                }
            }

            virtual AimpActionResult SetId(int index, Object^ id)
            {
                return CheckResult(InternalAimpObject->SetID(index, &AimpExtension::ToVariant(id)));
            }

            virtual AimpActionResult Clone(IAimpFileList^% list)
            {
                list = nullptr;

                IAIMPMLFileList* cloneList = NULL;
                AimpActionResult res = AimpActionResult::Fail;

                try
                {
                    res = CheckResult(InternalAimpObject->Clone((void**)&cloneList));

                    if (res == AimpActionResult::Ok)
                    {
                        list = gcnew AimpFileList(cloneList);
                    }
                }
                finally
                {
                    if (cloneList != NULL)
                    {
                        cloneList->Release();
                        cloneList = NULL;
                    }
                }

                return res;
            }
        };
    }
}