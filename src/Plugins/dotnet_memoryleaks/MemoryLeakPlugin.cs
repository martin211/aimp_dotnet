using System;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Player;

namespace Aimp.DotNet.MemoryLeaks
{
    public class AimpHook : IAimpMessageHook
    {
        private IAimpPlayer _player;

        public AimpHook(IAimpPlayer player)
        {
            _player = player;
        }

        public AimpActionResult CoreMessage(AimpCoreMessageType message, int param1, int param2)
        {
            if (message == AimpCoreMessageType.AIMP_MSG_EVENT_PLAYER_STATE && param1 == 2)
            {
                var cfi = _player.CurrentFileInfo;
            }

            return AimpActionResult.OK;
        }
    }

    [AimpPlugin("MemoryLeakPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MemoryLeakPlugin plugin")]
    public class MemoryLeakPlugin : AimpPlugin
    {
        private IAimpMessageHook _hook;

        public override void Initialize()
        {
            _hook = new AimpHook(Player);
            Player.ServiceMessageDispatcher.Hook(_hook);
        }

        public override void Dispose()
        {
        }
    }
}
