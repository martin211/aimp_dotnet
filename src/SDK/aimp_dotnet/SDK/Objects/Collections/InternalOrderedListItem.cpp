#include "stdafx.h"
#include "InternalOrderedListItem.h"

using namespace AIMP::SDK::Collections;
using namespace MusicLibrary;

InternalOrderedListItem::InternalOrderedListItem(IAIMPString* name, SortDirectionType sortDirection) {
    _sortDirection = static_cast<int>(sortDirection);
    _name = gcnew AimpString(name);
}

HRESULT InternalOrderedListItem::GetValue(int* Value) {
    *Value = _sortDirection;
    return S_OK;
}

HRESULT InternalOrderedListItem::SetValue(int Value) {
    _sortDirection = Value;
    return S_OK;
}

HRESULT InternalOrderedListItem::GetChar(int Index, WCHAR* Char) {
    return _name->InternalAimpObject->GetChar(Index, Char);
}

WCHAR* InternalOrderedListItem::GetData() {
    return _name->InternalAimpObject->GetData();
}

int InternalOrderedListItem::GetLength() {
    return _name->GetLength();
}

int InternalOrderedListItem::GetHashCode() {
    return _name->GetHashCode();
}

HRESULT InternalOrderedListItem::SetChar(int index, WCHAR Char) {
    return _name->InternalAimpObject->SetChar(index, Char);
}

HRESULT InternalOrderedListItem::SetData(WCHAR* Chars, int CharsCount) {
    return _name->InternalAimpObject->SetData(Chars, CharsCount);
}

HRESULT InternalOrderedListItem::Add(IAIMPString* S) {
    return _name->InternalAimpObject->Add(S);
}

HRESULT InternalOrderedListItem::Add2(WCHAR* Chars, int CharsCount) {
    return _name->InternalAimpObject->Add2(Chars, CharsCount);
}

HRESULT InternalOrderedListItem::ChangeCase(int Mode) {
    return _name->InternalAimpObject->ChangeCase(Mode);
}

HRESULT InternalOrderedListItem::Clone(IAIMPString** S) {
    return _name->InternalAimpObject->Clone(S);
}

HRESULT InternalOrderedListItem::Compare(IAIMPString* S, int* CompareResult, BOOL IgnoreCase) {
    return _name->InternalAimpObject->Compare(S, CompareResult, IgnoreCase);
}

HRESULT InternalOrderedListItem::Compare2(WCHAR* Chars, int CharsCount, int* CompareResult, BOOL IgnoreCase) {
    return _name->InternalAimpObject->Compare2(Chars, CharsCount, CompareResult, IgnoreCase);
}

HRESULT InternalOrderedListItem::Delete(int Index, int Count) {
    return _name->InternalAimpObject->Delete(Index, Count);
}

HRESULT InternalOrderedListItem::Find(IAIMPString* s, int* index, int flags, int startFromIndex) {
    return _name->InternalAimpObject->Find(s, index, flags, startFromIndex);
}

HRESULT InternalOrderedListItem::Find2(WCHAR* chars, int charsCount, int* index, int flags, int startFromIndex) {
    return _name->InternalAimpObject->Find2(chars, charsCount, index, flags, startFromIndex);
}

HRESULT InternalOrderedListItem::Insert(int index, IAIMPString* s) {
    return _name->InternalAimpObject->Insert(index, s);
}

HRESULT InternalOrderedListItem::Insert2(int index, WCHAR* chars, int charsCount) {
    return _name->InternalAimpObject->Insert2(index, chars, charsCount);
}

HRESULT InternalOrderedListItem::Replace(IAIMPString* oldPattern, IAIMPString* newPattern, int flags) {
    return _name->InternalAimpObject->Replace(oldPattern, newPattern, flags);
}

HRESULT InternalOrderedListItem::Replace2(WCHAR* oldPatternChars, int oldPatternCharsCount, WCHAR* newPatternChars, int newPatternCharsCount, int flags) {
    return _name->InternalAimpObject->Replace2(oldPatternChars, oldPatternCharsCount, newPatternChars, newPatternCharsCount, flags);
}

HRESULT InternalOrderedListItem::SubString(int index, int count, IAIMPString** s) {
    return _name->InternalAimpObject->SubString(index, count, s);
}

HRESULT InternalOrderedListItem::QueryInterface(const IID& riid, void** ppvObject) {
    if (riid == IID_IAIMPString) {
        *ppvObject = static_cast<IAIMPString*>(this);
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLSortDirection) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return E_NOTIMPL;
}

ULONG InternalOrderedListItem::AddRef() {
    _linkCounter++;
    return _linkCounter;
}

ULONG InternalOrderedListItem::Release() {
    _linkCounter--;

    if (_linkCounter == 0)
    {
        _name->Release();
        delete this;
        return 0;
    }

    return _linkCounter;
}
