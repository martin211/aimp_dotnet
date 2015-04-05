namespace AIMP
{
	using namespace System;
	using namespace AIMP::SDK::Infrastructure::PlayList;

	public ref class VirtualFileInfo : public AimpVirtualFileInfo
	{
	public:
		AimpFileInfo^ GetFileInfo() override
		{
			return nullptr;
		}

		bool IsExists() override
		{
			return true;
		}

		bool IsInSameStream() override
		{
			return true;
		}

		void Synchronize() override
		{

		}
	};
}