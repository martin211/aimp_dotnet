//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Windows.Input;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.MenuManager.Objects;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Playlist.Extensions;
using AIMP.SDK.Playlist.Objects;
using DemoPlugin;
using DemoPlugin.OptionsFrame;

namespace TestPlugin
{
    using AIMP.SDK;
    using AIMP.SDK.MenuManager;
    using AIMP.SDK.Options;
    using DemoPlugin.Extension;

    public delegate ActionResultType HookMessage(AimpCoreMessageType message, int param1, IntPtr param2);

    public class MessageHook : IAimpMessageHook
    {
        public AimpActionResult CoreMessage(AimpCoreMessageType message, int param1, IntPtr param2)
        {
            OnCoreMessage?.Invoke(message, param1, param2);
            return new AimpActionResult(ActionResultType.OK);
        }

        public event HookMessage OnCoreMessage;
    }

    public class ExtensionPlaylistManagerListener : IAimpExtension, IAimpExtensionPlaylistManagerListener
    {
        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }
    }

    [AimpPlugin("dotnet_demo", "Evgeniy Bogdan", AdditionalInfo.Version, AimpPluginType = AimpPluginType.Addons)]
    public class Plugin : AimpPlugin
    {
        private bool _checked;
        private PlayerForm _demoForm;

        private IAimpMenuItem _menuItem;
        private IAimpOptionsDialogFrame _optionsFrame;
        private MessageHook _hook;
        private OptionsDialogFrame _aimpOptionsDialogFrame;

        public override void Initialize()
        {
            TestWriteConfig();

            var listner = new ExtensionPlaylistManagerListener();
            var ext = new ExtensionPlaybackQueue();

            RegisterExtension(listner);
            RegisterExtension(ext);


            var result = Player.Core.CreateObject<IAimpMenuItem>();

            if (result.ResultType == ActionResultType.OK)
            {
                IAimpMenuItem demoFormItem = result.Result as IAimpMenuItem;

                demoFormItem.Name = "Open demo form";
                demoFormItem.Id = "demo_form";
                demoFormItem.Style = MenuItemStyle.CheckBox;

                demoFormItem.OnExecute += DemoFormItemOnOnExecute;
                demoFormItem.OnShow += (sender, args) =>
                {
                    var item = sender as IAimpMenuItem;
                };

                Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, demoFormItem);
            }

            _hook = new MessageHook();
            Player.ServiceMessageDispatcher.Hook(_hook);

            _demoForm = new PlayerForm(Player, _hook);

            CreateMenuWithAction();

            TestReadConfig();

            _aimpOptionsDialogFrame = new OptionsDialogFrame();
            Player.Core.RegisterExtension(_aimpOptionsDialogFrame);
        }

        private void DemoFormItemOnOnExecute(object sender, EventArgs eventArgs)
        {
            if (_demoForm.IsDisposed)
                _demoForm = new PlayerForm(Player, _hook);

            var item = sender as IAimpMenuItem;

            _demoForm.Show();
        }

        public override void Dispose()
        {
            _demoForm.Dispose();
            System.Diagnostics.Debug.WriteLine("Dispose");
            //Player.MenuManager.Delete(_menuItem);
            Player.ServiceMessageDispatcher.Unhook(_hook);
        }

        private void CreateMenuWithAction()
        {
            var menuItemResult = Player.Core.CreateAimpObject<IAimpMenuItem>();
            if (menuItemResult.ResultType == ActionResultType.OK)
            {
                IAimpMenuItem actionMenuItem = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;

                var action = Player.Core.CreateAimpObject<IAimpAction>().Result;
                action.Id = "aimp.MenuAndActionsDemo.action.1";
                action.Name = "Simple action title";
                action.GroupName = "Menu And Actions Demo";
                action.OnExecute += (sender, args) =>
                {
                    var item = sender as IAimpAction;
                };
                Player.ServiceActionManager.Register(action);

                actionMenuItem.Name = "Menu item with linked action";
                actionMenuItem.Id = "aimp.MenuAndActionsDemo.menuitem.with.action";
                actionMenuItem.Action = action;
                Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, actionMenuItem);

                var secondAction = Player.Core.CreateAimpObject<IAimpAction>().Result;
                secondAction.Id = Guid.NewGuid().ToString();
                secondAction.Name = "Action 2";
                secondAction.GroupName = "Menu And Actions Demo";
                secondAction.DefaultGlobalHotKey = Player.ServiceActionManager.MakeHotkey(ModifierKeys.Control,
                    (uint) KeyInterop.VirtualKeyFromKey(Key.B));
                Player.ServiceActionManager.Register(secondAction);

                var menuItem2 = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
                menuItem2.Id = Guid.NewGuid().ToString();
                menuItem2.Name = "Simple action 2";
                menuItem2.Action = secondAction;
                Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, menuItem2);
            }
        }

        private void TestWriteConfig()
        {
            Player.ServiceConfig.SetValueAsFloat("AIMP.DOTNET.DEMO\\FLOAT", 0.2f);
            Player.ServiceConfig.SetValueAsInt32("AIMP.DOTNET.DEMO\\INT32", 10);
            Player.ServiceConfig.SetValueAsInt64("AIMP.DOTNET.DEMO\\INT64", 20);
            Player.ServiceConfig.SetValueAsString("AIMP.DOTNET.DEMO\\STRING", "STRING");
            using (var stream = Player.Core.CreateStream().Result)
            {
                var buf = System.Text.Encoding.Default.GetBytes("STREAMDATA");
                int written;
                stream.Write(buf, buf.Length, out written);
                Player.ServiceConfig.SetValueAsStream("AIMP.DOTNET.DEMO\\STREAM", stream);
            }
        }

        private void TestReadConfig()
        {
            var floatValue = Player.ServiceConfig.GetValueAsFloat("AIMP.DOTNET.DEMO\\FLOAT");
            var int32Value = Player.ServiceConfig.GetValueAsInt32("AIMP.DOTNET.DEMO\\INT32");
            var int64Value = Player.ServiceConfig.GetValueAsInt64("AIMP.DOTNET.DEMO\\INT64");
            var stringValue = Player.ServiceConfig.GetValueAsString("AIMP.DOTNET.DEMO\\STRING");
            using (var streamValue = Player.ServiceConfig.GetValueAsStream("AIMP.DOTNET.DEMO\\STREAM").Result)
            {
                long count = streamValue.GetSize();
                var buf = new byte[count];
                streamValue.Read(buf, (int) count);
                var strData = System.Text.Encoding.Default.GetString(buf);
            }
        }

        private void RegisterExtension(IAimpExtension extension)
        {
            var res = Player.Core.RegisterExtension(extension);

            if (res.ResultType != ActionResultType.OK)
            {
                System.Diagnostics.Debugger.Break();
            }
        }
    }
}
