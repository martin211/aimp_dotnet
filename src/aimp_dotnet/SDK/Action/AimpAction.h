/*
* AIMP DotNet SDK
*
* (C) 2017
* Mail: mail4evgeniy@gmail.com
* https://github.com/martin211/aimp_dotnet
*
*/
#pragma once
#include "AimpSdk.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System::Runtime::InteropServices;
        using namespace AIMP::SDK::ActionManager;

        public ref class AimpAction : public AimpObject<IAIMPAction>, public IAimpAction
        {
        private:
            EventHandler ^_onExecuteHandler;
            IAIMPActionEvent *_onExecuteEvent;
            GCHandle _executeHandler;
        public:
            explicit AimpAction(IAIMPAction *action);

            virtual property String ^Id
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^CustomData
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^Name
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^GroupName
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool Enabled
            {
                bool get();
                void set(bool value);
            }

            virtual property int DefaultLocalHotKey
            {
                int get();
                void set(int value);
            }

            virtual property int DefaultGlobalHotKey
            {
                int get();
                void set(int value);
            }

            virtual property int AlternativeGlobalHotKey
            {
                int get();
                void set(int value);
            }

            virtual event EventHandler ^OnExecute
            {
                virtual void add(EventHandler ^onEvent);
                virtual void remove(EventHandler ^onEvent);
                virtual void raise(Object ^sender, EventArgs ^args);
            }

        internal:
            static void Execute(gcroot<AIMP::SDK::ActionManager::IAimpActionEvent^> sender, IUnknown *data)
            {
                Object ^obj = sender;
                AimpAction ^action = dynamic_cast<AimpAction^>(obj);
                action->OnExecute(obj, System::EventArgs::Empty);
            }
        };
    }
}
