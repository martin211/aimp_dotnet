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
using System.Runtime.InteropServices;
using AIMP.SDK.Objects;

namespace AIMP.SDK
{
    /// <summary>
    /// Class AimpObjectHelper.
    /// </summary>
    public static class AimpObjectHelper
    {
        /// <summary>
        /// Gets the object.
        /// </summary>
        /// <typeparam name="TObject">The type of the t object.</typeparam>
        /// <param name="core">The core.</param>
        /// <returns>TObject.</returns>
        public static TObject GetObject<TObject>(IAimpCore core)
        {
            var type = typeof(TObject);
            var header = IntPtr.Zero;
            if (type == typeof(IAimpString))
            {
                var id = new Guid(AimpObject.AimpString);
                //header = core.CreateObject(ref id);
            }

            if (header == IntPtr.Zero)
            {
                return default;
            }

            return GetObject<TObject>(header);
        }

        /// <summary>
        /// Gets the object.
        /// </summary>
        /// <typeparam name="TObject">The type of the t object.</typeparam>
        /// <param name="header">The header.</param>
        /// <returns>TObject.</returns>
        public static TObject GetObject<TObject>(IntPtr header)
        {
            return (TObject) Marshal.GetObjectForIUnknown(header);
        }

        /// <summary>
        /// Class AimpObject.
        /// </summary>
        public class AimpObject
        {
            /// <summary>
            /// The aimp string
            /// </summary>
            public const string AimpString = "41494D50-5374-7269-6E67-000000000000";
        }
    }
}