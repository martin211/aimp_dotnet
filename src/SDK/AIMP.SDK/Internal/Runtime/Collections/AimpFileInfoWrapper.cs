using System;
using System.Drawing;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.Internal.Runtime.Collections;

/// <summary>
/// v1 <see cref="IAimpFileInfo"/> on top of <c>IAIMPFileInfo</c>.
/// </summary>
internal class AimpFileInfoWrapper : AimpObjectWrapper, IAimpFileInfo, IAimpNativeObject
{
    private static class Id
    {
        public const int Custom = 0;
        public const int Album = 1;
        public const int AlbumArt = 2;
        public const int AlbumArtist = 3;
        public const int AlbumGain = 4;
        public const int AlbumPeak = 5;
        public const int Artist = 6;
        public const int BitRate = 7;
        public const int Bpm = 8;
        public const int Channels = 9;
        public const int Comment = 10;
        public const int Composer = 11;
        public const int Copyright = 12;
        public const int CueSheet = 13;
        public const int Date = 14;
        public const int DiskNumber = 15;
        public const int DiskTotal = 16;
        public const int Duration = 17;
        public const int FileName = 18;
        public const int FileSize = 19;
        public const int Genre = 20;
        public const int Lyrics = 21;
        public const int DisplayingMark = 22;
        public const int Publisher = 23;
        public const int SampleRate = 24;
        public const int Title = 25;
        public const int TrackGain = 26;
        public const int TrackNumber = 27;
        public const int TrackPeak = 28;
        public const int TrackTotal = 29;
        public const int Url = 30;
        public const int BitDepth = 31;
        public const int Codec = 32;
        public const int Conductor = 33;
        public const int Mood = 34;
        public const int Catalog = 35;
        public const int Isrc = 36;
        public const int Lyricist = 37;
        public const int EncodedBy = 38;
        public const int Rating = 39;
        public const int MlAddingDate = 40;
        public const int MlLastPlayDate = 41;
        public const int MlMark = 42;
        public const int MlPlayCount = 43;
        public const int MlRating = 44;
    }

    private readonly IAIMPFileInfoNative _native;
    private readonly AimpPropertyBag _properties;

