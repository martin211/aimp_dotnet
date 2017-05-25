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
#include "AimpPlayListItem.h"
#include "AimpPlayList.h"
#include "AimpPlaylistQueueListener.h"
#include "IPlayListQueueEventExecutor.h"
#include <gcroot.h>

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlaylistQueue :
            public AimpObject<IAIMPPlaylistQueue>,
            public IAimpPlaylistQueue,
            public IPlayListQueueEventExecutor
        {
        public:
            explicit AimpPlaylistQueue(IAIMPPlaylistQueue *queue, IAIMPPlaylistQueue2 *queue2);

            virtual property bool IsSuspended
            {
                bool get();
                void set(bool value);
            }

            virtual AimpActionResult Add(IAimpPlaylistItem^ item, bool insertAtBeginning);

            virtual AimpActionResult AddList(System::Collections::Generic::IList<IAimpPlaylistItem^>^ items, bool insertAtBeginning);

            virtual int GetItemCount();

            virtual AimpActionResult Delete(IAimpPlaylist^ playList);

            virtual AimpActionResult Delete(IAimpPlaylistItem^ item);

            virtual AimpActionResult Move(IAimpPlaylistItem^ item, int index);

            virtual AimpActionResult Move(int index, int targetIndex);

            virtual AimpActionResult GetItem(int index, IAimpPlaylistItem ^%item);

            virtual event AimpPlaylistQueueListenerHandler ^ContentChanged
            {
                void add(AimpPlaylistQueueListenerHandler ^onEvent);
                void remove(AimpPlaylistQueueListenerHandler ^onEvent);
                void raise(IAimpPlaylistQueue ^sender);
            }

            virtual event AimpPlaylistQueueListenerHandler ^StateChanged
            {
                void add(AimpPlaylistQueueListenerHandler ^onEvent);
                void remove(AimpPlaylistQueueListenerHandler ^onEvent);
                void raise(IAimpPlaylistQueue ^sender);
            }

            virtual void OnContentChanged()
            {
                ContentChanged(this);
            }

            virtual void OnStateChanged()
            {
                StateChanged(this);
            }
        private:
            IAIMPPlaylistQueue2 *_queue2;
            AimpPlaylistQueueListenerHandler ^_contentChanged;
            AimpPlaylistQueueListenerHandler ^_stateChanged;
            AimpPlaylistQueueListener* _listner;
        };
    }
}
