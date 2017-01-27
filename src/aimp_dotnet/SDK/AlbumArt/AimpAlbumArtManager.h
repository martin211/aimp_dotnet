/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once

#include "..\BaseManager.h"
#include "..\FileManager\AimpFileInfo.h"

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

            virtual IntPtr GetImage(String^ fileUrl, String^ artist, String^ album, AimpFingCovertArtType flags, Object^ userData);

            virtual IntPtr GetImage(AIMP::SDK::FileManager::IAimpFileInfo^ fileInfo, AimpFingCovertArtType flags, Object^ userData);

            virtual void Cancel(IntPtr taskId, AimpFingCovertArtType flags);
        private:
            delegate void OnFindCoverCallback(IAIMPImage *image, IAIMPImageContainer *imageContainer, void *UserData);
            OnFindCoverCallback^ _findCallback;
            EventHandler<AimpGetAlbumArtEventArgs^>^ _onComplete;
        };
    }
}
