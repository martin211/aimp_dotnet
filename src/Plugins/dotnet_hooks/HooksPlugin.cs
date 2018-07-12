using System;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Player;

namespace dotnet_hooks
{
    public class TestHook : IAimpMessageHook
    {
        private readonly IAimpPlayer _player;

        public TestHook(IAimpPlayer player)
        {
            _player = player;
        }

        public AimpActionResult CoreMessage(AimpMessages.AimpCoreMessageType message, int param1, int param2)
        {
            if (message == AimpMessages.AimpCoreMessageType.AIMP_MSG_CMD_QUIT || message == AimpMessages.AimpCoreMessageType.AIMP_MSG_EVENT_TERMINATING)
            {
                return AimpActionResult.Fail;
            }

            if (message == AimpMessages.AimpCoreMessageType.AIMP_MSG_PROPERTY_HWND)
            {
                switch ((AimpWindowHandleTypes)param1)
                {
                    case AimpWindowHandleTypes.MainForm:
                        break;
                    case AimpWindowHandleTypes.Application:
                        break;
                    case AimpWindowHandleTypes.TrayControl:
                        break;
                    case AimpWindowHandleTypes.PlaylistForm:
                        break;
                    case AimpWindowHandleTypes.EqualizerForm:
                        break;
                }
            }

            return AimpActionResult.Ok;
        }
    }

    [AimpPlugin("DotNet Hooks Test", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons)]
    public class HooksPlugin : AimpPlugin
    {
        private TestHook _hook;

        public override void Initialize()
        {
            _hook = new TestHook(Player);
            if (Player.ServiceMessageDispatcher.Hook(_hook) != AimpActionResult.Ok)
            {
                System.Diagnostics.Debugger.Break();
            }

            IntPtr prm = IntPtr.Zero;
            Player.ServiceMessageDispatcher.Send((int)AimpMessages.AimpCoreMessageType.AIMP_MSG_PROPERTY_HWND, (int)AimpWindowHandleTypes.PlaylistForm, prm);
        }

        public override void Dispose()
        {
            if (Player.ServiceMessageDispatcher.Unhook(_hook) != AimpActionResult.Ok)
            {
                System.Diagnostics.Debugger.Break();
            }
        }
    }
}
