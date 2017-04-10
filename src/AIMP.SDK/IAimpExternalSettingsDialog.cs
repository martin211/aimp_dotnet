using System;

namespace AIMP.SDK
{
    /// <summary>
    /// If plugin has external settings dialog that not integrated in the application via Options Dialog API, it should implement this interface on same to <see cref="IAimpPlugin"/> interface level.
    /// </summary>
    public interface IAimpExternalSettingsDialog
    {
        /// <summary>
        /// Shows the modal dialog.
        /// </summary>
        /// <param name="parentWindow">Handle of calling window.</param>
        void Show(IntPtr parentWindow);
    }
}