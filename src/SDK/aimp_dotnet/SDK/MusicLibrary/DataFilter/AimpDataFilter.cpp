//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataFilter.h"

#include "AimpSortItem.h"
#include "SDK/ManagedAimpCore.h"
#include "SDK/MusicLibrary/Internal/InternalAimpSortItem.h"

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

List<IAimpSortItem^>^ AimpDataFilter::SortByList::get()
{
	// TODO: The list is always an empty. Need to contact with owner
	IAIMPObjectList* list = nullptr;
	auto res = PropertyListExtension::GetObject(InternalAimpObject, AIMPML_FILTER_SORTBYLIST, IID_IAIMPObjectList, reinterpret_cast<void**>(&list));

	if (res != ActionResultType::OK)
	{
		return nullptr;
	};

	auto result = gcnew List<IAimpSortItem^>(list->GetCount());
	for (int i = 0; i < list->GetCount(); i++)
	{
		IAIMPString* itm = nullptr;
		IAIMPMLSortDirection* direction = nullptr;
		list->GetObject(i, IID_IAIMPString, reinterpret_cast<void**>(itm));
		list->GetObject(i, IID_IAIMPMLSortDirection, reinterpret_cast<void**>(direction));
		auto item = gcnew AimpSortItem(itm);
		result->Add(item);
	}
}

void AimpDataFilter::SortByList::set(List<IAimpSortItem^>^ value)
{
	IAIMPObjectList* list = nullptr;
	ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(list));

	for (int i = 0; i < value->Count; i++)
	{
		auto item = new InternalAimpSortItem(value[i]);
		list->Add(item);
	}

	InternalAimpObject->SetValueAsObject(AIMPML_FILTER_SORTBYLIST, list);
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

ActionResult AimpDataFilter::Assign(IAimpDataFilter^ source)
{
	IAIMPMLDataFilter* filter = static_cast<AimpDataFilter^>(source)->InternalDataFilter;
	return ACTION_RESULT(Utils::CheckResult(InternalDataFilter->Assign(filter)));
}

AimpActionResult<IAimpDataFilter^>^ AimpDataFilter::Clone()
{
	IAimpDataFilter^ source = nullptr;
	IAIMPMLDataFilter* clone = nullptr;

	const ActionResultType result = Utils::CheckResult(InternalDataFilter->Clone(reinterpret_cast<void**>(&clone)));
	if (result == ActionResultType::OK && clone != nullptr)
	{
		source = gcnew AimpDataFilter(clone);
	}

	return gcnew AimpActionResult<IAimpDataFilter^>(result, source);
}
