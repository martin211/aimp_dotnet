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
using System.IO;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Struct AimpFileAttributes
    /// Implements the <see cref="System.IEquatable{AIMP.SDK.FileManager.AimpFileAttributes}" />
    /// Implements the <see cref="System.IEquatable{AIMP.SDK.FileManager.AimpFileAttributes}" />
    /// </summary>
    /// <seealso cref="System.IEquatable{AIMP.SDK.FileManager.AimpFileAttributes}" />
    public struct AimpFileAttributes : IEquatable<AimpFileAttributes>
    {
        /// <summary>
        /// Gets or sets the attributes.
        /// </summary>
        /// <value>The attributes.</value>
        public FileAttributes Attributes { get; set; }

        /// <summary>
        /// Gets or sets the time last access.
        /// </summary>
        /// <value>The time last access.</value>
        public double TimeLastAccess { get; set; }

        /// <summary>
        /// Gets or sets the time last write.
        /// </summary>
        /// <value>The time last write.</value>
        public double TimeLastWrite { get; set; }

        /// <summary>
        /// Gets or sets the time creation.
        /// </summary>
        /// <value>The time creation.</value>
        public double TimeCreation { get; set; }

        /// <summary>
        ///     Indicates whether the current object is equal to another object of the same type.
        /// </summary>
        /// <param name="other">An object to compare with this object.</param>
        /// <returns>true if the current object is equal to the <paramref name="other" /> parameter; otherwise, false.</returns>
        /// <inheritdoc />
        public bool Equals(AimpFileAttributes other)
        {
            return Attributes.Equals(other.Attributes) &&
                   Math.Abs(TimeLastAccess - other.TimeLastAccess).Equals(0) &&
                   Math.Abs(TimeLastWrite - other.TimeLastWrite).Equals(0) &&
                   Math.Abs(TimeCreation - other.TimeCreation).Equals(0);
        }
    }
}
