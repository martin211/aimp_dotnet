using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TestPlugin
{
    using AIMP.SDK;
    using AIMP.SDK.Services.AlbumArtManager;
    using AIMP.SDK.Services.MenuManager;
    using AIMP.SDK.UI.ActionItem;
    using AIMP.SDK.UI.MenuItem;

    [AimpPlugin("dotNetInteropTest", "Evegniy Bogdan", "1")]
    public class Program : AimpPlugin
    {
        private Form1 _demoForm;

        public override void ShowSettingDialog(IWin32Window ParentWnd)
        {
            
        }

        public override void Initialize()
        {
            Player.Core.CoreMessage += (param1, param2) =>
                {
                    System.Diagnostics.Debug.WriteLine("Demo plugin: Player.Core.CoreMessage");
                };
            _demoForm = new Form1(Player);
            
            var menuItem = new StandartMenuItem("Demo plugin");
            menuItem.BeforeShow += (sender, args) =>
                {
                    
                };

            menuItem.Click += (sender, args) =>
                {
                    var m = Player.MenuManager.GetBuiltIn(ParentMenuType.AIMP_MENUID_PLAYER_MAIN_FUNCTIONS);
                _demoForm.Show();
            };

            Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, menuItem);
            var action = new AimpActionItem("Teset action", "test Group");
            Player.ActionManager.Add(action);
        }

        public override void Dispose()
        {
            System.Diagnostics.Debug.WriteLine("Dispose");
        }

        public override bool HasSettingDialog
        {
            get
            {
                return false;
            }
        }
    }
}
