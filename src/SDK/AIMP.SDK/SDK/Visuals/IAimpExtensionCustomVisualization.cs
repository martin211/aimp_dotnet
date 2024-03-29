﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Visuals
{
    /// <summary>
    /// This is extension for the <see cref="IAimpServiceVisualizations" /> service.
    /// This type of visualization provides an ability to render visualization outside of the visual display of player, and
    /// not depended from user choice.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application in the
    /// <see cref="AimpPlugin.Initialize" /> method via the <see cref="IAimpCore.RegisterExtension" /> method.
    /// </para>
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
    public interface IAimpExtensionCustomVisualization : IAimpExtension
    {
        /// <summary>
        /// Gets the combinations of the <see cref="AimpVisualFlags" />.
        /// </summary>
        /// <returns>AimpVisualFlags.</returns>
        AimpVisualFlags GetFlags();

        /// <summary>
        /// Draws the specified data.
        /// </summary>
        /// <param name="data">The visual data <see cref="AimpVisualData" />.</param>
        void Draw(AimpVisualData data);
    }
}
