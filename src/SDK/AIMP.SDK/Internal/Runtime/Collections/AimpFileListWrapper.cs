using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Runtime.Collections
{
    /// <summary>
    /// v1 <see cref="IAimpFileList"/> over <c>IAIMPMLFileList</c>.
    /// </summary>
    internal sealed class AimpFileListWrapper : AimpObjectWrapper, IAimpFileList
    {
        private readonly IAIMPMLFileListNative _native;
        private readonly IntPtr _pointer;

        public AimpFileListWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPMLFileListNative>(ownedPointer);
        }

        /// <summary>
        /// Borrowed native file list, for adapters.
        /// </summary>
        internal IAIMPMLFileListNative NativeRaw => _native;

        public AimpActionResult Add(object id, string fileName)
        {
            return AddCore(-1, id, fileName);
        }

        public AimpActionResult Insert(int index, object id, string fileName)
        {
            return AddCore(index, id, fileName);
        }

        public AimpActionResult Clear()
        {
            return AimpResult.From(_native.Clear());
        }

        public AimpActionResult Delete(int index)
        {
            return AimpResult.From(_native.Delete(index));
        }

        public int GetCount()
        {
            return _native.GetCount();
        }

        public AimpActionResult<string> GetFileName(int index)
        {
            var hr = _native.GetFileName(index, out var pointer);
            return hr < 0 ? AimpResult.Fail<string>() : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        public AimpActionResult SetFileName(int index, string fileName)
        {
            var pointer = AimpString.CreateNative(fileName);
            try
            {
                return AimpResult.From(_native.SetFileName(index, pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult<object> GetId(int index)
        {
            if (_native.GetID(index, out var pointer) < 0 || pointer == IntPtr.Zero)
            {
                return AimpResult.Fail<object>();
            }

            try
            {
                return AimpResult.Ok(AimpVariant.Read(pointer));
            }
            finally
            {
                // Read() does not own the variant: it is owned by the list.
            }
        }

        public AimpActionResult SetId(int index, object id)
        {
            var pointer = AimpVariant.Alloc(id);
            try
            {
                return AimpResult.From(_native.SetID(index, pointer));
            }
            finally
            {
                AimpVariant.Free(pointer);
            }
        }

        public AimpActionResult<IAimpFileList> Clone()
        {
            var hr = _native.Clone(out var pointer);
            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpFileList>()
                : AimpResult.Ok<IAimpFileList>(new AimpFileListWrapper(pointer));
        }

        private AimpActionResult AddCore(int index, object id, string fileName)
        {
            var identifier = AimpVariant.Alloc(id);
            var name = AimpString.CreateNative(fileName);

            try
            {
                var hr = index < 0
                    ? _native.Add(identifier, name)
                    : _native.Insert(index, identifier, name);

                return AimpResult.From(hr);
            }
            finally
            {
                AimpVariant.Free(identifier);
                AimpComHelper.Release(name);
            }
        }

        protected override void OnDispose()
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}