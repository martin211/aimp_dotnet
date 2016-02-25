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
            if (Player.MenuManager.CreateMenuItem(out _menuItem) == AimpActionResult.Ok)
            {
                _menuItem.Name = "Normal menu item";
                _menuItem.Id = "demo_item";
                _menuItem.Visible = true;
                _menuItem.Enabled = true;
                _menuItem.Style = AimpMenuItemStyle.Normal;

                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, _menuItem);
            }

            IAimpMenuItem checkedMenu;
            if (Player.MenuManager.CreateMenuItem(out checkedMenu) == AimpActionResult.Ok)
            {
                checkedMenu.Style = AimpMenuItemStyle.CheckBox;
                checkedMenu.Name = "CheckBox menu item";
                checkedMenu.Id = "CheckBox_menu_item";
                checkedMenu.OnExecute += (sender, args) =>
                {
                    _checked = !_checked;
                    checkedMenu.Checked = _checked;
                };

                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, checkedMenu);
            }

            IAimpMenuItem radioButtonMenu;
            if (Player.MenuManager.CreateMenuItem(out radioButtonMenu) == AimpActionResult.Ok)
            {
                radioButtonMenu.Style = AimpMenuItemStyle.RadioBox;
                radioButtonMenu.Name = "RadioBox menu item";
                radioButtonMenu.Id = "RadioBox_menu_item";

                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, radioButtonMenu);
            }

            IAimpMenuItem subItem1;
            if (Player.MenuManager.CreateMenuItem(out subItem1) == AimpActionResult.Ok)
            {
                subItem1.Name = "Sub item1";
                subItem1.Id = "Sub_item_1";
                subItem1.Style = AimpMenuItemStyle.Normal;
                subItem1.Parent = _menuItem;

                Player.MenuManager.Add(subItem1);
            }
        }

        public override void Dispose()
        {
            System.Diagnostics.Debug.WriteLine("Dispose");
            Player.MenuManager.Delete(_menuItem);
        }
    }
}
