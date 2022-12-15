//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Drawing;

namespace AIMP.SDK.Objects;

/// <summary>
/// The IAimpImageContainer interface unlike IAimpImage is used for storing and sharing images.
/// The image data is compressed and all requested parameters are calculated on-fly. 
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpObject" />
/// <seealso cref="AIMP.SDK.Objects.IAimpHashCode" />
public interface IAimpImageContainer : IAimpObject, IAimpHashCode
{
    /// <summary>
    /// Method creates <see cref="IAimpImage"/> that based on copy of source data.
    /// </summary>
    AimpActionResult<IAimpImage> CreateImage();

    /// <summary>
    /// Information about the image.
    /// Information is calculated on-fly using format headers - image data is not uncompressed to do it.Note that this information can be wrong if format headers in the file are corrupted
    /// </summary>
    AimpActionResult<Tuple<Size, AimpImageFormat>> GetInfo();

    /// <summary>
    /// Gets the data.
    /// </summary>
    AimpActionResult<byte[]> GetData();


    AimpActionResult SetData(byte[] data);

    /// <summary>
    /// Gets the size of the data.
    /// </summary>
    uint GetDataSize();

    /// <summary>
    /// Method provides an ability to set new size of data array.
    /// Warning! Changing the size leads to flush image data.
    /// </summary>
    /// <param name="value">The data size.</param>
    AimpActionResult SetDataSize(long value);
}