    public AimpFileInfoWrapper(IntPtr ownedPointer)
    {
        _native = AimpComHelper.Wrap<IAIMPFileInfoNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)_native);
    }

    public IntPtr NativePointer
    {
        get
        {
            var unknown = Marshal.GetIUnknownForObject(_native);
            try
            {
                var iid = AimpIids.IAIMPFileInfo;
                return Marshal.QueryInterface(unknown, ref iid, out var pointer) < 0
                    ? IntPtr.Zero
                    : pointer;
            }
            finally
            {
                Marshal.Release(unknown);
            }
        }
    }

    private string GetString(int id) => _properties.GetString(id);

    private void SetString(int id, string value) => _properties.SetString(id, value);

    private int GetInt(int id) => _properties.GetInt32(id);

    private void SetInt(int id, int value) => _properties.SetInt32(id, value);

    private double GetDouble(int id) => _properties.GetFloat(id);

    private void SetDouble(int id, double value) => _properties.SetFloat(id, value);

    public string CustomData
    {
        get => GetString(Id.Custom);
        set => SetString(Id.Custom, value);
    }

    public string Album
    {
        get => GetString(Id.Album);
        set => SetString(Id.Album, value);
    }

    public string AlbumArtist
    {
        get => GetString(Id.AlbumArtist);
        set => SetString(Id.AlbumArtist, value);
    }

    public double AlbumGain
    {
        get => GetDouble(Id.AlbumGain);
        set => SetDouble(Id.AlbumGain, value);
    }

    public double AlbumPeak
    {
        get => GetDouble(Id.AlbumPeak);
        set => SetDouble(Id.AlbumPeak, value);
    }

    public string Artist
    {
        get => GetString(Id.Artist);
        set => SetString(Id.Artist, value);
    }

    public int BitRate
    {
        get => GetInt(Id.BitRate);
        set => SetInt(Id.BitRate, value);
    }

    public int BitDepth
    {
        get => GetInt(Id.BitDepth);
        set => SetInt(Id.BitDepth, value);
    }

    public int BPM
    {
        get => GetInt(Id.Bpm);
        set => SetInt(Id.Bpm, value);
    }

    public int Channels
    {
        get => GetInt(Id.Channels);
        set => SetInt(Id.Channels, value);
    }

    public string Codec
    {
        get => GetString(Id.Codec);
        set => SetString(Id.Codec, value);
    }

    public string Comment
    {
        get => GetString(Id.Comment);
        set => SetString(Id.Comment, value);
    }

    public string Composer
    {
        get => GetString(Id.Composer);
        set => SetString(Id.Composer, value);
    }

    public string CopyRight
    {
        get => GetString(Id.Copyright);
        set => SetString(Id.Copyright, value);
    }

    public string CUESheet
    {
        get => GetString(Id.CueSheet);
        set => SetString(Id.CueSheet, value);
    }

    public string Date
    {
        get => GetString(Id.Date);
        set => SetString(Id.Date, value);
    }

    public string DiskNumber
    {
        get => GetString(Id.DiskNumber);
        set => SetString(Id.DiskNumber, value);
    }

    public string DiskTotal
    {
        get => GetString(Id.DiskTotal);
        set => SetString(Id.DiskTotal, value);
    }

    public double Duration
    {
        get => GetDouble(Id.Duration);
        set => SetDouble(Id.Duration, value);
    }

    public string FileName
    {
        get => GetString(Id.FileName);
        set => SetString(Id.FileName, value);
    }

    public long FileSize
    {
        get => _properties.GetInt64(Id.FileSize);
        set => _properties.SetInt64(Id.FileSize, value);
    }

    public string Genre
    {
        get => GetString(Id.Genre);
        set => SetString(Id.Genre, value);
    }

    public string Lyrics
    {
        get => GetString(Id.Lyrics);
        set => SetString(Id.Lyrics, value);
    }

    public string Publisher
    {
        get => GetString(Id.Publisher);
        set => SetString(Id.Publisher, value);
    }

    public int SampleRate
    {
        get => GetInt(Id.SampleRate);
        set => SetInt(Id.SampleRate, value);
    }

    public string Title
    {
        get => GetString(Id.Title);
        set => SetString(Id.Title, value);
    }

    public double TrackGain
    {
        get => GetDouble(Id.TrackGain);
        set => SetDouble(Id.TrackGain, value);
    }

    public string TrackNumber
    {
        get => GetString(Id.TrackNumber);
        set => SetString(Id.TrackNumber, value);
    }

    public double TrackPeak
    {
        get => GetDouble(Id.TrackPeak);
        set => SetDouble(Id.TrackPeak, value);
    }

    public string TrackTotal
    {
        get => GetString(Id.TrackTotal);
        set => SetString(Id.TrackTotal, value);
    }

    public string URL
    {
        get => GetString(Id.Url);
        set => SetString(Id.Url, value);
    }

    public double AddedDate => GetDouble(Id.MlAddingDate);

    public double LastPlayedDate => GetDouble(Id.MlLastPlayDate);

    public string Conductor
    {
        get => GetString(Id.Conductor);
        set => SetString(Id.Conductor, value);
    }

    public string Mood
    {
        get => GetString(Id.Mood);
        set => SetString(Id.Mood, value);
    }

    public string Catalog
    {
        get => GetString(Id.Catalog);
        set => SetString(Id.Catalog, value);
    }

    public string Isrc
    {
        get => GetString(Id.Isrc);
        set => SetString(Id.Isrc, value);
    }

    public string Lyricist
    {
        get => GetString(Id.Lyricist);
        set => SetString(Id.Lyricist, value);
    }

    public string EncodedBy
    {
        get => GetString(Id.EncodedBy);
        set => SetString(Id.EncodedBy, value);
    }

    public int Rating
    {
        get => GetInt(Id.Rating);
        set => SetInt(Id.Rating, value);
    }

    public DateTime StatAddingDate => ToDateTime(AddedDate);

    public DateTime StatLastPlayDate => ToDateTime(LastPlayedDate);

    public double StatMark
    {
        get => GetDouble(Id.MlMark);
        set => SetDouble(Id.MlMark, value);
    }

    public int StatPlayCount => GetInt(Id.MlPlayCount);

    public double StatRating => GetDouble(Id.MlRating);

    public double StatDisplayingMark
    {
        get => GetDouble(Id.DisplayingMark);
        set => SetDouble(Id.DisplayingMark, value);
    }

    public Bitmap AlbumArt
    {
        get => null;
        set
        {
            // Images are intentionally not projected into GDI+ bitmaps here:
            // the v1 contract exposes a Bitmap, the native object needs an
            // IAIMPImage. Providers that need it can use the native API.
        }
    }

    public void Assign(IAimpFileInfo source)
    {
        var native = source as AimpFileInfoWrapper;
        if (native != null)
        {
            var pointer = native.NativePointerInternal;
            try
            {
                _native.Assign(pointer);
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }
    }

    public IAimpFileInfo Clone()
    {
        var hr = _native.Clone(out var pointer);
        return hr < 0 || pointer == IntPtr.Zero ? null : new AimpFileInfoWrapper(pointer);
    }

    internal IAIMPFileInfoNative NativeRaw => _native;

    internal IntPtr NativePointerInternal
    {
        get
        {
            var unknown = Marshal.GetIUnknownForObject(_native);
            try
            {
                var iid = AimpIids.IAIMPFileInfo;
                return Marshal.QueryInterface(unknown, ref iid, out var pointer) < 0
                    ? IntPtr.Zero
                    : pointer;
            }
            finally
            {
                Marshal.Release(unknown);
            }
        }
    }

    private static DateTime ToDateTime(double value)
    {
        return value <= 0 ? DateTime.MinValue : DateTime.FromOADate(value);
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
        Marshal.FinalReleaseComObject(_native);
    }
}