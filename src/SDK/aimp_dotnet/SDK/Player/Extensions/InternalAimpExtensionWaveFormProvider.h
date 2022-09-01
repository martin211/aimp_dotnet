#pragma once

using namespace Player::Extensions;

public ref class AimpWaveformPeakInfo : public Player::Objects::IAimpWaveformPeakInfo {
private:
    TAIMPWaveformPeakInfo* _native;
public:
    AimpWaveformPeakInfo(TAIMPWaveformPeakInfo* native);

    property int MaxNegative {
        virtual int get();
        virtual void set(int value);
    }
    property int MaxPositive {
        virtual int get();
        virtual void set(int value);
    }
};


class InternalAimpExtensionWaveFormProvider : public IUnknownInterfaceImpl<IAIMPExtensionWaveFormProvider> {
private:
    gcroot<IAimpExtensionWaveFormProvider^> _managed;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionWaveFormProvider> Base;

    InternalAimpExtensionWaveFormProvider(gcroot<IAimpExtensionWaveFormProvider^> managed);

    HRESULT WINAPI Calculate(IAIMPString* fileURI, IAIMPTaskOwner* taskOwner, PAIMPWaveformPeakInfo peaks, int peakCount) override;

    HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) override;

    ULONG WINAPI AddRef(void) override;

    ULONG WINAPI Release(void) override;
};