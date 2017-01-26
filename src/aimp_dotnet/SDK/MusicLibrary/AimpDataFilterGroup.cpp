#include "Stdafx.h"
#include "AimpDataFilterGroup.h"
#include "AimpDataFieldFilter.h"

using namespace AIMP::SDK;

AimpDataFilterGroup::AimpDataFilterGroup(IAIMPMLDataFilterGroup* filterGroup) : AimpObject(filterGroup)
{
}

FilterGroupOperationType AimpDataFilterGroup::Operation::get()
{
    return (FilterGroupOperationType)PropertyListExtension::GetInt32(_aimpObject, AIMPML_FILTERGROUP_OPERATION);
}

void AimpDataFilterGroup::Operation::set(FilterGroupOperationType val)
{
    PropertyListExtension::SetInt32(_aimpObject, AIMPML_FILTERGROUP_OPERATION, (int)val);
}

AimpActionResult AimpDataFilterGroup::Add(String^ field, Object^ value1, Object^ value2, FieldFilterOperationType operation, IAimpDataFieldFilter^% filter)
{
    filter = nullptr;

    VARIANT val1 = AimpConverter::ToNativeVariant(value1);
    VARIANT val2 = AimpConverter::ToNativeVariant(value2);

    IAIMPMLDataFieldFilter* nativeFilter;

    VARIANT v1;
    VariantInit(&v1);

    IAIMPString *sField = AimpConverter::ToAimpString(field);

    try
    {
        AimpActionResult result = CheckResult(_aimpObject->Add(
            sField,
            &val1,
            &val2,
            (int)operation,
            &nativeFilter));

        if (result == AimpActionResult::Ok)
        {
            filter = gcnew AimpDataFieldFilter(nativeFilter);
        }

        return result;
    }
    finally
    {
        if (sField != NULL)
        {
            sField->Release();
            sField = NULL;
        }
    }
}

AimpActionResult AimpDataFilterGroup::Add(String^ field, array<Object^>^ values, int count, IAimpDataFieldFilterByArray^% filter)
{
    //AimpActionResult result = CheckResult(InternalAimpObject->Add2(
    //    AimpConverter::GetAimpString(field), 

    //    ));
    // todo Complete it.
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpDataFilterGroup::AddGroup(IAimpDataFilterGroup^% group)
{
    IAIMPMLDataFilterGroup *nativeGroup;
    AimpActionResult result = CheckResult(_aimpObject->AddGroup(&nativeGroup));
    group = nullptr;

    if (result == AimpActionResult::Ok)
    {
        group = gcnew AimpDataFilterGroup(nativeGroup);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::Clear()
{
    return CheckResult(_aimpObject->Clear());
}

AimpActionResult AimpDataFilterGroup::Delete(int index)
{
    return CheckResult(_aimpObject->Delete(index));
}

int AimpDataFilterGroup::GetChildCount()
{
    return _aimpObject->GetChildCount();
}

AimpActionResult AimpDataFilterGroup::GetChild(int index, IAimpDataFilterGroup^% group)
{
    IAIMPMLDataFilterGroup* child;
    AimpActionResult result = CheckResult(_aimpObject->GetChild(index, IID_IAIMPMLDataFilterGroup, (void**)&child));
    if (result == AimpActionResult::Ok && child != NULL)
    {
        group = gcnew AimpDataFilterGroup(child);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::GetChild(int index, IAimpDataFieldFilter^% fieldFilter)
{
    IAIMPMLDataFieldFilter* child;
    AimpActionResult result = CheckResult(_aimpObject->GetChild(index, IID_IAIMPMLDataFieldFilter, (void**)&child));
    if (result == AimpActionResult::Ok && child != NULL)
    {
        fieldFilter = gcnew AimpDataFieldFilter(child);
    }

    return result;
}

void AimpDataFilterGroup::BeginUpdate()
{
    _aimpObject->BeginUpdate();
}

void AimpDataFilterGroup::EndUpdate()
{
    _aimpObject->EndUpdate();
}
