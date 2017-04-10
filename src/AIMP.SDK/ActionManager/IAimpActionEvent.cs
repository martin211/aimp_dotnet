using System;

namespace AIMP.SDK.ActionManager
{
    /// <summary>
    /// This interface is simple event handler.
    /// </summary>
    public interface IAimpActionEvent
    {
        //todo: add Data parameter
        event EventHandler OnExecute;
    }
}