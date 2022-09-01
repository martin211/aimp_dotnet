//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK
{
    public interface IAimpDPIAware : IAimpObject
    {
        /// <summary>
        /// Gets or sets the dpi.
        /// </summary>
        /// <value>The dpi.</value>
        int DPI { get; set; }
    }
}
