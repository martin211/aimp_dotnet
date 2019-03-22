// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.Threading
{
    /// <summary>
    /// This is tool interface that provides an ability to plugin to be notified about canceling the operation.
    /// The instance of interface will be created by the application and will be sent to plugin as parameter of the <see cref="IAimpTask.Execute"/> method.
    /// </summary>
    public interface IAimpTaskOwner
    {
        /// <summary>
        /// Plugin must break the operation if the property is True.
        /// </summary>
        bool IsCanceled { get; }
    }
}