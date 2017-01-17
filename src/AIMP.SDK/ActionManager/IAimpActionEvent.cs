using System;

namespace AIMP.SDK.ActionManager
{
    public interface IAimpActionEvent
    {
        event EventHandler OnExecute;
    }
}