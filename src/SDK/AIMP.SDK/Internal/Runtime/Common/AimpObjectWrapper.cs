using System;
using AIMP.SDK;

namespace AIMP.Internal.Runtime.Common
{
    /// <summary>
    /// Common base of every managed wrapper around a native AIMP object.
    /// </summary>
    internal abstract class AimpObjectWrapper : IAimpObject
    {
        private bool _disposed;

        protected virtual void OnDispose()
        {
        }

        public void Dispose()
        {
            if (_disposed)
            {
                return;
            }

            _disposed = true;

            try
            {
                OnDispose();
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
            }
        }

        public override string ToString()
        {
            return GetType().Name;
        }
    }
}