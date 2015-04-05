#pragma once

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace System::IO;

		public ref class InternalLogger : public Logger::ILogger
		{
		private:
			static InternalLogger ^_instance;
			Logger::Logger ^_flatLogger;

		public:
			static property InternalLogger ^Instance
			{
				InternalLogger ^get()
				{
					if (_instance == nullptr)
					{
						_instance = gcnew InternalLogger();						
					}

					return _instance;
				}
			}

			void Initialize(String ^directory, String ^fileName)
			{
				_flatLogger = gcnew Logger::Logger();
				_flatLogger->Initialize(directory, fileName);
			}

			void virtual Write(String ^message)
			{
				if (_flatLogger != nullptr)
				{
					_flatLogger->Write(message);
				}
			}

			void virtual Write(Exception ^exception)
			{
				if (_flatLogger != nullptr)
				{
					_flatLogger->Write(exception);
				}
			}

			void virtual Close()
			{
				if (_flatLogger != nullptr)
				{
					_flatLogger->Close();
				}
			}
		};
	}
}