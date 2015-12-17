using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// AIMP Events
    /// </summary>
    public interface IMAIMPEventManager
    {
        event MAIMPPlayerEventsDelegate SatusChangeEvent;
        event MAIMPPlayerEventsDelegate PlayFileEvent;
        event MAIMPPlayerEventsDelegate InfoUpdateEvent;
        event MAIMPPlayerEventsDelegate PlayerStateChangedEvent;
        event MAIMPPlayerEventsDelegate EffectChangedEvent;
        event MAIMPPlayerEventsDelegate EQChangedEvent;
        event MAIMPPlayerEventsDelegate TrackPosChangedEvent;

        //MAIMPPlayerEventsDelegate GetInvocation(MAIMPPlayerEventsDelegate dlg); 
    }
}
