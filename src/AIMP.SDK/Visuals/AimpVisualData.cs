// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Visuals
{
    /// <summary>
    /// This structure contains visualization data that needed for frame rendering.
    /// <para>Data was calculated before the volume, balance and anti-clipping filters were applied.</para>
    /// </summary>
    public class AimpVisualData
    {
        /// <summary>
        /// An array of two elements of float (32-bit floating point value) type.
        /// Current signal level in left and right channels[0.0.. 1.0..infinity], where 1.0 is equals to 0 dB
        /// </summary>
        public float[] Peaks { get; set; }

        /// <summary>
        /// An array of three elements of float type.
        /// 0 - spectrum of left channel
        /// 1 - spectrum of right channel
        /// 2 - spectrum of both channels
        /// This field is populated only if the extension returns the <see cref="AimpVisualFlags.AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM"/> flag in the GetFlags method.
        /// <para>
        /// Here is short table of relationships between array index and freq of the signal:
        /// 0 ~ 20 Hz
        /// 10 ~ 200 Hz
        /// 20 ~ 400 Hz
        /// 30 ~ 630 Hz
        /// 40 ~ 870 Hz
        /// 50 ~ 1.1 KHz
        /// 60 ~ 1.4 KHz
        /// 70 ~ 1.7 KHz
        /// 80 ~ 2.1 KHz
        /// 90 ~ 2.5 KHz
        /// 100 ~ 3.0 KHz
        /// 110 ~ 3.5 KHz
        /// 120 ~ 4.0 KHz
        /// 130 ~ 4.5 KHz
        /// 140 ~ 5.2 KHz
        /// 150 ~ 6.0 KHz
        /// 160 ~ 6.7 KHz
        /// 170 ~ 7.6 KHz
        /// 180 ~ 8.5 KHz
        /// 190 ~ 9.6 KHz
        /// 200 ~ 11.0 KHz
        /// 210 ~ 12.0 KHz
        /// 220 ~ 13.5 KHz
        /// 230 ~ 15.0 KHz
        /// 240 ~ 16.8 KHz
        /// 255 ~ 20.0 KHz
        /// </para>
        /// </summary>
        public float[][] Spectrum { get; set; }

        /// <summary>
        /// An array of two elements of float type.
        /// Source data of left and right channels in wave-form.
        /// This field is populated only if the extension returns the <see cref="AimpVisualFlags.AIMP_VISUAL_FLAGS_RQD_DATA_WAVE"/> flag in the GetFlags method.
        /// <para>
        /// 32-bit float per sample.
        /// Sample range is [-infinity.. -1.0 .. 0.0 .. 1.0 .. infinity], where |1.0| is equals to 0 dbFS.
        /// </para>
        /// </summary>
        public float[][] WaveForm { get; set; }
    }
}