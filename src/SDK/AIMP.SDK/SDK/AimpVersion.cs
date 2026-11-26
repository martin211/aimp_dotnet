using System;
using AIMP.SDK.Core;

namespace AIMP.SDK;

/// <summary>
/// Version of the AIMP host application.
/// </summary>
public readonly struct AimpVersion : IComparable<AimpVersion>, IEquatable<AimpVersion>
{
    /// <summary>
    /// Version that could not be detected.
    /// </summary>
    public static readonly AimpVersion Unknown =
        new AimpVersion(false, 0, 0, 0, 0, null, default, BuildStateType.Alpha);

    public AimpVersion(
        int major,
        int minor,
        int edition,
        int build,
        string displayName = null,
        DateTime buildDate = default,
        BuildStateType buildState = BuildStateType.Alpha)
        : this(true, major, minor, edition, build, displayName, buildDate, buildState)
    {
    }

    private AimpVersion(
        bool isKnown,
        int major,
        int minor,
        int edition,
        int build,
        string displayName,
        DateTime buildDate,
        BuildStateType buildState)
    {
        IsKnown = isKnown;
        Major = major;
        Minor = minor;
        Edition = edition;
        Build = build;
        DisplayName = displayName;
        BuildDate = buildDate;
        BuildState = buildState;
    }

    /// <summary>
    /// Gets whether the version was detected.
    /// </summary>
    public bool IsKnown { get; }

    /// <summary>
    /// Gets the major version (5 for AIMP 5.x, 6 for AIMP 6.x).
    /// </summary>
    public int Major { get; }

    /// <summary>
    /// Gets the minor version (for example 40 for AIMP 5.40).
    /// </summary>
    public int Minor { get; }

    /// <summary>
    /// Gets the edition digit of the version identifier.
    /// </summary>
    public int Edition { get; }

    /// <summary>
    /// Gets the build number.
    /// </summary>
    public int Build { get; }

    /// <summary>
    /// Gets the version string reported by AIMP, when available.
    /// </summary>
    public string DisplayName { get; }

    /// <summary>
    /// Gets the build date reported by AIMP, when available.
    /// </summary>
    public DateTime BuildDate { get; }

    /// <summary>
    /// Gets the build state reported by AIMP.
    /// </summary>
    public BuildStateType BuildState { get; }

    /// <summary>
    /// Gets the version identifier in the <c>XYYZ</c> form.
    /// </summary>
    public int VersionId => IsKnown ? Major * 1000 + Minor * 10 + Edition : 0;

    /// <summary>
    /// Returns <c>true</c> when the version is unknown or is at least
    /// <paramref name="major"/>.<paramref name="minor"/>.
    /// </summary>
    public bool IsAtLeast(int major, int minor)
    {
        return !IsKnown ||
               Major > major ||
               (Major == major && Minor >= minor);
    }

    public int CompareTo(AimpVersion other)
    {
        if (!IsKnown)
        {
            return other.IsKnown ? -1 : 0;
        }

        if (!other.IsKnown)
        {
            return 1;
        }

        var result = Major.CompareTo(other.Major);
        if (result != 0)
        {
            return result;
        }

        result = Minor.CompareTo(other.Minor);
        if (result != 0)
        {
            return result;
        }

        result = Edition.CompareTo(other.Edition);
        return result != 0 ? result : Build.CompareTo(other.Build);
    }

    public bool Equals(AimpVersion other)
    {
        return IsKnown == other.IsKnown &&
               Major == other.Major &&
               Minor == other.Minor &&
               Edition == other.Edition &&
               Build == other.Build;
    }

    public override bool Equals(object obj)
    {
        return obj is AimpVersion other && Equals(other);
    }

    public override int GetHashCode()
    {
        unchecked
        {
            var hash = IsKnown.GetHashCode();
            hash = (hash * 397) ^ Major;
            hash = (hash * 397) ^ Minor;
            hash = (hash * 397) ^ Edition;
            hash = (hash * 397) ^ Build;
            return hash;
        }
    }

    public override string ToString()
    {
        if (!IsKnown)
        {
            return "unknown";
        }

        return string.IsNullOrWhiteSpace(DisplayName)
            ? "v" + Major + "." + Minor + "." + Build
            : DisplayName;
    }
}