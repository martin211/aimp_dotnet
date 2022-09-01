﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.Loader;

/// <summary>
/// Class PluginLoadingStrategy.
/// Implements the <see cref="System.MarshalByRefObject" />
/// </summary>
/// <seealso cref="System.MarshalByRefObject" />
public abstract class PluginLoadingStrategy : MarshalByRefObject
{
    /// <summary>
    /// Loads the specified path.
    /// </summary>
    /// <param name="path">The path.</param>
    /// <returns>PluginShortInfoForLoad.</returns>
    public abstract PluginShortInfoForLoad Load(string path);
}
