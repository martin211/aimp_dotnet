namespace AIMP.SDK.Objects;

/// <summary>
/// 
/// </summary>
public interface IAimpHashCode
{
    /// <summary>
    /// Returns a hash code for this instance.
    /// </summary>
    /// <returns>
    /// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
    /// </returns>
    int GetAimpHashCode();

    /// <summary>
    /// Recalculates the hash code.
    /// </summary>
    void Recalculate();
}