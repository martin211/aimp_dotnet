#pragma once
#include "guiddef.h"


namespace AIMP
{
    using namespace System;
    using namespace AIMP::SDK;
    
    /// <summary>
    /// Aimp  Converter helper class.
    /// </summary>
    public ref class AimpConverter sealed
    {
    internal:
        /// <summary>
        /// Gets the AIMP native object.
        /// </summary>
        /// <param name="objectId">The object identifier.</param>
        template<typename TAimpNativeObject>
        static TAimpNativeObject GetObject(REFIID objectId);

        static IAIMPString* GetAimpString()
        {
            return NULL;
        }
    };
}