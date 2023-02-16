//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Player.Objects
{
    /// <summary>
    /// 
    /// </summary>
    public interface IAimpEqualizerBands : IAimpObject
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