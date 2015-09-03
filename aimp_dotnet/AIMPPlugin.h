#pragma once
#include "Services\MenuManager\ServiceMenuManager.h"
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
					return (IAimpPlayer^) AimpPlayer;
				} 
			}

			property AIMP::SDK::Logger::ILogger ^LoggerManager
			{
				AIMP::SDK::Logger::ILogger ^get()
				{
					return AIMP::SDK::InternalLogger::Instance;
				}
			}

		private:
			ServiceMenuManager^ _menuManager;
		};
	}
}