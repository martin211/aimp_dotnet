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

namespace AIMP.SDK.Core
{
    public enum BuildStateType
    {
        Relese,
        ReleaseCandidate,
        Beta,
        Alpha
    }

    /// <summary>
    /// Service provide ability to get information about program version.
    /// </summary>
    public interface IAimpServiceVersionInfo
    {
        /// <summary>
        /// Gets the information about version.
        /// Format is v<major>.<minor>.<build>, build <buildNumber> (build date)
        /// </summary>
        string FormatInfo { get; }

        /// <summary>
        /// Gets the build date.
        /// </summary>
        DateTime BuildDate { get; }

        /// <summary>
        /// Gets the state of the build.
        /// </summary>
        BuildStateType BuildState { get; }

        /// <summary>
        /// Gets the build number.
        /// </summary>
        int BuildNumber { get; }

        /// <summary>
        /// Gets the version identifier.
        /// Format XYYZ. Where X - major version. YY - minor version. Z - edition version.
        /// <p>
        /// Example:
        /// 3551 -> 3.55.1
        /// 10051 -> 10.05.1
        /// 0010 -> 0.01.0
        /// </p>
        /// </summary>
        int VersionId { get; }
    }
}
