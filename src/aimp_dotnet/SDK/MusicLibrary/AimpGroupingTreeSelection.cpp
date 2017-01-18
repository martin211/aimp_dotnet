#include "Stdafx.h"
#include "AimpGroupingTreeSelection.h"

using namespace AIMP::SDK;

AimpGroupingTreeSelection::AimpGroupingTreeSelection(IAIMPMLGroupingTreeSelection* aimpObject) : AimpObject(aimpObject)
{

}

AimpGroupingTreeSelection::~AimpGroupingTreeSelection()
{
    this->!AimpGroupingTreeSelection();
}

AimpGroupingTreeSelection::!AimpGroupingTreeSelection()
{
    _aimpObject->Release();
}

int AimpGroupingTreeSelection::GetCount()
{
    return InternalAimpObject->GetCount();
}

AimpActionResult AimpGroupingTreeSelection::GetValue(int index, System::String^% fieldName, System::Object^% value)
{
    IAIMPString* str;
    VARIANT val;

    fieldName = nullptr;
    value = nullptr;

    AimpActionResult result = CheckResult(InternalAimpObject->GetValue(index, &str, &val));

    try
    {
        if (result == AimpActionResult::Ok)
        {
            if (str != NULL)
                fieldName = AimpExtension::GetString(str);

            value = AimpExtension::FromVaiant(&val);
        }
    }
    finally
    {
        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return result;
}
