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

        public ref class AimpPlaylistQueue :
            public AimpObject<IAIMPPlaylistQueue>,
            public IAimpPlayListQueue,
            public IPlayListQueueEventExecutor
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

            virtual void OnContentChanged()
            {
                ContentChanged(this, EventArgs::Empty);
            }

            virtual void OnStateChanged()
            {
                StateChanged(this, EventArgs::Empty);
            }
        private:
            IAIMPPlaylistQueue2 *_queue2;
            EventHandler ^_contentChanged;
            EventHandler ^_stateChanged;
            AimpPlaylistQueueListener* _listner;
        };
    }
}
