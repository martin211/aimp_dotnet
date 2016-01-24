namespace DotnetGui
{
    using System.Diagnostics;

    using AIMP.SDK;
    using AIMP.SDK.GUI;
    using AIMP.SDK.GUI.Controls.Form;
    using AIMP.SDK.MenuManager;

    [AimpPlugin("dotnet_gui", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons)]
    public class GuiDemoPlugin : AimpPlugin
    {
        #region Overrides of AimpPlugin

        /// <summary>
        /// Inside this function, plugin should perform all initialization
        /// </summary>
        public override void Initialize()
        {
            IAimpMenuItem menuItem;
            if (Player.MenuManager.CreateMenuItem(out menuItem) == AimpActionResult.Ok)
            {
                menuItem.OnExecute += (sender, args) =>
                {
                    var aimpHandle = Player.Win32Manager.GetAimpHandle();
                    IAimpUIForm form;
                    AimpActionResult res = Player.ServiceUI.CreateForm(aimpHandle, CreateFormFlags.None, "Test", out form);
                    form.ShowTasksBar = true;
                    form.CloseByEscape = true;
                    form.Show();

                    form.OnCreated += control =>
                    {
                        Debugger.Break();
                    };

                    form.OnMouseDown += (control, clickArgs) =>
                    {
                        Debugger.Break();
                    };
                };

                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, menuItem);
            }
        }

        /// <summary>
        /// Inside this function, plugin should dispose all resources
        /// </summary>
        public override void Dispose()
        {

        }

        #endregion
    }
}
