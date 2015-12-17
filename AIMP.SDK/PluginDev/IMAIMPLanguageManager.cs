using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Working with language file
    /// </summary>
    public interface IMAIMPLanguageManager
    {
        /// <summary>
        /// Test, if language ection exists
        /// </summary>
        /// <param name="Section">Name of section</param>
        /// <returns>Existence</returns>
        bool IsSectionExist(string Section);
        /// <summary>
        /// Get value from language file as string
        /// </summary>
        /// <param name="Section">Section name</param>
        /// <param name="Name">Parameter name</param>
        /// <returns>Value</returns>
        string ReadValueString(string Section, string Name);

        /// <summary>
        /// Get Language file version
        /// </summary>
        /// <returns>Version</returns>
        int GetLanguageVersion();
        /// <summary>
        /// Get current language
        /// </summary>
        /// <returns>Language</returns>
        string GetCurrentLanguage();
        /// <summary>
        /// Get path to current language file
        /// </summary>
        /// <returns>Path to file</returns>
        string GetLanguageFilePath();
    }
}
