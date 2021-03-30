// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AimpErrorInfo.h"
#include "SDK/AimpExtensionBase.h"
#include "Action/AimpAction.h"
#include "Lyrics/AimpLyrics.h"
#include "Menu/AimpMenuItem.h"
#include "Objects/AimpImage.h"
#include "Objects/AimpMemoryStream.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace SDK;

        [System::Serializable]
        public ref class AimpCore : public IAimpCore {
        private:
            ManagedAimpCore^ _aimpCore;
            bool _disposed;

        public:
            AimpCore(ManagedAimpCore^ core) {
                _aimpCore = core;
            }

            ~AimpCore() {
                Diagnostics::Trace::TraceInformation("Dispose AimpCore");
                Diagnostics::Trace::Flush();
                if (_disposed) {
                    return;
                }

                this->!AimpCore();
                _disposed = true;
            }

            !AimpCore() {
            }

            virtual String^ GetPath(MessageDispatcher::AimpCorePathType pathType) {
                String^ path;
                if (_aimpCore->GetPath(pathType, path) == ActionResultType::OK) {
                    return path;
                }

                return String::Empty;
            }

            virtual AimpActionResult^ SendMessage(MessageDispatcher::AimpCoreMessageType message, int value,
                                                  Object^ obj) {
                return ACTION_RESULT(Utils::CheckResult(_aimpCore->SendMessage(message, value, obj)));
            }

            virtual AimpActionResult^ RegisterExtension(IAimpExtension^ extension) {
                return ACTION_RESULT(
                    Utils::CheckResult(_aimpCore->RegisterExtension(IID_IAIMPOptionsDialogFrame, extension)));
            }

            virtual AimpActionResult^ UnregisterExtension(IAimpExtension^ extension) {
                return ACTION_RESULT(Utils::CheckResult(_aimpCore->UnregisterExtension(extension)));
            }

            virtual StreamResult CreateStream() {
                IAIMPStream* stream = nullptr;
                const auto result = _aimpCore->CreateStream(&stream);
                if (result == ActionResultType::OK && stream != nullptr) {
                    return gcnew AimpActionResult<IAimpStream^>(result, gcnew AimpStream(stream));
                }

                return gcnew AimpActionResult<IAimpStream^>(result, nullptr);
            }

            generic <class TAimpObject>
            virtual AimpActionResult<IAimpObject^>^ CreateObject() {
                const auto t = TAimpObject::typeid;

                const auto core = _aimpCore->GetAimpCore();

                if (t == IAimpStream::typeid) {
                    IAIMPStream* obj = nullptr;
                    IAimpStream^ managed = nullptr;
                    const auto result = Utils::CheckResult(
                        core->CreateObject(IID_IAIMPMemoryStream, reinterpret_cast<void**>(&obj)));

                    if (result == ActionResultType::OK) {
                        managed = gcnew AimpStream(obj);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(result, managed);
                }

                if (t == IAimpAction::typeid) {
                    IAIMPAction* obj = nullptr;
                    IAimpAction^ managed = nullptr;
                    const auto result = Utils::CheckResult(
                        core->CreateObject(IID_IAIMPAction, reinterpret_cast<void**>(&obj)));

                    if (result == ActionResultType::OK) {
                        managed = gcnew AimpAction(obj);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(result, managed);
                }

                if (t == IAimpFileInfo::typeid) {
                    IAIMPFileInfo* obj = nullptr;
                    IAimpFileInfo^ managed = nullptr;
                    const auto result = Utils::CheckResult(
                        core->CreateObject(IID_IAIMPFileInfo, reinterpret_cast<void**>(&obj)));

                    if (result == ActionResultType::OK) {
                        managed = gcnew AimpFileInfo(obj);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(result, managed);
                }

                if (t == IAimpLyrics::typeid) {
                    IAIMPLyrics* obj = nullptr;
                    IAimpLyrics^ managed = nullptr;
                    const auto result = Utils::CheckResult(
                        core->CreateObject(IID_IAIMPLyrics, reinterpret_cast<void**>(&obj)));

                    if (result == ActionResultType::OK) {
                        managed = gcnew AimpLyrics(obj);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(result, managed);
                }

                if (t == IAimpMenuItem::typeid) {
                    IAIMPMenuItem* obj = nullptr;
                    IAimpMenuItem^ managed = nullptr;
                    const auto result = Utils::CheckResult(
                        core->CreateObject(IID_IAIMPMenuItem, reinterpret_cast<void**>(&obj)));

                    if (result == ActionResultType::OK) {
                        managed = gcnew AimpMenuItem(obj);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(result, managed);
                }

                if (t == IAimpErrorInfo::typeid) {
                    IAIMPErrorInfo* obj = nullptr;
                    IAimpErrorInfo^ m = nullptr;
                    const auto result = Utils::CheckResult(
                        core->CreateObject(IID_IAIMPErrorInfo, reinterpret_cast<void**>(&obj)));

                    if (result == ActionResultType::OK) {
                        m = gcnew AimpErrorInfo(obj);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(result, m);
                }

                if (t == IAimpImage::typeid) {
                    IAIMPImage2* obj = nullptr;
                    IAimpImage^ img = nullptr;

                    const auto res = Utils::CheckResult(core->CreateObject(IID_IAIMPImage2, reinterpret_cast<void**>(&obj)));
                    if (res == ActionResultType::OK) {
                        img = gcnew AimpImage(obj, _aimpCore);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(res, img);
                }

                if (t == Objects::IAimpMemoryStream::typeid) {
                    IAIMPMemoryStream* stream = nullptr;
                    Objects::IAimpMemoryStream^ obj = nullptr;

                    const auto res = Utils::CheckResult(core->CreateObject(IID_IAIMPMemoryStream, reinterpret_cast<void**>(&stream)));
                    if (res == ActionResultType::OK) {
                        obj = gcnew Objects::AimpMemoryStream(stream);
                    }

                    return gcnew AimpActionResult<IAimpObject^>(res, obj);
                }

                return nullptr;
            }
        };
    }
}
