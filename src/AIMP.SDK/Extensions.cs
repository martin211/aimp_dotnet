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

namespace AIMP.SDK
{
    /// <summary>
    /// Class Extensions.
    /// </summary>
    public static class Extensions
    {
        /// <summary>
        /// Creates the aimp object.
        /// </summary>
        /// <typeparam name="TAimpObject">The type of the t aimp object.</typeparam>
        /// <param name="core">The core.</param>
        /// <returns>AimpActionResult&lt;TAimpObject&gt;.</returns>
        public static AimpActionResult<TAimpObject> CreateAimpObject<TAimpObject>(this IAimpCore core)
            where TAimpObject : class, IAimpObject
        {
            var result = core.CreateObject<TAimpObject>();
            if (result.ResultType != ActionResultType.OK)
            {
                return new AimpActionResult<TAimpObject>(result.ResultType, default);
            }

            return new AimpActionResult<TAimpObject>(result.ResultType, result.Result as TAimpObject);
        }
    }
}