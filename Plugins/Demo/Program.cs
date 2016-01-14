using System.Windows.Forms;

namespace TestPlugin
{
    using AIMP.SDK;
    using AIMP.SDK.MenuManager;
    using AIMP.SDK.Options;
    using AIMP.SDK.UI.ActionItem;
    using AIMP.SDK.UI.MenuItem;

    [AimpPlugin("dotnet_demo", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons)]
    public class Program : AimpPlugin
    {
        private Form1 _demoForm;
        private IAimpOptionsDialogFrame _optionsFrame;

        private StandartMenuItem _menuItem;

        public override void Initialize()
        {
            //Player.Core.CoreMessage += (param1, param2) =>
            //    {
            //        System.Diagnostics.Debug.WriteLine("Demo plugin: Player.Core.CoreMessage");
            //    };
            //_demoForm = new Form1(Player);

            _menuItem = new StandartMenuItem("Demo plugin");
            //_menuItem.BeforeShow += (sender, args) =>
            //    {

            //    };

            //_menuItem.Click += (sender, args) =>
            //    {
            //        var m = Player.MenuManager.GetBuiltIn(ParentMenuType.AIMP_MENUID_PLAYER_MAIN_FUNCTIONS);
            //        _demoForm.Show();
            //    };

            Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, _menuItem);
            //var action = new AimpActionItem("Teset action", "test Group");
            //Player.ActionManager.Add(action);

            //_optionsFrame = new OptionsFrame(Player);
            //Player.Core.RegisterExtension(_optionsFrame);
        }

        public override void Dispose()
        {
            System.Diagnostics.Debug.WriteLine("Dispose");
            Player.MenuManager.Delete(_menuItem);
        }
    }
}
