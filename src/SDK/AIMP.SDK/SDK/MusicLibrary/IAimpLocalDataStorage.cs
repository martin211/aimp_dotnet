//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary;

public interface IAimpLocalDataStorage : IAimpDataStorage2
{
    public class Fields
    {
        public const string ID = "ID";
        public const string Added = "Added";
        public const string Album = "Album";
        public const string AlbumArtist = "AlbumArtist";
        public const string Artist = "Artist";
        public const string BitDepth = "BitDepth";
        public const string BitRate = "Bitrate";
        public const string BPM = "BPM";
        public const string Channels = "Channels";
        public const string Catalog = "Catalog";
        public const string Comment = "Comment";
        public const string Composer = "Composer";
        public const string Conductor = "Conductor";
        public const string Copyrights = "Copyrights";
        public const string DiskNumber = "DiskNumber";
        public const string Duration = "Duration";
        public const string FileName = "FileName";
        public const string FileSize = "FileSize";
        public const string Genre = "Genre";
        public const string Labels = "Labels";
        public const string LastModification = "LastModification";
        public const string LastPlayback = "LastPlayback";
        public const string Lyricist = "Lyricist";
        public const string Mood = "Mood";
        public const string PlayBackCount = "PlaybackCount";
        public const string Publisher = "Publisher";
        public const string Rating = "Rating";
        public const string SampleRate = "SampleRate";
        public const string Title = "Title";
        public const string Url = "URL";
        public const string UserMark = "UserMark";
        public const string Year = "Year";
        public const string FileFormat = "FileFormat";
        public const string TrackNumber = "TrackNumber";
    }
}