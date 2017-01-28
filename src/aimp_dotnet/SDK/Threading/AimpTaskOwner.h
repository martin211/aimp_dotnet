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