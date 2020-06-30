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

using AIMP.SDK.ActionManager;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Uses for notify library about changes at data storage.
    /// <para>
    /// Instance of interface creates by music library manager and put to plugin via the <see cref="AIMP.SDK.MusicLibrary.Extension.IAimpExtensionDataStorage.Initialize"/> method.
    /// </para>
    /// </summary>
    public interface IAimpDataStorageManager
    {
        /// <summary>
        /// Notifies about the background task that has been started.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="caption">The caption.</param>
        /// <param name="cancelEvent">The cancel event.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType BackgroundTaskStarted(int id, string caption, IAimpActionEvent cancelEvent);

        /// <summary>
        /// Notifies about the background task that has been finished.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType BackgroundTaskFinished(int id);

        /// <summary>
        /// Notifies the manager that data in data storage has been changed.
        /// This reloads the data in all views of Music Library and smart-playlists.
        /// </summary>
        void Changed();
    }
}