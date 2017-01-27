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

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::PlayList;

        public ref class AimpPlayListGroup : public AimpObject<IAIMPPlaylistGroup>, public IAimpPlayListGroup
        {
        private:
            IAimpPlayListItem ^_item;

        public:
            ~AimpPlayListGroup()
            {
                _item = nullptr;
            }
            AimpPlayListGroup();

            explicit AimpPlayListGroup(IAIMPPlaylistGroup *item);

            virtual property System::String^ Name
            {
                System::String^ get();
            }

            virtual property bool Expanded
            {
                bool get();
                void set(bool value);
            }

            virtual property double Duration
            {
                double get();
                void set(double value);
            }

            virtual property int Index
            {
                int get();
            }

            virtual property bool Selected
            {
                bool get();
                void set(bool value);
            }

            virtual property int Count
            {
                int get();
            }

            virtual IAimpPlayListItem ^GetItem(int index);
        };
    }
}
