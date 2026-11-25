#pragma once
#include "SDK/ManagedAimpCore.h"

class InternalAimpString : IUnknownInterfaceImpl<IAIMPString> {
protected:
    IAIMPString* Instance = nullptr;
private:
    typedef IUnknownInterfaceImpl<IAIMPString> Base;
public:
    InternalAimpString(IAIMPString* inst)
    {
        Instance = inst;
    }

    InternalAimpString() {
        ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&Instance));
    }

    ULONG WINAPI AddRef(void) override {
        return Base::AddRef();
    }

    ULONG WINAPI Release(void) override {
        return Base::Release();
    }

    HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) override {
        const HRESULT res = Base::QueryInterface(riid, ppvObject);

        if (riid == IID_IAIMPString) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        *ppvObject = nullptr;
        return res;
    }

    HRESULT WINAPI GetChar(int Index, WCHAR *Char) override {
        return Instance->GetChar(Index, Char);
    }

    WCHAR* WINAPI GetData() override {
        return Instance->GetData();
    }

    int WINAPI GetLength() override {
        return Instance->GetLength();
    }

    int WINAPI GetHashCode() override {
        return Instance->GetHashCode();
    }

    HRESULT WINAPI SetChar(int Index, WCHAR Char) override {
        return Instance->SetChar(Index, Char);
    }

    HRESULT WINAPI SetData(WCHAR* Chars, int CharsCount) override {
        return Instance->SetData(Chars, CharsCount);
    }

    HRESULT WINAPI Add(IAIMPString* S) override {
        return Instance->Add(S);
    }

    HRESULT WINAPI Add2(WCHAR* Chars, int CharsCount) override {
        return Instance->Add2(Chars, CharsCount);
    }

    HRESULT WINAPI ChangeCase(int Mode) override {
        return Instance->ChangeCase(Mode);
    }

    HRESULT WINAPI Clone(IAIMPString **S) override {
        return Instance->Clone(S);
    }

    HRESULT WINAPI Compare(IAIMPString* S, int* CompareResult, BOOL IgnoreCase) override {
        return Instance->Compare(S, CompareResult, IgnoreCase);
    }

    HRESULT WINAPI Compare2(WCHAR* Chars, int CharsCount, int* CompareResult, BOOL IgnoreCase) override {
        return Instance->Compare2(Chars, CharsCount, CompareResult, IgnoreCase);
    }

    HRESULT WINAPI Delete(int Index, int Count) override {
        return Instance->Delete(Index, Count);
    }

    HRESULT WINAPI Find(IAIMPString* S, int *Index, int Flags, int StartFromIndex) override {
        return Instance->Find(S, Index, Flags, StartFromIndex);
    }

    HRESULT WINAPI Find2(WCHAR *Chars, int CharsCount, int *Index, int Flags, int StartFromIndex) override {
        return Instance->Find2(Chars, CharsCount, Index, Flags, StartFromIndex);
    }

    HRESULT WINAPI Insert(int Index, IAIMPString *S) override {
        return Instance->Insert(Index, S);
    }

    HRESULT WINAPI Insert2(int Index, WCHAR *Chars, int CharsCount) override {
        return Instance->Insert2(Index, Chars, CharsCount);
    }

    HRESULT WINAPI Replace(IAIMPString *OldPattern, IAIMPString *NewPattern, int Flags) override {
        return Instance->Replace(OldPattern, NewPattern, Flags);
    }

    HRESULT WINAPI Replace2(WCHAR *OldPatternChars, int OldPatternCharsCount, WCHAR *NewPatternChars, int NewPatternCharsCount, int Flags) override {
        return S_OK;
    }

    HRESULT WINAPI SubString(int Index, int Count, IAIMPString **S) override {
        return Instance->SubString(Index, Count, S);
    }
};
