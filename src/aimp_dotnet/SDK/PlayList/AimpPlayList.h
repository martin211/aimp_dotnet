// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "SDK\FileManager\AimpFileInfo.h"
#include "AimpExtensionPlaylistPreimageFactory.h"
#include "SDK/PlayList/Internal/InternalAimpPlaylistPreimage.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace Generic;
        using namespace Runtime::InteropServices;

        using namespace SDK;
        using namespace Playlist;

        public interface class IPlayListListnerExecutor
        {
        public:
            void OnChanged(DWORD flag);

            void OnActivated();

            void OnRemoved();

            void OnScanningBegin();

            void OnScanningProgress(const double progress);

            void OnScanningEnd(bool hasChanges, bool canceled);
        };


        class AimpPlaylistListener :
            public IUnknownInterfaceImpl<IAIMPPlaylistListener>,
            public IAIMPPlaylistListener2
        {
        private:
            gcroot<IPlayListListnerExecutor^> _playList;

        public:
            AimpPlaylistListener(gcroot<IPlayListListnerExecutor^> playList);

            typedef IUnknownInterfaceImpl<IAIMPPlaylistListener> Base;

            virtual void WINAPI Activated();

            virtual void WINAPI Changed(DWORD flags);

            virtual void WINAPI Removed();

            virtual void WINAPI ScanningBegin();

            virtual void WINAPI ScanningProgress(const double Progress);

            virtual void WINAPI ScanningEnd(BOOL HasChanges, BOOL Canceled);

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

            virtual ULONG WINAPI AddRef(void);

            virtual ULONG WINAPI Release(void);
        };

        /// <summary>
        /// 
        /// </summary>
        public ref class AimpPlayList :
            public AimpObject<IAIMPPlaylist>,
            public IAimpPlaylist,
            public IPlayListListnerExecutor
        {
        private:
            Func<IAimpPlaylistItem^, IAimpPlaylistItem^, Object^, PlaylistSortComapreResult>^ _compareFunc;
            Func<IAimpPlaylistItem^, Object^, bool> ^_deleteFilterFunc;
            PlayListChangedHandler ^_onChanged;
            AimpPlayListHandler ^_onActivated;
            AimpPlayListHandler ^_onRemoved;
            AimpPlayListHandler ^_scanningBeginHandler;
            AimpPlayListHandler<ScanningProgressEventArgs^> ^_scanningProgressHandler;
            AimpPlayListHandler<ScanningEndEventArgs^> ^_scanningEndHandler;

            AimpPlaylistListener *_listner = nullptr;
            InternalAimpPlaylistPreimage *_internalPreImage = nullptr;
            bool _disposed;

        internal:
            AimpPlayList(IAimpPlaylist ^item);

        public:
            explicit AimpPlayList(IAIMPPlaylist *aimpPlayList);

            ~AimpPlayList();

            !AimpPlayList();

            virtual property String ^Id
            {
                String ^get();
            }

            virtual property String ^Name
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool ReadOnly
            {
                bool get();
                void set(bool value);
            }

            virtual property Object ^FocusedObject
            {
                Object ^get();
                void set(Object ^value);
            }

            virtual property bool GroupingOverridden
            {
                bool get();
                void set(bool value);
            }

            virtual property bool Grouping
            {
                bool get();
                void set(bool value);
            }

            virtual property bool GroupingAutomerg
            {
                bool get();
                void set(bool value);
            }

            virtual property String ^GroupingTemplate
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool FormatingOverride
            {
                bool get();
                void set(bool value);
            }

            virtual property String ^FormattingLine1Template
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^FormattingLine2Template
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool ViewOverride
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewDuration
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewExpandButtons
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewMarks
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewNumbers
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewAbsoluteNumbers
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewSecondLine
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ViewSwitches
            {
                bool get();
                void set(bool value);
            }

            virtual property int FocusIndex
            {
                int get();
                void set(int value);
            }

            virtual property int PlaybackCursor
            {
                int get();
                void set(int value);
            }

            virtual property int PlayingIndex
            {
                int get();
                void set(int value);
            }

            virtual property double Duration
            {
                double get();
            }

            virtual property double Size
            {
                double get();
            }

            virtual property IAimpPlaylistPreimage ^PreImage
            {
                IAimpPlaylistPreimage ^get();
                void set(IAimpPlaylistPreimage ^value);
            }

            virtual void OnChanged(DWORD flags);

            virtual void OnActivated();

            virtual void OnRemoved();

            virtual void OnScanningBegin();

            virtual void OnScanningProgress(const double progress);

            virtual void OnScanningEnd(bool hasChanges, bool canceled);

        public:
            virtual AimpActionResult Add(IAimpFileInfo^ fileInfo, PlaylistFlags flags, PlaylistFilePosition filePosition);

            virtual AimpActionResult Add(System::String^ fileUrl, PlaylistFlags flags, PlaylistFilePosition filePosition);

            virtual AimpActionResult AddList(System::Collections::Generic::IList<IAimpFileInfo^>^ fileUrlList, PlaylistFlags flags, PlaylistFilePosition filePosition);

            virtual AimpActionResult AddList(System::Collections::Generic::IList<System::String^>^ fileUrlList, PlaylistFlags flags, PlaylistFilePosition filePosition);

            virtual AimpActionResult Delete(IAimpPlaylistItem ^item);

            virtual AimpActionResult Delete(int index);

            virtual AimpActionResult DeleteAll();

            virtual AimpActionResult Delete(PlaylistDeleteFlags deleteFlags, System::Object ^customFilterData, System::Func<IAimpPlaylistItem^, System::Object^, bool> ^filterFunc);

            virtual AimpActionResult Sort(PlaylistSort sort);

            virtual AimpActionResult Sort(Object ^customSortData, Func<IAimpPlaylistItem^, IAimpPlaylistItem^, Object^, PlaylistSortComapreResult>^ compareFunc);

            virtual AimpActionResult Sort(String ^templateString);

            virtual AimpActionResult BeginUpdate();

            virtual AimpActionResult EndUpdate();

            virtual AimpActionResult Close(PlaylistCloseFlag closeFlag);

            virtual AimpActionResult GetFiles(PlaylistGetFilesFlag filesFlag, System::Collections::Generic::IList<String^> ^%files);

            virtual AimpActionResult ReloadFromPreimage();

            virtual AimpActionResult ReloadInfo(bool fullReload);

            virtual IAimpPlaylistItem ^GetItem(int index);

            virtual int GetItemCount();

            virtual IAimpPlaylistGroup ^GetGroup(int index);

            virtual int GetGroupCount();

            virtual AimpActionResult MergeGroup(IAimpPlaylistGroup ^playlistGroup);

            virtual event AimpPlayListHandler ^Activated
            {
                void add(AimpPlayListHandler ^onEvent);
                void remove(AimpPlayListHandler ^onEvent);
                void raise(IAimpPlaylist ^sender);
            }

            virtual event AimpPlayListHandler ^Removed
            {
                void add(AimpPlayListHandler ^onEvent);
                void remove(AimpPlayListHandler ^onEvent);
                void raise(IAimpPlaylist ^sender);
            }

            virtual event PlayListChangedHandler ^Changed
            {
                void add(PlayListChangedHandler ^onEvent);
                void remove(PlayListChangedHandler ^onEvent);
                void raise(IAimpPlaylist ^esnder, PlaylistNotifyType notifyType);
            }

            virtual event AimpPlayListHandler ^ScanningBegin
            {
                void add(AimpPlayListHandler ^onEvent);
                void remove(AimpPlayListHandler ^onEvent);
                void raise(IAimpPlaylist ^sender);
            }

            virtual event AimpPlayListHandler<ScanningProgressEventArgs^> ^ScanningProgress
            {
                void add(AimpPlayListHandler<ScanningProgressEventArgs^> ^onEvent);
                void remove(AimpPlayListHandler<ScanningProgressEventArgs^> ^onEvent);
                void raise(IAimpPlaylist ^sender, ScanningProgressEventArgs^ args);
            }

            virtual event AimpPlayListHandler<ScanningEndEventArgs^> ^ScanningEnd
            {
                void add(AimpPlayListHandler<ScanningEndEventArgs^> ^onEvent);
                void remove(AimpPlayListHandler<ScanningEndEventArgs^> ^onEvent);
                void raise(IAimpPlaylist ^sender, ScanningEndEventArgs^ args);
            }

        private:
            AimpActionResult GetProperties(IAIMPPropertyList** properties);
            AimpFileInfo ^CreateFileInfo(IAimpFileInfo ^fi);

            void RegisterListner();

            delegate int OnSortCallback(IAIMPPlaylistItem *item1, IAIMPPlaylistItem *item2, void *userData);
            delegate bool OnDeleteCallback(IAIMPPlaylistItem *item1, void *customFilterData);
            OnSortCallback ^_sortCallback;
            OnDeleteCallback ^_deleteCallback;

            int OnSortReceive(IAIMPPlaylistItem* item1, IAIMPPlaylistItem* item2, void* userData);

            bool OnDeleteReceive(IAIMPPlaylistItem *item1, void *customFilterData);
        };
    }
}
