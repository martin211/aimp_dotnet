//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.Core
{
    /// <summary>
    /// The build state type enum
    /// </summary>
    public enum BuildStateType
    {
        /// <summary>
        /// Relese
        /// </summary>
        Relese = 0,
        /// <summary>
        /// Release candidate
        /// </summary>
        ReleaseCandidate = 1,
        /// <summary>
        /// Beta
        /// </summary>
        Beta = 2,
        /// <summary>
        /// Alpha
        /// </summary>
        Alpha = 3
    }

    /// <summary>
    /// Service provide ability to get information about program version.
    /// </summary>
    public interface IAimpServiceVersionInfo
    {
        /// <summary>
        /// Gets the information about version.
        /// Format is v'Major'.'Minor'.'Build', build 'BuildNumber' (build date)
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
