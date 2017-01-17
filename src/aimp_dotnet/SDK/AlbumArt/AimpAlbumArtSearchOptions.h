#pragma once

namespace AIMP
{
    namespace SDK
    {
        ref class AimpAlbumArtSearchOptions : public AIMP::SDK::AlbumArtManager::IAimpAlbumArtSearchOptions
        {
        private:
            bool _findInFiles;
            IAIMPPropertyList *_properties;
            IAIMPCore *_core;

        public:
            AimpAlbumArtSearchOptions(IAIMPPropertyList *properties, IAIMPCore* core)
            {
                _properties = properties;
                _core = core;
                _findInFiles = false;
            }

            virtual property bool FindInFiles
            {
                bool get()
                {
                    int val;
                    _properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, &val);
                    return val != 0;
                }
                void set(bool value)
                {
                    _properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, value);
                }
            }

            virtual property bool FindInInternet
            {
                bool get()
                {
                    int val;
                    _properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, &val);
                    return false;
                }
                void set(bool value)
                {
                    _properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value);
                }
            }

            virtual property array<System::String^>^ FileMasks
            {
                array<System::String^>^ get()
                {
                    IAIMPString *str;
                    _properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString, (void**)&str);
                    String^ result = gcnew String(str->GetData());
                    str->Release();
                    return result->Split(gcnew array<WCHAR>{';'}, System::StringSplitOptions::RemoveEmptyEntries);
                }
                void set(array<System::String^>^ val)
                {
                    String^ str;
                    for (int i = 0; i < val->Length; i++)
                    {
                        str += val[i] + ";";
                    }
                    _properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, AimpExtension::GetAimpString(str));
                }
            }

            virtual property array<System::String^>^ FileExtensions
            {
                array<System::String^>^ get()
                {
                    IAIMPString *str;
                    _properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString, (void**)&str);
                    String^ result = gcnew String(str->GetData());
                    str->Release();
                    return result->Split(gcnew array<WCHAR>{';'}, System::StringSplitOptions::RemoveEmptyEntries);
                }
                void set(array<System::String^>^ val)
                {
                    String^ str;
                    for (int i = 0; i < val->Length; i++)
                    {
                        str += val[i] + ";";
                    }
                    IAIMPString *s = AimpExtension::GetAimpString(str);
                    _properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, s);
                    s->Release();
                }
            }

            virtual property int MaxFileSize
            {
                int get()
                {
                    return 0;
                }
                void set(int val)
                {
                }
            }
        };
    }
}
