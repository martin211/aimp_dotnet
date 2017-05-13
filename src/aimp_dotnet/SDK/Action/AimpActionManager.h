/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System::Windows::Input;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::UI::ActionItem;
        using namespace AIMP::SDK::ActionManager;

        public ref class AimpActionManager :
            public AimpBaseManager<IAIMPServiceActionManager>,
            public IAimpActionManager,
            public IAimpServiceActionManager
        {
        public:
            explicit AimpActionManager(ManagedAimpCore^ core);

            ~AimpActionManager();

            virtual void Add(AimpActionItem ^action);

            virtual void AddRange(ActionItemCollection ^actions);

            virtual AimpActionResult GetById(String ^id, IAimpAction ^%action);

            virtual int MakeHotkey(ModifierKeys modifiers, unsigned int key);
        private:
            void RegisterAction(AimpActionItem^ menuItem);

            void OnPropertyChanged(System::Object ^sender, System::ComponentModel::PropertyChangedEventArgs ^e);

            void UpdateItem(AimpActionItem^ menuItem);
        };
    }
}
