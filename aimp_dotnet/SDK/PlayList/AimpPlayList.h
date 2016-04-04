#pragma once
#include "AimpPlayListItem.h"
#include "..\..\IUnknownInterfaceImpl.h"
#include "AimpFileInfo.h"

namespace AIMP
{
    typedef boost::signals::connection ConnectionCallback;
    typedef boost::signal<void(void)> VoidSignal;
    typedef boost::signal<void(int)> IntSignal;
    typedef boost::signal<void(double)> DoubleSignal;
    typedef boost::signal<void(BOOL, BOOL)> ScanningEndSignal;

    typedef boost::signal<void(void)>::slot_function_type VoidSignalCB;
    typedef boost::signal<void(double)>::slot_function_type DoubleSignalCB;
    typedef boost::signal<void(int)>::slot_function_type DwordSignalCB;
    typedef boost::signal<void(BOOL, BOOL)>::slot_function_type  ScanningEndSignalCB;

    namespace SDK
    {
        using namespace System;
        using namespace System::Collections::Generic;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        class AimpPlaylistListener :
            public IUnknownInterfaceImpl<IAIMPPlaylistListener>, 
            public IAIMPPlaylistListener2
        {
        private:
            IntSignal _changed;
            VoidSignal _activated;
            VoidSignal _removed;
            VoidSignal _scanningBegin;
            DoubleSignal _scanningProgress;
            ScanningEndSignal _scanningEnd;

        public:
            typedef IUnknownInterfaceImpl<IAIMPPlaylistListener> Base;

            ConnectionCallback RegisterActivatedCallback(VoidSignalCB subscriber)
            {
                return _activated.connect(subscriber);
            }

            ConnectionCallback RegisterRemovedCallback(VoidSignalCB subscriber)
            {
                return _removed.connect(subscriber);
            }

            ConnectionCallback RegisterChangedCallback(DwordSignalCB subscriber)
            {
                return _changed.connect(subscriber);
            }

            ConnectionCallback RegisterScanningBeginCallback(VoidSignalCB subscriber)
            {
                return _scanningBegin.connect(subscriber);
            }

            ConnectionCallback RegisterScanningProgress(DoubleSignalCB subscriber)
            {
                return _scanningProgress.connect(subscriber);
            }

            ConnectionCallback RegisterScanningEnd(ScanningEndSignalCB subscriber)
            {
                return _scanningEnd.connect(subscriber);
            }

            void UregisterActivatedCallback(ConnectionCallback *activatedCallback)
            {
                _activated.disconnect(activatedCallback);
            }

            void UnregisterRemoveCallback(ConnectionCallback *removedCallback)
            {
                _removed.disconnect(removedCallback);
            }

            void UnregisterChangedCallback(ConnectionCallback *changedCallback)
            {
                _changed.disconnect(changedCallback);
            }

            void UnregisterScanningBeginCallback(ConnectionCallback *cb)
            {
                _scanningBegin.disconnect(cb);
            }

            void UnregisterScanningProgress(ConnectionCallback *cb)
            {
                _scanningProgress.disconnect(cb);
            }

            void UnregisterScanningEnd(ConnectionCallback *cb)
            {
                _scanningEnd.disconnect(cb);
            }

            virtual void WINAPI Activated()
            {
                _activated();
            }

            virtual void WINAPI Changed(DWORD flags)
            {
                _changed(flags);
            }

            virtual void WINAPI Removed()
            {
                _removed();
            }

            virtual void WINAPI ScanningBegin()
            {
                _scanningBegin();
            }

            virtual void WINAPI ScanningProgress(const double Progress)
            {
                _scanningProgress(Progress);
            }

            virtual void WINAPI ScanningEnd(BOOL HasChanges, BOOL Canceled)
            {
                _scanningEnd(HasChanges, Canceled);
            }

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
            {
                if (riid == IID_IAIMPPlaylistListener)
                {
                    *ppvObject = this;
                    AddRef();
                    return S_OK;
                }

                if (riid == IID_IAIMPPlaylistListener2)
                {
                    *ppvObject = static_cast<IAIMPPlaylistListener2*>(this);
                    AddRef();
                    return S_OK;
                }

                ppvObject = NULL;
                return E_NOTIMPL;
            }

            virtual ULONG WINAPI AddRef(void)
            {
                return Base::AddRef();
            }

            virtual ULONG WINAPI Release(void)
            {
                return Base::Release();
            }
        };

