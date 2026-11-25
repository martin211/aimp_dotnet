using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Objects;

namespace AIMP.Internal
{
    /// <summary>
    /// Wrapper around a native <c>IAIMPFileInfo</c>.
    /// </summary>
    internal sealed class AimpFileInfo : IDisposable
    {
        private readonly IAIMPFileInfoNative _native;
        private readonly AimpPropertyBag _properties;

        /// <summary>
        /// Wraps a pointer taking ownership of the reference.
        /// </summary>
        public AimpFileInfo(IntPtr pointer)
        {
            Pointer = pointer;
            _native = AimpComHelper.Wrap<IAIMPFileInfoNative>(pointer);
            _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
        }

        /// <summary>
        /// Wraps a pointer owned by native code.
        /// </summary>
        public static AimpFileInfo FromBorrowed(IntPtr pointer)
        {
            return pointer == IntPtr.Zero ? null : new AimpFileInfo(AimpComHelper.AddRef(pointer));
        }

        internal IntPtr Pointer { get; }

        public string Album
        {
            get => GetString(AimpPropId.FileInfoAlbum);
            set => SetString(AimpPropId.FileInfoAlbum, value);
        }

        public string AlbumArtist
        {
            get => GetString(AimpPropId.FileInfoAlbumArtist);
            set => SetString(AimpPropId.FileInfoAlbumArtist, value);
        }

        public string Artist
        {
            get => GetString(AimpPropId.FileInfoArtist);
            set => SetString(AimpPropId.FileInfoArtist, value);
        }

        public string Comment
        {
            get => GetString(AimpPropId.FileInfoComment);
            set => SetString(AimpPropId.FileInfoComment, value);
        }

        public string FileName
        {
            get => GetString(AimpPropId.FileInfoFileName);
            set => SetString(AimpPropId.FileInfoFileName, value);
        }

        public string Genre
        {
            get => GetString(AimpPropId.FileInfoGenre);
            set => SetString(AimpPropId.FileInfoGenre, value);
        }

        public string Title
        {
            get => GetString(AimpPropId.FileInfoTitle);
            set => SetString(AimpPropId.FileInfoTitle, value);
        }

        public int BitRate
        {
            get => _properties.GetInt32(AimpPropId.FileInfoBitRate);
            set => _properties.SetInt32(AimpPropId.FileInfoBitRate, value);
        }

        public double Duration
        {
            get => _properties.GetFloat(AimpPropId.FileInfoDuration);
            set => _properties.SetFloat(AimpPropId.FileInfoDuration, value);
        }

        public long FileSize
        {
            get => _properties.GetInt64(AimpPropId.FileInfoFileSize);
            set => _properties.SetInt64(AimpPropId.FileInfoFileSize, value);
        }

        public string GetString(int propertyId)
        {
            return _properties.GetString(propertyId);
        }

        public void SetString(int propertyId, string value)
        {
            _properties.SetString(propertyId, value);
        }

        public int GetInt32(int propertyId)
        {
            return _properties.GetInt32(propertyId);
        }

        public void SetInt32(int propertyId, int value)
        {
            _properties.SetInt32(propertyId, value);
        }

        public void BeginUpdate()
        {
            _properties.BeginUpdate();
        }

        public void EndUpdate()
        {
            _properties.EndUpdate();
        }

        public void Assign(AimpFileInfo source)
        {
            if (source != null)
            {
                _native.Assign(source.Pointer);
            }
        }

        public void Dispose()
        {
            _properties.Dispose();
            Marshal.FinalReleaseComObject(_native);
        }
    }
}