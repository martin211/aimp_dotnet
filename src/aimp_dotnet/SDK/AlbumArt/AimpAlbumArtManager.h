/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

#include "SDK\BaseManager.h"
#include "SDK\FileManager\AimpFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::IO;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::AlbumArtManager;

        public ref class AimpAlbumArtManager : public AimpBaseManager<IAIMPServiceAlbumArt>, public IAimpAlbumArtManager
        {
        public:
            explicit AimpAlbumArtManager(ManagedAimpCore^ core);

            ~AimpAlbumArtManager();

            event EventHandler<AimpGetAlbumArtEventArgs^>^ Completed
            {
                virtual void add(EventHandler<AimpGetAlbumArtEventArgs^>^ onCompleted)
                {
                    if (this->_onComplete == nullptr)
                    {
                        this->_onComplete = (EventHandler<AimpGetAlbumArtEventArgs^>^)Delegate::Combine(this->_onComplete, onCompleted);
                    }
                }
                virtual void remove(EventHandler<AimpGetAlbumArtEventArgs^>^ onCompleted)
                {
                    delete _onComplete;
                    _onComplete = nullptr;
                }
                void raise(Object^ sender, AimpGetAlbumArtEventArgs^ args)
                {
                    if (_onComplete != nullptr)
                    {
                        _onComplete(sender, args);
                    }
                }
            }

            virtual property bool FindInFiles
            {
                bool get();
                void set(bool value);
            }

            virtual property bool FindInInternet
            {
                bool get();
                void set(bool value);
            }

            virtual property array<System::String^>^ FileMasks
            {
                array<System::String^>^ get();
                void set(array<System::String^>^ val);
            }

            virtual property array<System::String^>^ FileExtensions
            {
                array<System::String^>^ get();
                void set(array<System::String^>^ val);
            }

            virtual property int MaxFileSize
            {
                int get();
                void set(int val);
            }

            void OnAlbumArtReceive(IAIMPImage* image, IAIMPImageContainer* image_container, void* user_data);

            virtual IntPtr GetImage(String^ fileUrl, String^ artist, String^ album, AimpFindCovertArtType flags, Object^ userData);

            virtual IntPtr GetImage(AIMP::SDK::FileManager::IAimpFileInfo^ fileInfo, AimpFindCovertArtType flags, Object^ userData);

            virtual void Cancel(IntPtr taskId, AimpFindCovertArtType flags);
        private:
            delegate void OnFindCoverCallback(IAIMPImage *image, IAIMPImageContainer *imageContainer, void *UserData);
            OnFindCoverCallback^ _findCallback;
            EventHandler<AimpGetAlbumArtEventArgs^>^ _onComplete;
        };
    }
}
