using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Threading;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Threading;

namespace AIMP.Internal.Runtime.Threading
{
    /// <summary>
    /// v1 <see cref="IAimpServiceThreads"/>.
    /// </summary>
    internal sealed class AimpServiceThreads(IntPtr borrowedPointer) : AimpObjectWrapper, IAimpServiceThreads
    {
        private readonly IAIMPServiceThreadsNative _native =
            AimpComHelper.WrapBorrowed<IAIMPServiceThreadsNative>(borrowedPointer);

        private readonly Dictionary<ulong, TaskEntry> _tasks = new Dictionary<ulong, TaskEntry>();

        private sealed class TaskEntry
        {
            public AimpTaskBridge Bridge;
            public IntPtr Pointer;
        }

        public bool IsExists => _native != null;

        public AimpActionResult ExecuteInMainThread(IAimpTask task, AimpServiceThreadPoolType flags)
        {
            if (_native == null || task == null)
            {
                return AimpResult.Fail();
            }

            var bridge = new AimpTaskBridge(task);
            var pointer = AimpComHelper.GetPointer(bridge, typeof(IAIMPTaskNative));

            return AimpResult.From(_native.ExecuteInMainThread(pointer, (uint)flags));
        }

        public AimpActionResult<UIntPtr> ExecuteInThread(IAimpTask task)
        {
            if (_native == null || task == null)
            {
                return AimpResult.Fail<UIntPtr>();
            }

            var bridge = new AimpTaskBridge(task);
            var pointer = AimpComHelper.GetPointer(bridge, typeof(IAIMPTaskNative));
            var hr = _native.ExecuteInThread(pointer, out var handle);

            if (hr < 0)
            {
                AimpComHelper.Release(pointer);
                return AimpResult.Fail<UIntPtr>();
            }

            _tasks[ToUInt64(handle)] = new TaskEntry { Bridge = bridge, Pointer = pointer };
            return AimpResult.Ok(handle);
        }

        public AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var result = AimpResult.From(_native.Cancel(taskHandle, (uint)flags));
            Release(taskHandle);
            return result;
        }

        public AimpActionResult WaitFor(UIntPtr taskHandle)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var result = AimpResult.From(_native.WaitFor(taskHandle));
            Release(taskHandle);
            return result;
        }

        private void Release(UIntPtr handle)
        {
            var key = ToUInt64(handle);
            if (_tasks.TryGetValue(key, out var entry))
            {
                _tasks.Remove(key);
                AimpComHelper.Release(entry.Pointer);
            }
        }

        private static ulong ToUInt64(UIntPtr value)
        {
            return value.ToUInt64();
        }

        protected override void OnDispose()
        {
            foreach (var entry in _tasks.Values)
            {
                AimpComHelper.Release(entry.Pointer);
            }

            _tasks.Clear();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}