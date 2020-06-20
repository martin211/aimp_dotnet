// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AimpSdk.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace Runtime::InteropServices;
        using namespace ActionManager;

        public ref class AimpAction : public AimpObject<IAIMPAction>, public IAimpAction
        {
        private:
            EventHandler^ _onExecuteHandler;
            IAIMPActionEvent* _onExecuteEvent;
            GCHandle _executeHandler;
        public:
            explicit AimpAction(IAIMPAction* action);

            virtual property String^ Id
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ CustomData
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Name
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ GroupName
            {
                String^ get();
                void set(String^ value);
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

            virtual event EventHandler^ OnExecute
            {
                virtual void add(EventHandler^ onEvent);
                virtual void remove(EventHandler^ onEvent);
                virtual void raise(Object^ sender, EventArgs^ args);
            }

        internal:
            static void Execute(gcroot<IAimpActionEvent^> sender, IUnknown* data);

        protected:
            void FreeResources() override;
        };
    }
}
