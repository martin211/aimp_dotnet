using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Threading;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpTaskOwner"/> over a native task owner.
    /// </summary>
    internal sealed class AimpTaskOwnerWrapper : AimpObjectWrapper, IAimpTaskOwner
    {
        private static readonly int IsCanceledSlot = 3 * IntPtr.Size;

        private readonly IntPtr _pointer;

        public AimpTaskOwnerWrapper(IntPtr borrowedPointer)
        {
            _pointer = borrowedPointer;
        }

        public bool IsCanceled
        {
            get
            {
                if (_pointer == IntPtr.Zero)
                {
                    return false;
                }

                // AIMP may pass an internal owner object that does not answer
                // QueryInterface for IID_IAIMPTaskOwner. Call IsCanceled through
                // the vtable instead of creating an RCW via Marshal.
                var vtable = Marshal.ReadIntPtr(_pointer);
                var isCanceled = Marshal.GetDelegateForFunctionPointer<IsCanceledDelegate>(
                    Marshal.ReadIntPtr(vtable, IsCanceledSlot));

                return isCanceled(_pointer) != 0;
            }
        }

        protected override void OnDispose()
        {
        }

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int IsCanceledDelegate(IntPtr self);
    }
}