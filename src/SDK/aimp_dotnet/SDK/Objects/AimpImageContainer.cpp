#include "Stdafx.h"
#include "AimpImageContainer.h"
#include "AimpImage.h"

AimpImageContainer::AimpImageContainer(IAIMPImageContainer* container) : AimpObject<IAIMPImageContainer>(container, true) {
}

AimpActionResult<IAimpImage^>^ AimpImageContainer::CreateImage() {
    IAIMPImage* img = nullptr;

    const auto result = CheckResult(InternalAimpObject->CreateImage(&img));

    if (result == ActionResultType::OK && img != nullptr) {
        return gcnew AimpActionResult<IAimpImage^>(result, nullptr);
    }

    return gcnew AimpActionResult<IAimpImage^>(result);
}

AimpActionResult<Tuple<Size, int>^>^ AimpImageContainer::GetInfo() {
    SIZE* s = new SIZE();
    int* format = 0;

    auto const result = CheckResult(InternalAimpObject->GetInfo(s, format));

    if (result == ActionResultType::OK) {
        Size size = Size(s->cx, s->cy);
        delete s;
        return gcnew AimpActionResult<Tuple<Size, int>^>(result, gcnew Tuple<Size, int>(size, *format));
    }

    return gcnew AimpActionResult<Tuple<Size, int>^>(result);
}

AimpActionResult<array<unsigned char>^>^ AimpImageContainer::GetData() {
    const auto size = InternalAimpObject->GetDataSize();

    if (size > 0) {
        byte* b = InternalAimpObject->GetData();

        array<byte>^ result = gcnew array<unsigned char, 1>(size);

        for (int i = 0; i < size - 1; i++) {
            result[i] = b[i];
        }

        return gcnew AimpActionResult<array<unsigned char>^>(ActionResultType::OK, result);
    }

    return gcnew AimpActionResult<array<unsigned char>^>(ActionResultType::OK);
}

unsigned AimpImageContainer::GetDataSize() {
    return InternalAimpObject->GetDataSize();
}

AimpActionResult^ AimpImageContainer::SetDataSize(long long value) {
    auto const result = CheckResult(InternalAimpObject->SetDataSize(value));
    return gcnew AimpActionResult(result);
}
