#include "Stdafx.h"
#include "AimpDataFilter.h"

using namespace AIMP::SDK;

AimpDataFilter::AimpDataFilter(IAIMPMLDataFilter* native) : AimpDataFilterGroup(native)
{}

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
    return (SortDirectionType)PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_SORTDIRECTION);
}

void  AimpDataFilter::SortDirection::set(SortDirectionType value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_SORTDIRECTION, (int)value);
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

AimpActionResult AimpDataFilter::Assign(IAimpDataFieldFilter^ source)
{
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpDataFilter::Clone(IAimpDataFilter^% source)
{
    source = nullptr;
    return AimpActionResult::NotImplemented;
}
