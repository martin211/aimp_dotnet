using System;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// Local files storage marker over <see cref="AimpDataStorageWrapper"/>.
/// </summary>
internal sealed class AimpLocalDataStorageWrapper : AimpDataStorageWrapper, IAimpLocalDataStorage
{
    public AimpLocalDataStorageWrapper(IntPtr ownedPointer)
        : base(ownedPointer)
    {
    }
}