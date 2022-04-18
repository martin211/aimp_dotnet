// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Objects
{
    public class Clipping
    {
        public Clipping(int offset, int size)
        {
            Offset = offset;
            Size = size;
        }

        public int Offset { get; }

        public int Size { get; }
    }

    /// <summary>
    /// IAimpFileStream is extended variant of IAimpStream specially for file-based streams.
    /// Implements the <see cref="IAimpStream" /></summary>
    /// <seealso cref="IAimpStream" />
    public interface IAimpFileStream : IAimpStream
    {
        /// <summary>
        /// If file is clipped the method will return clipping bounds. See the IAimpServiceFileStreaming.CreateStreamForFile.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult<Clipping> GetClipping();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        AimpActionResult<IAimpString> GetFileName();
    }
}
