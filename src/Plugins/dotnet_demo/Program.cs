using System;
using System.Diagnostics;
using AIMP.SDK.ActionManager;
using DemoPlugin;

namespace TestPlugin
{
    using AIMP.SDK;
    using AIMP.SDK.MenuManager;
    using AIMP.SDK.Options;

    [AimpPlugin("dotnet_demo", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons)]
    public class Program : AimpPlugin
    {
        private PlayerForm _demoForm;
        private IAimpOptionsDialogFrame _optionsFrame;

        private IAimpMenuItem _menuItem;

        private bool _checked;

        public override void Initialize()
        {
            IAimpMenuItem demoFormItem;
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
            Player.MenuManager.Delete(_menuItem);
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
    }
}
