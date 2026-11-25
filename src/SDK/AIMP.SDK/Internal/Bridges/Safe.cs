using System;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Common HRESULT values and exception guards used by the bridges.
    /// </summary>
    internal static class Safe
    {
        public const int S_OK = 0;
        public const int S_FALSE = 1;
        public const int E_NOTIMPL = unchecked((int)0x80004001);
        public const int E_NOINTERFACE = unchecked((int)0x80004002);
        public const int E_FAIL = unchecked((int)0x80004005);
        public const int E_INVALIDARG = unchecked((int)0x80070057);
        public const int E_POINTER = unchecked((int)0x80004003);

        public static int Run(Action action)
        {
            try
            {
                action();
                return S_OK;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return E_FAIL;
            }
        }

        public static int Run(Func<int> action)
        {
            try
            {
                return action();
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return E_FAIL;
            }
        }

        public static T Run<T>(Func<T> action, T fallback)
        {
            try
            {
                return action();
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return fallback;
            }
        }

        public static bool Check(bool condition)
        {
            return condition;
        }
    }
}