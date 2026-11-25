using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates that a parameter is a path to a file or a folder within a web project.
    /// Path can be relative or absolute, starting from web root (~)
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Parameter)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public class PathReferenceAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PathReferenceAttribute" /> class.
        /// </summary>
        public PathReferenceAttribute()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="PathReferenceAttribute" /> class.
        /// </summary>
        /// <param name="basePath">The base path.</param>
        public PathReferenceAttribute([PathReference] string basePath)
        {
            BasePath = basePath;
        }

        /// <summary>
        /// Gets the base path.
        /// </summary>
        /// <value>The base path.</value>
        public string BasePath { get; }
    }
}