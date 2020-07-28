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

using System;

namespace AIMP.SDK
{
    /// <summary>
    /// Interface provides methods for working with binary stream.
    /// Implements the <see cref="System.IDisposable" />
    /// Implements the <see cref="AIMP.SDK.IAimpObject" />
    /// </summary>
    /// <seealso cref="System.IDisposable" />
    /// <seealso cref="AIMP.SDK.IAimpObject" />
    public interface IAimpStream : IDisposable, IAimpObject
    {
        /// <summary>
        /// Gets the size of stream, in bytes.
        /// </summary>
        /// <returns>System.Int64.</returns>
        long GetSize();

        /// <summary>
        /// Method provides an ability to set stream size, in bytes.
        /// <para>
        /// Note: size of stream will be automatically extended when it needed.This method is for optimization purposes only.
        /// Warning! If current stream size more than new defined - part of data will be truncated.
        /// </para>
        /// </summary>
        /// <param name="value">New size, in bytes.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetSize(long value);

        /// <summary>
        /// Gets the position of reading / writing cursor in bytes.
        /// </summary>
        /// <returns>System.Int64.</returns>
        long GetPosition();

        /// <summary>
        /// Allows to change position of reading / writing cursor.
        /// </summary>
        /// <param name="offset">Offset in bytes.</param>
        /// <param name="mode">A value of type <see cref="T:System.IO.SeekOrigin" /> indicating the reference point used to obtain the new position.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Seek(long offset, System.IO.SeekOrigin mode);

        /// <summary>
        /// Reads a block of bytes from the current stream and writes the data to a buffer.
        /// </summary>
        /// <param name="buffer">When this method returns, contains the specified byte array with the values from the current stream.</param>
        /// <param name="count">The maximum number of bytes to read.</param>
        /// <returns>-1 on unexpected failure or count of read bytes otherwise.</returns>
        int Read(byte[] buffer, int count);

        /// <summary>
        /// Writes a block of bytes to the current stream using data read from a buffer.
        /// </summary>
        /// <param name="buffer">The buffer to write data from.</param>
        /// <param name="count">The maximum number of bytes to write.</param>
        /// <param name="writen">Parameter displays what bytes has been really written to the stream.
        /// This parameter is optional - can be null.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Write(byte[] buffer, int count, out int writen);
    }
}