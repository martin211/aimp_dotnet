#pragma once
#include "SDK/Objects/Internal/InternalAimpString.h"

using namespace MusicLibrary;

class InternalAimpSortItem :
	public IUnknownInterfaceImpl<IAIMPMLSortDirection>
{
private:
	gcroot<IAimpSortItem^> _managed;
	IAIMPString* _str;
	int _sortDirection;

public:
	using Base = IUnknownInterfaceImpl<IAIMPMLSortDirection>;

	explicit InternalAimpSortItem(const gcroot<IAimpSortItem^> managed)
		: _managed(managed)
	{
		_str = AimpConverter::ToAimpString(managed->FieldName);
		_sortDirection = static_cast<int>(managed->SortDirection);
	}

	ULONG WINAPI AddRef(void) override;
	ULONG WINAPI Release(void) override;
	HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) override;

	HRESULT WINAPI GetValue(int* Value) override;
	HRESULT WINAPI SetValue(int Value) override;
};
