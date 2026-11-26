using System;
using System.Windows.Input;
using AIMP.SDK;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.MenuManager;
using AIMP.SDK.MenuManager.Objects;

namespace Aimp.SamplePlugin;

[AimpPlugin("DotNetDemo", "Martin", "1.0.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "DotNet general demo plugin")]
public class Plugin : AimpPlugin
{
    public override void Initialize()
    {
        CreateMenuWithAction();
    }

    public override void Dispose()
    {
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
}