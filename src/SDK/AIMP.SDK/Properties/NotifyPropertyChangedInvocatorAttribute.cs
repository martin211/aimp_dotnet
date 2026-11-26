using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates that the method is contained in a type that implements
    /// <c>System.ComponentModel.INotifyPropertyChanged</c> interface and this method
    /// is used to notify that some property value changed
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    /// <example>
    ///   <code>
    /// public class Foo : INotifyPropertyChanged {
    /// public event PropertyChangedEventHandler PropertyChanged;
    /// [NotifyPropertyChangedInvocator]
    /// protected virtual void NotifyChanged(string propertyName) { ... }
    /// private string _name;
    /// public string Name {
    /// get { return _name; }
    /// set { _name = value; NotifyChanged("LastName"); /* Warning */ }
    /// }
    /// }
    /// </code>
    /// Examples of generated notifications:
    /// <list><item><c>NotifyChanged("Property")</c></item><item><c>NotifyChanged(() =&gt; Property)</c></item><item><c>NotifyChanged((VM x) =&gt; x.Property)</c></item><item><c>SetProperty(ref myField, value, "Property")</c></item></list></example>
    /// <remarks>The method should be non-static and conform to one of the supported signatures:
    /// <list><item><c>NotifyChanged(string)</c></item><item><c>NotifyChanged(params string[])</c></item><item><c>NotifyChanged{T}(Expression{Func{T}})</c></item><item><c>NotifyChanged{T,U}(Expression{Func{T,U}})</c></item><item><c>SetProperty{T}(ref T, T, string)</c></item></list></remarks>
    [AttributeUsage(AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class NotifyPropertyChangedInvocatorAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="NotifyPropertyChangedInvocatorAttribute" /> class.
        /// </summary>
        public NotifyPropertyChangedInvocatorAttribute()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="NotifyPropertyChangedInvocatorAttribute" /> class.
        /// </summary>
        /// <param name="parameterName">Name of the parameter.</param>
        public NotifyPropertyChangedInvocatorAttribute(string parameterName)
        {
            ParameterName = parameterName;
        }

        /// <summary>
        /// Gets the name of the parameter.
        /// </summary>
        /// <value>The name of the parameter.</value>
        public string ParameterName { get; }
    }
}