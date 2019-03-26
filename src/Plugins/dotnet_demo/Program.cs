// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System;
using System.Diagnostics;
using System.Threading;
using AIMP.SDK.ActionManager;
using AIMP.SDK.Playlist;
using DemoPlugin;

namespace TestPlugin
{
    using AIMP.SDK;
    using AIMP.SDK.MenuManager;
    using AIMP.SDK.Options;

    public class ExtensionPlaylistManagerListener : IAimpExtension, IAimpExtensionPlaylistManagerListener
    {
        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }
    }

    [AimpPlugin("dotnet_demo", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons)]
    public class Program : AimpPlugin
    {
        private bool _checked;
        private PlayerForm _demoForm;

        private IAimpMenuItem _menuItem;
        private IAimpOptionsDialogFrame _optionsFrame;

        public override void Initialize()
        {
            TestWriteConfig();

            IAimpMenuItem demoFormItem;

            var listner = new ExtensionPlaylistManagerListener();
            Player.Core.RegisterExtension(listner);

            if (Player.MenuManager.CreateMenuItem(out demoFormItem) == AimpActionResult.Ok)
            {
                demoFormItem.Name = "Open demo form";
                demoFormItem.Id = "demo_form";
                demoFormItem.Style = AimpMenuItemStyle.CheckBox;

                demoFormItem.OnExecute += DemoFormItemOnOnExecute;
                demoFormItem.OnShow += (sender, args) =>
                {
                    var item = sender as IAimpMenuItem;
                    Logger.Instance.AddInfoMessage($"Event: [Show] {item.Id}");
                };

                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, demoFormItem);
            }

            _demoForm = new PlayerForm(Player);

            CreateMenuWithAction();

            TestReadConfig();
        }

        private void DemoFormItemOnOnExecute(object sender, EventArgs eventArgs)
        {
            if (_demoForm.IsDisposed)
                _demoForm = new PlayerForm(Player);

            var item = sender as IAimpMenuItem;
            Logger.Instance.AddInfoMessage($"Event: [Execute] {item.Id}");

            _demoForm.Show();
        }

        public override void Dispose()
        {
            _demoForm.Dispose();
            System.Diagnostics.Debug.WriteLine("Dispose");
            //Player.MenuManager.Delete(_menuItem);
        }

        private void CreateMenuWithAction()
        {
            IAimpMenuItem actionMenuItem;
            if (Player.MenuManager.CreateMenuItem(out actionMenuItem) == AimpActionResult.Ok)
            {

                IAimpAction action = Player.ActionManager.CreateAction();
                action.Id = "aimp.MenuAndActionsDemo.action.1";
                action.Name = "Simple action title";
                action.GroupName = "Menu And Actions Demo";
                action.OnExecute += (sender, args) =>
                {
                    var item = sender as IAimpAction;
                    Logger.Instance.AddInfoMessage($"Event: [Execute] {item.Id}");
                };
                Player.ActionManager.Register(action);

                actionMenuItem.Name = "Menu item with linked action";
                actionMenuItem.Id = "aimp.MenuAndActionsDemo.menuitem.with.action";
                actionMenuItem.Action = action;
                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, actionMenuItem);
            }
        }

        private void TestWriteConfig()
        {
            Player.ServiceConfig.SetValueAsFloat("AIMP.DOTNET.DEMO\\FLOAT", 0.2f);
            Player.ServiceConfig.SetValueAsInt32("AIMP.DOTNET.DEMO\\INT32", 10);
            Player.ServiceConfig.SetValueAsInt64("AIMP.DOTNET.DEMO\\INT64", 20);
            Player.ServiceConfig.SetValueAsString("AIMP.DOTNET.DEMO\\STRING", "STRING");
            using (var stream = Player.Core.CreateStream())
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
            Debug.Assert(floatValue == 0.2f);
            var int32Value = Player.ServiceConfig.GetValueAsInt32("AIMP.DOTNET.DEMO\\INT32");
            Debug.Assert(int32Value == 10);
            var int64Value = Player.ServiceConfig.GetValueAsInt64("AIMP.DOTNET.DEMO\\INT64");
            Debug.Assert(int64Value == 20);
            var stringValue = Player.ServiceConfig.GetValueAsString("AIMP.DOTNET.DEMO\\STRING");
            Debug.Assert(stringValue.Equals("STRING"));
            using (var streamValue = Player.ServiceConfig.GetValueAsStream("AIMP.DOTNET.DEMO\\STREAM"))
            {
                long count = streamValue.GetSize();
                var buf = new byte[count];
                streamValue.Read(buf, (int) count);
                var strData = System.Text.Encoding.Default.GetString(buf);
                Debug.Assert(strData.Equals("STREAMDATA"));
            }
        }
    }
}
