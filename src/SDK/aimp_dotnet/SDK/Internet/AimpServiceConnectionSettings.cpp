#include "stdafx.h"
#include "AimpServiceConnectionSettings.h"

using namespace AIMP::SDK;

AimpServiceConnectionSettings::AimpServiceConnectionSettings(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceConnectionSettings>(core) {    
}

AimpServiceConnectionSettings::~AimpServiceConnectionSettings() {
}

Internet::ConnectionType AimpServiceConnectionSettings::ConnectionType::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return static_cast<Internet::ConnectionType>(PropertyListExtension::GetInt32(prop, AIMP_SERVICE_CONSET_PROPID_CONNECTION_TYPE));
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return Internet::ConnectionType::SystemDefaults;
}

void AimpServiceConnectionSettings::ConnectionType::set(Internet::ConnectionType value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetInt32(prop, AIMP_SERVICE_CONSET_PROPID_CONNECTION_TYPE, static_cast<int>(value));
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

String^ AimpServiceConnectionSettings::ProxyServer::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return PropertyListExtension::GetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_SERVER);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return String::Empty;
}

void AimpServiceConnectionSettings::ProxyServer::set(String^ value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_SERVER, value);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

String^ AimpServiceConnectionSettings::ProxyPort::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return PropertyListExtension::GetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_PORT);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return String::Empty;
}

void AimpServiceConnectionSettings::ProxyPort::set(String^ value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_PORT, value);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

String^ AimpServiceConnectionSettings::ProxyUserName::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return PropertyListExtension::GetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_USERNAME);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return String::Empty;
}

void AimpServiceConnectionSettings::ProxyUserName::set(String^ value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_USERNAME, value);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

String^ AimpServiceConnectionSettings::ProxyUserPass::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return PropertyListExtension::GetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_USERPASS);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return String::Empty;
}

void AimpServiceConnectionSettings::ProxyUserPass::set(String^ value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetString(prop, AIMP_SERVICE_CONSET_PROPID_PROXY_USERPASS, value);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

int AimpServiceConnectionSettings::TimeOut::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return PropertyListExtension::GetInt32(prop, AIMP_SERVICE_CONSET_PROPID_TIMEOUT);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return 0;
}

void AimpServiceConnectionSettings::TimeOut::set(int value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetInt32(prop, AIMP_SERVICE_CONSET_PROPID_TIMEOUT, value);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

String^ AimpServiceConnectionSettings::UserAgent::get() {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            return PropertyListExtension::GetString(prop, AIMP_SERVICE_CONSET_PROPID_USERAGENT);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }

    return String::Empty;
}

void AimpServiceConnectionSettings::UserAgent::set(String^ value) {
    IAIMPServiceConnectionSettings* service = GetAimpService();
    IAIMPPropertyList* prop = nullptr;

    try {
        if (service != nullptr) {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            PropertyListExtension::SetString(prop, AIMP_SERVICE_CONSET_PROPID_USERAGENT, value);
        }
    }
    finally {
        ReleaseObject(prop);
        ReleaseObject(service);
    }
}

IAIMPServiceConnectionSettings* AimpServiceConnectionSettings::GetAimpService() {
    IAIMPServiceConnectionSettings* service = nullptr;
    GetService(IID_IAIMPServiceConnectionSettings, &service);
    return service;
}
