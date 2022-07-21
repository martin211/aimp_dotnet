#include "stdafx.h"
#include "AimpServiceFileInfoFormatterUtils.h"

#include "SDK/Action/AimpActionEvent.h"

AimpServiceFileInfoFormatterUtils::AimpServiceFileInfoFormatterUtils(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileInfoFormatterUtils>(core) {
}

AimpActionResult^ AimpServiceFileInfoFormatterUtils::ShowMacrosLegend(RectangleF screenTarget, IAimpActionEvent^ actionEvent) {
    auto service = GetAimpService();

    try {
        if (service != nullptr) {
            RECT r = RECT();
            r.top = screenTarget.Top;
            r.bottom = screenTarget.Bottom;
            r.left = screenTarget.Left;
            r.right = screenTarget.Right;

            AimpActionEvent* action = nullptr;

            if (actionEvent != nullptr) {
                action = new AimpActionEvent(actionEvent);
            }

            const auto result = CheckResult(service->ShowMacrosLegend(r, 0, action));

            return gcnew AimpActionResult(result);
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult(ActionResultType::Fail);
}

IAIMPServiceFileInfoFormatterUtils* AimpServiceFileInfoFormatterUtils::GetAimpService() {
    IAIMPServiceFileInfoFormatterUtils* service = nullptr;
    GetService(IID_IAIMPServiceFileInfoFormatterUtils, &service);
    return service;
}
