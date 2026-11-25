using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates how method invocation affects content of the collection
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class CollectionAccessAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CollectionAccessAttribute" /> class.
        /// </summary>
        /// <param name="collectionAccessType">Type of the collection access.</param>
        public CollectionAccessAttribute(CollectionAccessType collectionAccessType)
        {
            CollectionAccessType = collectionAccessType;
        }

        /// <summary>
        /// Gets the type of the collection access.
        /// </summary>
        /// <value>The type of the collection access.</value>
        public CollectionAccessType CollectionAccessType { get; }
    }
}