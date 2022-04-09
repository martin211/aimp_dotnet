using System;
using System.Drawing;

namespace AIMP.SDK.Objects;

public interface IAimpImageContainer : IAimpObject
{
    AimpActionResult<IAimpImage> CreateImage();

    AimpActionResult<Tuple<Size, int>> GetInfo();

    AimpActionResult<byte[]> GetData();

    uint GetDataSize();

    AimpActionResult SetDataSize(long value);
}