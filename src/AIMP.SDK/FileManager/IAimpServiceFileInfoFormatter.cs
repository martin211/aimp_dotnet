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

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Service provides an ability to format file information with specified template.
    /// </summary>
    public interface IAimpServiceFileInfoFormatter : IAimpService
    {
        /// <summary>
        /// Formats the specified template.
        /// </summary>
        /// <param name="template">The list of supported macros for template depends from version of application.</param>
        /// <param name="fileInfo">Put null to generate preview string.</param>
        /// <param name="formattedResult">The formatted string.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult<string> Format(string template, IAimpFileInfo fileInfo);
    }
}