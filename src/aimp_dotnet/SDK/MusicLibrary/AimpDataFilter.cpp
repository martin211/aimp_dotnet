// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataFilter.h"

using namespace AIMP::SDK;

AimpDataFilter::AimpDataFilter(IAIMPMLDataFilter* native) : AimpDataFilterGroup(native)
{
    InternalDataFilter = native;
}

int AimpDataFilter::Offset::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_OFFSET);
}

void AimpDataFilter::Offset::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_OFFSET, value);
}

int AimpDataFilter::Limit::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_LIMIT);
}

void AimpDataFilter::Limit::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_LIMIT, value);
}

String^ AimpDataFilter::SortBy::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FILTER_SORTBY);
}

void AimpDataFilter::SortBy::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FILTER_SORTBY, value);
}

SortDirectionType AimpDataFilter::SortDirection::get()
{
    return SortDirectionType(PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_SORTDIRECTION));
}

void AimpDataFilter::SortDirection::set(SortDirectionType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_SORTDIRECTION, int(value));
}

String^ AimpDataFilter::SearchString::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FILTER_SEARCHSTRING);
}

void AimpDataFilter::SearchString::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FILTER_SEARCHSTRING, value);
}

int AimpDataFilter::AlphaBeticIndex::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_ALPHABETICINDEX);
}

void AimpDataFilter::AlphaBeticIndex::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_ALPHABETICINDEX, value);
}

ActionResultType AimpDataFilter::Assign(IAimpDataFilter^ source)
{
    IAIMPMLDataFilter* filter = static_cast<AimpDataFilter^>(source)->InternalDataFilter;
    return Utils::CheckResult(InternalDataFilter->Assign(filter));
}

ActionResultType AimpDataFilter::Clone(IAimpDataFilter^% source)
{
    source = nullptr;
    IAIMPMLDataFilter* clone = nullptr;

    const ActionResultType result = Utils::CheckResult(InternalDataFilter->Clone(reinterpret_cast<void**>(&clone)));
    if (result == ActionResultType::OK && clone != nullptr)
    {
        source = gcnew AimpDataFilter(clone);
    }

    // TODO: clone release?

    return result;
}
