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
#include "..\..\AimpSdk.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Threading;

        public ref class AimpTaskOwner : public AimpObject<IAIMPTaskOwner>, public IAimpTaskOwner
        {
        public:
            explicit AimpTaskOwner(IAIMPTaskOwner *taskOwner);

            virtual property bool IsCanceled
            {
                bool get();
            }
        };
    }
}
