using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// This attribute is intended to mark publicly available API
    /// which should not be removed and so is treated as used
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [MeansImplicitUse]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class PublicAPIAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PublicAPIAttribute" /> class.
        /// </summary>
        public PublicAPIAttribute()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="PublicAPIAttribute" /> class.
        /// </summary>
        /// <param name="comment">The comment.</param>
        public PublicAPIAttribute([NotNull] string comment)
        {
            Comment = comment;
        }

        /// <summary>
        /// Gets the comment.
        /// </summary>
        /// <value>The comment.</value>
        public string Comment { get; }
    }
}