#using <mscorlib.dll>
#include <msclr/marshal.h>

namespace AIMP
{
	typedef boost::signals::connection Callback;
	typedef boost::signal<void(DWORD, int)> ChangedSignal;
	typedef boost::signal<void(DWORD, int)>::slot_function_type ChangedSignalCB;

	using namespace System;
	using namespace msclr::interop;

	//delegate void ChangeHandler(void);

	class EventHelper
	{
	public:
		Callback RegisterCallback(ChangedSignalCB subscriber)
		{
			return changed.connect(subscriber);
		}

		void UnregisterCallback(Callback callback)
		{
			changed.disconnect(callback);
		}

		void ChangeIt(DWORD param1, int param2)
		{
			changed(param1, param2);
		}

	private:
		ChangedSignal changed;
	};
}