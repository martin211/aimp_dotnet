using System;
using System.IO;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Native <c>IAIMPStream</c> over a managed <see cref="IAimpStream"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class AimpStreamBridge : IAIMPStreamNative
    {
        private readonly IAimpStream _stream;

        public AimpStreamBridge(IAimpStream stream)
        {
            _stream = stream ?? throw new ArgumentNullException(nameof(stream));
        }

        [PreserveSig]
        public long GetSize()
        {
            return Safe.Run(() => _stream.GetSize(), 0L);
        }

        [PreserveSig]
        public int SetSize(long value)
        {
            return Safe.Run(() =>
            {
                var result = _stream.SetSize(value);
                return result == null ? Safe.E_FAIL : (int)result.ResultType;
            });
        }

        [PreserveSig]
        public long GetPosition()
        {
            return Safe.Run(() => _stream.GetPosition(), 0L);
        }

        [PreserveSig]
        public int Seek(long offset, int mode)
        {
            return Safe.Run(() =>
            {
                var result = _stream.Seek(offset, (SeekOrigin)mode);
                return result == null ? Safe.E_FAIL : (int)result.ResultType;
            });
        }

        [PreserveSig]
        public int Read(IntPtr buffer, int count)
        {
            return Safe.Run(() =>
            {
                if (count <= 0)
                {
                    return 0;
                }

                var data = new byte[count];
                var read = _stream.Read(data, count);

                if (read > 0 && buffer != IntPtr.Zero)
                {
                    Marshal.Copy(data, 0, buffer, read);
                }

                return read;
            }, 0);
        }

        [PreserveSig]
        public int Write(IntPtr buffer, int count, out int written)
        {
            var result = 0;

            var hr = Safe.Run(() =>
            {
                if (count <= 0)
                {
                    return Safe.S_OK;
                }

                var data = new byte[count];

                if (buffer != IntPtr.Zero)
                {
                    Marshal.Copy(buffer, data, 0, count);
                }

                var actionResult = _stream.Write(data, count, out result);
                return actionResult == null ? Safe.E_FAIL : (int)actionResult.ResultType;
            });

            written = result;
            return hr;
        }
    }
}