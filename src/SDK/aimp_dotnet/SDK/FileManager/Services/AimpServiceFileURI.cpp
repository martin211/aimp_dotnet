#include "stdafx.h"
#include "AimpServiceFileURI.h"

AimpServiceFileURI::AimpServiceFileURI(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileURI>(core) {
}

IAIMPServiceFileURI* AimpServiceFileURI::GetAimpService() {
    IAIMPServiceFileURI* service = nullptr;
    GetService(IID_IAIMPServiceFileURI, &service);
    return service;
}

AimpActionResult<String^>^ AimpServiceFileURI::Build(String^ containerName, String^ partName) {
    const auto service = GetAimpService();
    IAIMPString* container = nullptr;
    IAIMPString* part = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* fileUri = nullptr;

    try {
        container = AimpConverter::ToAimpString(containerName);
        part = AimpConverter::ToAimpString(partName);

        result = CheckResult(service->Build(container, part, &fileUri));
        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(fileUri));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(container);
        ReleaseObject(part);
    }

    return gcnew AimpActionResult<String^>(result);
}

AimpActionResult<Tuple<String^, String^>^>^ AimpServiceFileURI::Parse(String^ fileUri) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString *file = AimpConverter::ToAimpString(fileUri);
    IAIMPString* containerName = nullptr;
    IAIMPString* partName = nullptr;

    try {
        result = CheckResult(service->Parse(file, &containerName, &partName));

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<Tuple<String^, String^>^>(result, gcnew Tuple<String^, String^>(
                AimpConverter::ToManagedString(containerName),
                AimpConverter::ToManagedString(partName))
                );
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(containerName);
        ReleaseObject(partName);
    }

    return gcnew AimpActionResult<Tuple<String^, String^>^>(result);
}

AimpActionResult^ AimpServiceFileURI::ChangeFileExt(String^ fileUri, String^ extension, FileUriFlag flag) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;
    IAIMPString* newExt = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);
        newExt = AimpConverter::ToAimpString(extension);

        result = CheckResult(service->ChangeFileExt(&file, newExt, static_cast<DWORD>(flag)));

        return gcnew AimpActionResult(result);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(newExt);
    }
}

AimpActionResult<String^>^ AimpServiceFileURI::ExtractFileExt(String^ fileUri, FileUriFlag flag) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;
    IAIMPString* ext = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);

        result = CheckResult(service->ExtractFileExt(file, &ext, static_cast<DWORD>(flag)));

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(ext));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(ext);
    }

    return gcnew AimpActionResult<String^>(result);
}

AimpActionResult<String^>^ AimpServiceFileURI::ExtractFileName(String^ fileUri) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;
    IAIMPString* fileName = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);

        result = CheckResult(service->ExtractFileName(file, &fileName));

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(fileName));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(fileName);
    }

    return gcnew AimpActionResult<String^>(result);
}

AimpActionResult<String^>^ AimpServiceFileURI::ExtractFileParentDirName(String^ fileUri) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;
    IAIMPString* name = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);

        result = CheckResult(service->ExtractFileParentDirName(file, &name));

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(name));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(name);
    }

    return gcnew AimpActionResult<String^>(result);
}

AimpActionResult<String^>^ AimpServiceFileURI::ExtractFileParentName(String^ fileUri) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;
    IAIMPString* name = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);

        result = CheckResult(service->ExtractFileParentName(file, &name));

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(name));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(name);
    }

    return gcnew AimpActionResult<String^>(result);
}

AimpActionResult<String^>^ AimpServiceFileURI::ExtractFilePath(String^ fileUri) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;
    IAIMPString* name = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);

        result = CheckResult(service->ExtractFilePath(file, &name));

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(name));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(name);
    }

    return gcnew AimpActionResult<String^>(result);
}

AimpActionResult^ AimpServiceFileURI::IsURL(String^ fileUri) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* file = nullptr;

    try {
        file = AimpConverter::ToAimpString(fileUri);

        result = CheckResult(service->IsURL(file));
        return gcnew AimpActionResult(result);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
    }
}
