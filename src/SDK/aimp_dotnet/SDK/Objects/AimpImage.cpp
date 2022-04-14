// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpImage.h"

#include "SDK/ManagedAimpCore.h"

AimpImage::AimpImage(IAIMPImage2* obj) : AimpObject<IAIMPImage2>(obj) {
}

AimpImage::AimpImage(IAIMPImage2* obj, ManagedAimpCore^ core) : AimpObject<IAIMPImage2>(obj) {
    _core = core;
}

AimpImageFormat AimpImage::FormatId::get() {
    return static_cast<AimpImageFormat>(InternalAimpObject->GetFormatID());
}

Drawing::PointF AimpImage::Size::get() {
    SIZE* s = new SIZE();
    const auto res = CheckResult(InternalAimpObject->GetSize(s));
    if (res == ActionResultType::OK) {
        const auto result = Drawing::PointF(s->cx, s->cy);
        delete s;
        return result;
    }

    return Drawing::PointF::Empty;
}

AimpActionResult^ AimpImage::LoadFromFile(String^ fileName) {
    if (String::IsNullOrEmpty(fileName)) {
        ARGUMENT_NULL("fileName", "fileName cannot be empty");
    }

    const auto res = CheckResult(InternalAimpObject->LoadFromFile(AimpConverter::ToAimpString(fileName)));
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpImage::LoadFromStream(IAimpStream^ stream) {
    const auto res = CheckResult(InternalAimpObject->LoadFromStream(static_cast<AimpStream^>(stream)->InternalAimpObject));
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpImage::SaveToFile(String^ fileName, AimpImageFormat format) {
    const auto path = AimpConverter::ToAimpString(fileName);
    try {
        const auto res = CheckResult(InternalAimpObject->SaveToFile(path, static_cast<int>(format)));
        return gcnew AimpActionResult(res);
    }
    finally {
        path->Release();
    }
}

AimpActionResult^ AimpImage::SaveToStream(IAimpStream^ stream, AimpImageFormat format) {
    const auto res = CheckResult(InternalAimpObject->SaveToStream(static_cast<AimpStream^>(stream)->InternalAimpObject, static_cast<int>(format)));
    return gcnew AimpActionResult(res);
}

AimpActionResult<IAimpImage^>^ AimpImage::Clone() {
    IAIMPImage2* img = nullptr;
    //_core->GetAimpCore()->CreateObject(IID_IAIMPImage2, reinterpret_cast<void**>(&img));
    //const auto res = CheckResult(InternalAimpObject->Clone(&img));
    //if (res == ActionResultType::OK) {
    //    return gcnew AimpActionResult<IAimpImage^>(res, gcnew AimpImage(img, _core));
    //}

    return gcnew AimpActionResult<IAimpImage^>(ActionResultType::NotImplemented);
}

AimpActionResult^ AimpImage::Draw(IntPtr dc, Drawing::RectangleF rect) {
    RECT r = RECT();
    r.top = rect.Top;
    r.bottom = rect.Bottom;
    r.left = rect.Left;
    r.right = rect.Right;
    //TODO complete
    const auto res = CheckResult(InternalAimpObject->Draw(static_cast<HDC>(dc.ToPointer()), r, 0, nullptr));
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpImage::Resize(int width, int height) {
    const auto res = CheckResult(InternalAimpObject->Resize(width, height));
    return gcnew AimpActionResult(res);
}

AimpActionResult^ AimpImage::LoadFromResource() {
    // TODO: Not implemented
    return gcnew AimpActionResult(ActionResultType::NotImplemented);
}

AimpActionResult^ AimpImage::LoadFromBitmap(IntPtr bitmap) {
    // TODO: Not implemented
    return gcnew AimpActionResult(ActionResultType::NotImplemented);
}

AimpActionResult^ AimpImage::LoadFromBits(RGBQuad bits, int width, int height) {
    // TODO: Not implemented
    return gcnew AimpActionResult(ActionResultType::NotImplemented);
}

AimpActionResult^ AimpImage::CopyToClipboard() {
    return gcnew AimpActionResult(CheckResult(InternalAimpObject->CopyToClipboard()));
}

AimpActionResult^ AimpImage::CanPasteFromClipboard() {
    return gcnew AimpActionResult(CheckResult(InternalAimpObject->CanPasteFromClipboard()));
}

AimpActionResult^ AimpImage::PasteFromClipboard() {
    return gcnew AimpActionResult(CheckResult(InternalAimpObject->PasteFromClipboard()));
}
