using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{

    /// <summary>
    /// Contains operation with configuration file
    /// </summary>
    public interface IMAIMPConfigurationManager
    {
        /// <summary>
        /// Test, if section exists in configuration file
        /// </summary>
        /// <param name="SectionName">Name of section</param>
        /// <returns>Section existence</returns>
        bool IsSectionExist(string SectionName);
        /// <summary>
        /// Read some parameter from configuration file as Int32 value (if value doesn't exist, it return 0)
        /// </summary>
        /// <param name="Section">Configuration file section</param>
        /// <param name="Name">Parameter name</param>
        /// <returns>Value</returns>
        int ReadParameterInt32(string Section, string Name);
        /// <summary>
        /// Read some parameter from configuration file as Int32 value
        /// </summary>
        /// <param name="Section">Configuration file section</param>
        /// <param name="Name">Parameter name</param>
        /// <param name="Val">Readed value</param>
        /// <returns>Parameter existence</returns>
        bool ReadParameterInt32(string Section, string Name, out int Val);
        /// <summary>
        /// Read some parameter from configuration file as String value
        /// </summary>
        /// <param name="Section">Configuration file section</param>
        /// <param name="Name">Parameter name</param>
        /// <returns>Readed value ('null' if doesn't exist)</returns>
        string ReadParameterString(string Section, string Name);
        /// <summary>
        /// Remove hole section inside configuration file
        /// </summary>
        /// <param name="SectionName">Name of section</param>
        /// <returns>Success</returns>
        bool RemoveSection(string SectionName);
        /// <summary>
        /// Write Int32 parameter to configuration file
        /// </summary>
        /// <param name="Section">Name of section</param>
        /// <param name="Name">Parameter</param>
        /// <param name="val">Value</param>
        /// <returns>Success</returns>
        bool WriteParameter(string Section, string Name, int val);
        /// <summary>
        /// Write String parameter to configuration file
        /// </summary>
        /// <param name="Section">Name of section</param>
        /// <param name="Name">Parameter</param>
        /// <param name="val">Value</param>
        /// <returns>Success</returns>
        bool WriteParameter(string Section, string Name, string val);

        /// <summary>
        /// Path to configuration file
        /// </summary>
        /// <returns>Path to configuration file</returns>
        string GetConfigFilePath();
    }
}
