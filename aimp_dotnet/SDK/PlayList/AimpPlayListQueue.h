#pragma once
#include "AimpPlayListItem.h"
#include "AimpPlayList.h"
#include "AimpPlaylistQueueListener.h"
#include <gcroot.h>

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;

        public ref class AimpPlaylistQueue :
            public AimpObject<IAIMPPlaylistQueue>,
            public IAimpPlayListQueue
        {
        public:
            explicit AimpPlaylistQueue(IAIMPPlaylistQueue *queue, IAIMPPlaylistQueue2 *queue2);

            virtual property bool IsSuspended
            {
                bool get();
                void set(bool value);
            }

            virtual AimpActionResult Add(IAimpPlayListItem^ item, bool insertAtBeginning);

            virtual AimpActionResult AddList(System::Collections::Generic::IList<IAimpPlayListItem^>^ items, bool insertAtBeginning);

            virtual int GetItemCount();

            virtual AimpActionResult Delete(IAimpPlayList^ playList);

            virtual AimpActionResult Delete(IAimpPlayListItem^ item);

            virtual AimpActionResult Move(IAimpPlayListItem^ item, int index);

            virtual AimpActionResult Move(int index, int targetIndex);

            virtual AimpActionResult GetItem(int index, IAimpPlayListItem ^%item);

            virtual event EventHandler ^ContentChanged
            {
                void add(EventHandler ^onEvent);
                void remove(EventHandler ^onEvent);
                void raise(Object ^sender, EventArgs ^args);
            }

            virtual event EventHandler ^StateChanged
            {
                void add(EventHandler ^onEvent);
                void remove(EventHandler ^onEvent);
                void raise(Object ^sender, EventArgs ^args);
            }
        private:
            IAIMPPlaylistQueue2 *_queue2;
            EventHandler ^_contentChanged;
            EventHandler ^_stateChanged;
            AimpPlaylistQueueListener* _listner;

            ConnectionCallback *_contentChangedCallback;
            ConnectionCallback *_stateChangedCallback;
        };
    }
}