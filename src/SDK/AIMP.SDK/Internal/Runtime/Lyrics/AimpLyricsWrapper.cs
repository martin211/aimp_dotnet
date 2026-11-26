using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Lyrics;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Lyrics.Objects;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Lyrics
{
    /// <summary>
    /// v1 <see cref="IAimpLyrics"/>.
    /// </summary>
    internal sealed class AimpLyricsWrapper : AimpObjectWrapper, IAimpLyrics, IAimpNativeObject
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPLyricsNative _native;
        private readonly AimpPropertyBag _properties;

        public AimpLyricsWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPLyricsNative>(ownedPointer);
            _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        public string Text
        {
            get => _properties.GetString(AimpPropId.LyricsText);
            set => _properties.SetString(AimpPropId.LyricsText, value);
        }

        public string Author
        {
            get => _properties.GetString(AimpPropId.LyricsLyricist);
            set => _properties.SetString(AimpPropId.LyricsLyricist, value);
        }

        public string Album
        {
            get => _properties.GetString(AimpPropId.LyricsAlbum);
            set => _properties.SetString(AimpPropId.LyricsAlbum, value);
        }

        public string Title
        {
            get => _properties.GetString(AimpPropId.LyricsTitle);
            set => _properties.SetString(AimpPropId.LyricsTitle, value);
        }

        public string Creator
        {
            get => _properties.GetString(AimpPropId.LyricsCreator);
            set => _properties.SetString(AimpPropId.LyricsCreator, value);
        }

        public string Application
        {
            get => _properties.GetString(AimpPropId.LyricsApplication);
            set => _properties.SetString(AimpPropId.LyricsApplication, value);
        }

        public string ApplicationVersion
        {
            get => _properties.GetString(AimpPropId.LyricsApplicationVersion);
            set => _properties.SetString(AimpPropId.LyricsApplicationVersion, value);
        }

        public LyricsType Type
        {
            get => (LyricsType)_properties.GetInt32(AimpPropId.LyricsType);
            set => _properties.SetInt32(AimpPropId.LyricsType, (int)value);
        }

        public int Offset
        {
            get => _properties.GetInt32(AimpPropId.LyricsOffset);
            set => _properties.SetInt32(AimpPropId.LyricsOffset, value);
        }

        public AimpActionResult Assign(IAimpLyrics source)
        {
            var pointer = AimpBridgeHelper.GetPointer(source, typeof(IAIMPLyricsNative));

            try
            {
                return AimpResult.From(_native.Assign(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult<IAimpLyrics> Clone()
        {
            return _native.Clone(out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpLyrics>()
                : AimpResult.Ok<IAimpLyrics>(new AimpLyricsWrapper(pointer));
        }

        public AimpActionResult Add(int timeStart, int timeFinish, string text)
        {
            var pointer = AimpString.CreateNative(text ?? string.Empty);

            try
            {
                return AimpResult.From(_native.Add(timeStart, timeFinish, pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Delete(int index) => AimpResult.From(_native.Delete(index));

        public AimpActionResult<string> Find(int time, int index)
        {
            var hr = _native.Find(time, ref index, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        public AimpActionResult<string> Get(int index, int timeStart, int timeFinish)
        {
            var hr = _native.Get(index, ref timeStart, ref timeFinish, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        public AimpActionResult<int> GetCount()
        {
            return _native.GetCount(out var value) < 0
                ? AimpResult.Fail<int>()
                : AimpResult.Ok(value);
        }

        public AimpActionResult LoadFromFile(string virtualFileName)
        {
            var pointer = AimpString.CreateNative(virtualFileName ?? string.Empty);

            try
            {
                return AimpResult.From(_native.LoadFromFile(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult LoadFromStream(IAimpStream stream, LyricsFormat format)
        {
            var pointer = AimpBridgeHelper.GetStreamPointer(stream);

            try
            {
                return AimpResult.From(_native.LoadFromStream(pointer, (int)format));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult LoadFromString(string lyrics, LyricsFormat format)
        {
            var pointer = AimpString.CreateNative(lyrics ?? string.Empty);

            try
            {
                return AimpResult.From(_native.LoadFromString(pointer, (int)format));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult SaveToFile(string fileUri)
        {
            var pointer = AimpString.CreateNative(fileUri ?? string.Empty);

            try
            {
                return AimpResult.From(_native.SaveToFile(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult SaveToStream(IAimpStream stream, LyricsFormat format)
        {
            var pointer = AimpBridgeHelper.GetStreamPointer(stream);

            try
            {
                return AimpResult.From(_native.SaveToStream(pointer, (int)format));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult<string> SaveToString(LyricsFormat format)
        {
            var hr = _native.SaveToString(out var pointer, (int)format);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        protected override void OnDispose()
        {
            _properties.Dispose();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}