using System;
using System.Collections.Generic;
using System.Diagnostics;
using AIMP.SDK;
using AIMP.SDK.Core;

namespace AIMP.Internal
{
    /// <summary>
    /// Process wide state of the managed host: the AIMP core and the list of
    /// objects that must stay reachable while native code holds their CCW.
    /// </summary>
    internal static class AimpRuntime
    {
        private static readonly object Sync = new object();
        private static readonly List<object> Alive = new List<object>();

        /// <summary>
        /// Access to the player. Set by the host before the plugin starts.
        /// </summary>
        public static AimpCore Core { get; private set; }

        /// <summary>
        /// Version of the running AIMP. Unknown until detected.
        /// </summary>
        public static AimpVersion Version { get; private set; } = AimpVersion.Unknown;

        internal static void Initialize(AimpCore core)
        {
            Core = core;
        }

        internal static void SetVersion(AimpVersion version)
        {
            Version = version;
        }

        /// <summary>
        /// Reads the AIMP version from the version service, falling back to the
        /// version of the running executable when the service is unavailable.
        /// </summary>
        internal static AimpVersion DetectVersion(IAimpServiceVersionInfo versionInfo)
        {
            if (versionInfo != null)
            {
                try
                {
                    var versionId = versionInfo.VersionId;
                    if (versionId > 0)
                    {
                        var build = 0;
                        var displayName = (string)null;
                        var buildDate = default(DateTime);
                        var buildState = BuildStateType.Alpha;

                        try
                        {
                            build = versionInfo.BuildNumber;
                        }
                        catch
                        {
                            // The version is still usable without the build number.
                        }

                        try
                        {
                            displayName = versionInfo.FormatInfo;
                        }
                        catch
                        {
                            // The version is still usable without the display string.
                        }

                        try
                        {
                            buildDate = versionInfo.BuildDate;
                        }
                        catch
                        {
                            // The version is still usable without the build date.
                        }

                        try
                        {
                            buildState = versionInfo.BuildState;
                        }
                        catch
                        {
                            // The version is still usable without the build state.
                        }

                        return new AimpVersion(
                            versionId / 1000,
                            (versionId / 10) % 100,
                            versionId % 10,
                            build,
                            displayName,
                            buildDate,
                            buildState);
                    }
                }
                catch (Exception exception)
                {
                    AimpLog.Write(
                        $"Unable to read the AIMP version from the version service: {exception.Message}");
                }
            }

            try
            {
                var fileVersion = Process.GetCurrentProcess().MainModule?.FileVersionInfo;
                if (fileVersion != null && fileVersion.FileMajorPart > 0)
                {
                    return new AimpVersion(
                        fileVersion.FileMajorPart,
                        fileVersion.FileMinorPart,
                        0,
                        fileVersion.FileBuildPart,
                        "v" + fileVersion.FileMajorPart + "." +
                        fileVersion.FileMinorPart + "." + fileVersion.FileBuildPart);
                }
            }
            catch (Exception exception)
            {
                AimpLog.Write(
                    $"Unable to read the AIMP version from the host executable: {exception.Message}");
            }

            return AimpVersion.Unknown;
        }

        internal static void Shutdown()
        {
            Core = null;
            Version = AimpVersion.Unknown;

            lock (Sync)
            {
                Alive.Clear();
            }
        }

        /// <summary>
        /// AIMP keeps raw interface pointers of our COM callable wrappers, so the
        /// managed objects behind them must not be collected.
        /// </summary>
        public static T KeepAlive<T>(T instance) where T : class
        {
            if (instance == null)
            {
                return null;
            }

            lock (Sync)
            {
                if (!Alive.Contains(instance))
                {
                    Alive.Add(instance);
                }
            }

            return instance;
        }

        /// <summary>
        /// Forgets an object previously pinned with <see cref="KeepAlive{T}"/>.
        /// </summary>
        public static void Release(object instance)
        {
            if (instance == null)
            {
                return;
            }

            lock (Sync)
            {
                Alive.Remove(instance);
            }
        }

        public static AimpCore RequireCore()
        {
            var core = Core;
            if (core == null)
            {
                throw new InvalidOperationException("AIMP core is not available yet.");
            }

            return core;
        }
    }
}