#pragma once
#include "SDK\Menu\AimpMenuManager.h"
#include "InternalLogger.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;        
        using namespace AIMP::SDK::Services::Player;
        using namespace AIMP::SDK::Interfaces;

        public ref class AimpPlugin abstract : public AimpPluginBase
        {
        public:
            AimpPlugin()
            {
            }

            property IAimpCore^ AimpCore
            {
                IAimpCore^ get()
                {
                    return Player->Core;
                }
            }

            property IAimpPlayer^ Player
            {
                IAimpPlayer^ get()
                {
                    return (IAimpPlayer^)AimpPlayer;
                }
            }

            property AIMP::SDK::Logger::ILogger ^LoggerManager
            {
                AIMP::SDK::Logger::ILogger ^get()
                {
                    return AIMP::SDK::InternalLogger::Instance;
                }
            }

            //property IAimpMenuManager^ MenuManager
            //{
            //    IAimpMenuManager^ get()
            //    {
            //        if (_menuManager == nullptr)
            //        {
            //            _menuManager = gcnew AimpMenuManager(_core);
            //        }

            //        return _menuManager;
            //    }
            //}

        //private:
        //    AimpMenuManager^ _menuManager;
        //    ManagedAimpCore ^_core;
        };
    }
}