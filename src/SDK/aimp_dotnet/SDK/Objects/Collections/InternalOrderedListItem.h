#pragma once
#include "SDK/Objects/AimpString.h"

namespace AIMP {
    namespace SDK {
        namespace Collections {
            public class InternalOrderedListItem : public IAIMPString, public IAIMPMLSortDirection {
            private:
                ULONG _linkCounter;
                int _sortDirection;
                gcroot<AimpString^> _name;

            public:
                InternalOrderedListItem(IAIMPString* name, MusicLibrary::SortDirectionType sortDirection);
                HRESULT WINAPI GetValue(int* Value) override;
                HRESULT WINAPI SetValue(int Value) override;
                HRESULT WINAPI GetChar(int Index, WCHAR* Char) override;
                WCHAR* WINAPI GetData() override;
                int WINAPI GetLength() override;
                int WINAPI GetHashCode() override;
                HRESULT WINAPI SetChar(int index, WCHAR Char) override;
                HRESULT WINAPI SetData(WCHAR* Chars, int CharsCount) override;
                HRESULT WINAPI Add(IAIMPString* S) override;
                HRESULT WINAPI Add2(WCHAR* Chars, int CharsCount) override;
                HRESULT WINAPI ChangeCase(int Mode) override;
                HRESULT WINAPI Clone(IAIMPString** S) override;
                HRESULT WINAPI Compare(IAIMPString* S, int* CompareResult, BOOL IgnoreCase) override;
                HRESULT WINAPI Compare2(WCHAR* Chars, int CharsCount, int* CompareResult, BOOL IgnoreCase) override;
                HRESULT WINAPI Delete(int Index, int Count) override;
                HRESULT WINAPI Find(IAIMPString* s, int* index, int flags, int startFromIndex) override;
                HRESULT WINAPI Find2(WCHAR* chars, int charsCount, int* index, int flags, int startFromIndex) override;
                HRESULT WINAPI Insert(int index, IAIMPString* s) override;
                HRESULT WINAPI Insert2(int index, WCHAR* chars, int charsCount) override;
                HRESULT WINAPI Replace(IAIMPString* oldPattern, IAIMPString* newPattern, int flags) override;
                HRESULT WINAPI Replace2(WCHAR* oldPatternChars, int oldPatternCharsCount, WCHAR* newPatternChars, int newPatternCharsCount, int flags) override;
                HRESULT WINAPI SubString(int index, int count, IAIMPString** s) override;
                HRESULT __stdcall QueryInterface(const IID& riid, void** ppvObject) override;
                ULONG __stdcall AddRef() override;
                ULONG __stdcall Release() override;
            };
        }
    }
}