        /// <summary>
        /// 
        /// </summary>
        public ref class AimpPlayList : public AimpObject<IAIMPPlaylist>, public IAimpPlayList
        {
        private:
            Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ _compareFunc;
            PlayListChangedHandler ^_onChanged;
            AimpPlayListHandler ^_onActivated;
            AimpPlayListHandler ^_onRemoved;
            AimpPlayListHandler ^_scanningBeginHandler;
            AimpPlayListHandler<ScanningProgressEventArgs^> ^_scanningProgressHandler;
            AimpPlayListHandler<ScanningEndEventArgs^> ^_scanningEndHandler;

            AimpPlaylistListener *_listner;
            ConnectionCallback *_activatedCallback;
            ConnectionCallback *_removedCallBack;
            ConnectionCallback *_changedCallBack;
            ConnectionCallback *_scanningBeginCallBack;
            ConnectionCallback *_scanningProgressCallBack;
            ConnectionCallback *_scanningEndCallBack;

            bool _disposed;

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

            virtual property bool GrouppingOvveriden
            {
                bool get();
                void set(bool value);
            }

            virtual property bool Groupping
            {
                bool get();
                void set(bool value);
            }

            virtual property String ^GrouppingTemplate
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool GrouppingAutomerging
            {
                bool get();
                void set(bool value);
            }

            virtual property bool FormatingOverride
            {
                bool get();
                void set(bool value);
            }

            virtual property String ^FirstLineTemplate
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^SecondLineTemplate
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool ViewOverride
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowDuration
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowExpandButtons
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowMarks
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowNumbers
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowAbsoluteNumbers
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowSecondLine
            {
                bool get();
                void set(bool value);
            }

            virtual property bool ShowSwitches
            {
                bool get();
                void set(bool value);
            }

            virtual property int SelectedIndex
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

            virtual property String ^PreImage
            {
                String ^get();
                void set(String ^value);
            }

        public:
            virtual AimpActionResult Add(IAimpFileInfo^ fileInfo, PlayListFlags flags, PlayListFilePosition filePosition);

            virtual AimpActionResult Add(System::String^ fileUrl, PlayListFlags flags, PlayListFilePosition filePosition);

            virtual AimpActionResult AddList(System::Collections::Generic::IList<IAimpFileInfo^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

            virtual AimpActionResult AddList(System::Collections::Generic::IList<System::String^>^ fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

            virtual AimpActionResult Delete(IAimpPlayListItem ^item);

            virtual AimpActionResult Delete(int index);

            virtual AimpActionResult DeleteAll();

            virtual AimpActionResult Sort(PlayListSort sort);

            virtual AimpActionResult Sort(System::Func<IAimpPlayListItem^, IAimpPlayListItem^, PlayListSortComapreResult>^ compareFunc);

            virtual AimpActionResult BeginUpdate();

            virtual AimpActionResult EndUpdate();

            virtual AimpActionResult Close(PlayListCloseFlag closeFlag);

            virtual System::Collections::Generic::IList<String^>^ GetFiles(PlayListGetFilesFlag filesFlag);

            virtual AimpActionResult ReloadFromPreimage();

            virtual AimpActionResult ReloadInfo(bool fullReload);

            virtual IAimpPlayListItem ^GetItem(int index);

            virtual int GetItemCount();

            virtual IAimpPlayListGroup ^GetGroup(int index);

            virtual int GetGroupCount();

            virtual event AimpPlayListHandler ^Activated
            {
                void add(AimpPlayListHandler ^onEvent);
                void remove(AimpPlayListHandler ^onEvent);
                void raise(IAimpPlayList ^sender);
            }

            virtual event AimpPlayListHandler ^Removed
            {
                void add(AimpPlayListHandler ^onEvent);
                void remove(AimpPlayListHandler ^onEvent);
                void raise(IAimpPlayList ^sender);
            }

            virtual event PlayListChangedHandler ^Changed
            {
                void add(PlayListChangedHandler ^onEvent);
                void remove(PlayListChangedHandler ^onEvent);
                void raise(IAimpPlayList ^esnder, PlayListNotifyType notifyType);
            }

            virtual event AimpPlayListHandler ^ScanningBegin
            {
                void add(AimpPlayListHandler ^onEvent);
                void remove(AimpPlayListHandler ^onEvent);
                void raise(IAimpPlayList ^sender);
            }

            virtual event AimpPlayListHandler<ScanningProgressEventArgs^> ^ScanningProgress
            {
                void add(AimpPlayListHandler<ScanningProgressEventArgs^> ^onEvent);
                void remove(AimpPlayListHandler<ScanningProgressEventArgs^> ^onEvent);
                void raise(IAimpPlayList ^sender, ScanningProgressEventArgs^ args);
            }

            virtual event AimpPlayListHandler<ScanningEndEventArgs^> ^ScanningEnd
            {
                void add(AimpPlayListHandler<ScanningEndEventArgs^> ^onEvent);
                void remove(AimpPlayListHandler<ScanningEndEventArgs^> ^onEvent);
                void raise(IAimpPlayList ^sender, ScanningEndEventArgs^ args);
            }

            virtual void Release();

        private:
            AimpActionResult GetProperties(IAIMPPropertyList** properties);
            AimpFileInfo ^CreateFileInfo(IAimpFileInfo ^fi);

            void RegisterListner();

            delegate int OnSortCallback(IAIMPPlaylistItem* item1, IAIMPPlaylistItem* item2, void* userData);
            OnSortCallback^ _sortCallback;

            int OnSortReceive(IAIMPPlaylistItem* item1, IAIMPPlaylistItem* item2, void* userData)
            {
                System::Diagnostics::Debugger::Break();
                PWCHAR sp = (PWCHAR)userData;
                //delete sp;
                return (int)_compareFunc(gcnew AimpPlayListItem(item1), gcnew AimpPlayListItem(item2));
            }
        };
    }
}