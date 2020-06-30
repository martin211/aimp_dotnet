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

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public interface IAimpDataStorageCommandAddFilesDialog
    {
        /// <summary>
        /// Executes the specified owner handle.
        /// </summary>
        /// <param name="ownerHandle">The owner window handle.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Execute(IntPtr ownerHandle);
    }
}