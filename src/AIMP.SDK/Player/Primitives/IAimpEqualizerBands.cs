namespace AIMP.SDK.Player.Primitives
{
    /// <summary>
    /// 
    /// </summary>
    public interface IAimpEqualizerBands
    {
        /// <summary>
        /// Gets the band count.
        /// </summary>
        /// <returns></returns>
        int GetBandCount();

        /// <summary>
        /// Gets the band frequency.
        /// </summary>
        /// <param name="bandIndex">Index of the band.</param>
        /// <returns></returns>
        DoubleActionResult GetBandFrequency(int bandIndex);

        /// <summary>
        /// Gets the band gain.
        /// </summary>
        /// <param name="bandIndex">Index of the band.</param>
        /// <returns></returns>
        DoubleActionResult GetBandGain(int bandIndex);

        /// <summary>
        /// Sets the band gain.
        /// </summary>
        /// <param name="integer">The integer.</param>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        AimpActionResult SetBandGain(int integer, double value);
    }
}