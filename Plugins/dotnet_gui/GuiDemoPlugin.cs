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
        IAimpUIForm _form;

        #region Overrides of AimpPlugin

        /// <summary>
        /// Inside this function, plugin should perform all initialization
        /// </summary>
        public override void Initialize()
        {
            IAimpMenuItem menuItem;
            if (Player.MenuManager.CreateMenuItem(out menuItem) == AimpActionResult.Ok)
            {
                menuItem.Enabled = true;
                menuItem.Visible = true;
                menuItem.Name = "Test form";
                menuItem.Id = "test_form";
                menuItem.OnExecute += MenuItem_OnExecute;
                Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_COMMON_UTILITIES, menuItem);
            }
        }

        private void MenuItem_OnExecute(object sender, System.EventArgs e)
        {
            var aimpHandle = Player.Win32Manager.GetAimpHandle();

            AimpActionResult res = Player.ServiceUI.CreateForm(aimpHandle, CreateFormFlags.None, "Test", out _form);
            //form.ShowTasksBar = true;
            //form.CloseByEscape = true;
            _form.Show();

            //form.OnCreated += control =>
            //{
            //    Debugger.Break();
            //};

            //form.OnMouseDown += (control, clickArgs) =>
            //{
            //    Debugger.Break();
            //};
        }

        /// <summary>
        /// Inside this function, plugin should dispose all resources
        /// </summary>
        public override void Dispose()
        {
            _form.Release(false);
        }

        #endregion
    }
}
