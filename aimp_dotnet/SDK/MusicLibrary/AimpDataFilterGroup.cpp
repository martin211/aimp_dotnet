#include "Stdafx.h"
#include "AimpDataFilterGroup.h"
#include "AimpDataFieldFilter.h"

using namespace AIMP::SDK;

AimpDataFilterGroup::AimpDataFilterGroup(IAIMPMLDataFilterGroup* filterGroup) : AimpObject(filterGroup)
{}

FilterGroupOperationType AimpDataFilterGroup::Operation::get()
{
    return (FilterGroupOperationType)PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTERGROUP_OPERATION);
}

void AimpDataFilterGroup::Operation::set(FilterGroupOperationType val)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTERGROUP_OPERATION, (int)val);
}

AimpActionResult AimpDataFilterGroup::Add(String^ field, Object^ value1, Object^ value2, FilterGroupOperationType operation, IAimpDataFieldFilter^% filter)
{
    VARIANT val1 = AimpExtension::ToNativeVariant(value1);
    VARIANT val2 = AimpExtension::ToNativeVariant(value2);

    IAIMPMLDataFieldFilter* nativeFilter;

    AimpActionResult result = CheckResult(InternalAimpObject->Add(
        AimpExtension::GetAimpString(field),
        val1,
        val2,
        (int)operation,
        &nativeFilter));

    filter = nullptr;

    if (result == AimpActionResult::Ok)
    {
        filter = gcnew AimpDataFieldFilter(nativeFilter);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::Add(String^ field, array<Object^>^ values, int count, IAimpDataFieldFilterByArray^% filter)
{
    //AimpActionResult result = CheckResult(InternalAimpObject->Add2(
    //    AimpExtension::GetAimpString(field), 

    //    ));
    // todo Complete it.
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpDataFilterGroup::AddGroup(IAimpDataFilterGroup^% group)
{
    IAIMPMLDataFilterGroup *nativeGroup;
    AimpActionResult result = CheckResult(InternalAimpObject->AddGroup(&nativeGroup));
    group = nullptr;

    if (result == AimpActionResult::Ok)
    {
        group = gcnew AimpDataFilterGroup(nativeGroup);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::Clear()
{
    return CheckResult(InternalAimpObject->Clear());
}

AimpActionResult AimpDataFilterGroup::Delete(int index)
{
    return CheckResult(InternalAimpObject->Delete(index));
}

int AimpDataFilterGroup::GetChildCount()
{
    return InternalAimpObject->GetChildCount();
}

AimpActionResult AimpDataFilterGroup::GetChild(int index, IAimpDataFilterGroup^% group)
{
    IAIMPMLDataFilterGroup* child;
    AimpActionResult result = CheckResult(InternalAimpObject->GetChild(index, IID_IAIMPMLDataFilterGroup, (void**)&child));
    if (result == AimpActionResult::Ok && child != NULL)
    {
        group = gcnew AimpDataFilterGroup(child);
    }

    return result;
}

AimpActionResult AimpDataFilterGroup::GetChild(int index, IAimpDataFieldFilter^% fieldFilter)
{
    IAIMPMLDataFieldFilter* child;
    AimpActionResult result = CheckResult(InternalAimpObject->GetChild(index, IID_IAIMPMLDataFieldFilter, (void**)&child));
    if (result == AimpActionResult::Ok && child != NULL)
    {
        fieldFilter = gcnew AimpDataFieldFilter(child);
    }

    return result;
}
