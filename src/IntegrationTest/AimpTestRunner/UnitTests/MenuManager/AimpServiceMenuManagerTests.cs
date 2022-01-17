// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK;
using AIMP.SDK.MenuManager;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.MenuManager;

public class AimpServiceMenuManagerTests : AimpIntegrationTest
{
    [Test]
    public void Add_NoParentMenu_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>();
            var menuItem = item.Result;
            menuItem.Id = Guid.NewGuid().ToString();
            var result = Player.ServiceMenuManager.Add(menuItem);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);

            Player.ServiceMenuManager.Delete(menuItem);
        });
    }

    [TestCase(ParentMenuType.CommonUtilities, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.CommonUtilities, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.CommonUtilities, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlDeletion, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlDeletion, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlDeletion, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlMainDB, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlMainDB, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlMainDB, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlMainFunctions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlMainFunctions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlMainFunctions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlMainOpen, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlMainOpen, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlMainOpen, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.mlMainOptions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.mlMainOptions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.mlMainOptions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlMiscellaneous, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlMiscellaneous, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlMiscellaneous, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlTableContextAdding, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlTableContextAdding, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlTableContextAdding, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlTableContextDeletion, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlTableContextDeletion, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlTableContextDeletion, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlTableContextFunctions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlTableContextFunctions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlTableContextFunctions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlTableContextSending, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlTableContextSending, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlTableContextSending, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlTreeContextDeletion, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlTreeContextDeletion, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlTreeContextDeletion, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.MlTreeContextFunctions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.MlTreeContextFunctions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.MlTreeContextFunctions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerEqLib, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerEqLib, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerEqLib, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerTray, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerTray, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerTray, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerMainFunctions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerMainFunctions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerMainFunctions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerMainOpen, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerMainOpen, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerMainOpen, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerMainOpen, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerMainOpen, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerMainOpen, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerMainOptions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerMainOptions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerMainOptions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistAdding, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistAdding, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistAdding, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextAdding, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextAdding, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistContextAdding, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextDeletion, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextDeletion, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistContextDeletion, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextFunctions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextFunctions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistContextFunctions, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextQueue, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextQueue, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistContextQueue, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextSending, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistContextSending, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistContextSending, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistDeletion, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistDeletion, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistDeletion, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistManage, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistManage, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistManage, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistMiscellaneous, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistMiscellaneous, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistMiscellaneous, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerPlaylistSorting, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerPlaylistSorting, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerPlaylistSorting, MenuItemStyle.RadioBox)]
    [TestCase(ParentMenuType.PlayerStopOptions, MenuItemStyle.CheckBox)]
    [TestCase(ParentMenuType.PlayerStopOptions, MenuItemStyle.Normal)]
    [TestCase(ParentMenuType.PlayerStopOptions, MenuItemStyle.RadioBox)]
    public void Add_ParentMenu_ShouldReturnOK(ParentMenuType parentMenuType, MenuItemStyle menuItemStyle)
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>();
            var menuItem = item.Result;
            menuItem.Id = Guid.NewGuid().ToString();
            menuItem.Style = menuItemStyle;

            var result = Player.ServiceMenuManager.Add(parentMenuType, menuItem);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);

            var getItemResult = Player.ServiceMenuManager.GetById(menuItem.Id);
            AimpAssert.AreEqual(menuItemStyle, getItemResult.Result.Style);

            Player.ServiceMenuManager.Delete(menuItem);
        });
    }

    [Test]
    public void Delete_Item_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>();
            var menuItem = item.Result;
            menuItem.Id = Guid.NewGuid().ToString();
            Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, menuItem);
            var result = Player.ServiceMenuManager.Delete(menuItem);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    public void Delete_Id_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>();
            var menuItem = item.Result;
            menuItem.Id = "id_for_test";
            Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, menuItem);
            var result = Player.ServiceMenuManager.Delete("id_for_test");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    public void GetById_Id_ShouldReturnItem()
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>();
            var menuItem = item.Result;
            menuItem.Id = "id_for_test";
            Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, menuItem);
            var result = Player.ServiceMenuManager.GetById("id_for_test");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.NotNull(result.Result);
            Player.ServiceMenuManager.Delete(menuItem);
        });
    }

    [TestCase(ParentMenuType.CommonUtilities)]
    [TestCase(ParentMenuType.MlDeletion)]
    [TestCase(ParentMenuType.MlMainDB)]
    [TestCase(ParentMenuType.MlMainFunctions)]
    [TestCase(ParentMenuType.MlMainOpen)]
    [TestCase(ParentMenuType.mlMainOptions)]
    [TestCase(ParentMenuType.MlMiscellaneous)]
    [TestCase(ParentMenuType.MlTableContextAdding)]
    [TestCase(ParentMenuType.MlTableContextDeletion)]
    [TestCase(ParentMenuType.MlTableContextFunctions)]
    [TestCase(ParentMenuType.MlTableContextSending)]
    [TestCase(ParentMenuType.MlTreeContextDeletion)]
    [TestCase(ParentMenuType.MlTreeContextFunctions)]
    [TestCase(ParentMenuType.PlayerEqLib)]
    [TestCase(ParentMenuType.PlayerTray)]
    [TestCase(ParentMenuType.PlayerMainFunctions)]
    [TestCase(ParentMenuType.PlayerMainOpen)]
    [TestCase(ParentMenuType.PlayerMainOptions)]
    [TestCase(ParentMenuType.PlayerPlaylistAdding)]
    [TestCase(ParentMenuType.PlayerPlaylistContextAdding)]
    [TestCase(ParentMenuType.PlayerPlaylistContextDeletion)]
    [TestCase(ParentMenuType.PlayerPlaylistContextFunctions)]
    [TestCase(ParentMenuType.PlayerPlaylistContextQueue)]
    [TestCase(ParentMenuType.PlayerPlaylistContextSending)]
    [TestCase(ParentMenuType.PlayerPlaylistDeletion)]
    [TestCase(ParentMenuType.PlayerPlaylistManage)]
    [TestCase(ParentMenuType.PlayerPlaylistMiscellaneous)]
    [TestCase(ParentMenuType.PlayerPlaylistSorting)]
    [TestCase(ParentMenuType.PlayerStopOptions)]
    public void GetBuiltIn_ShouldReturnItem(ParentMenuType menuType)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceMenuManager.GetBuiltIn(menuType);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.NotNull(result.Result);
        });
    }

    [Test]
    public void Add_TwoLevel_ShouldBeCorrect()
    {
        ExecuteInMainThread(() =>
        {
            var parent = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            parent.Id = Guid.NewGuid().ToString();
            parent.Name = "Parent item";

            var child = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            child.Id = Guid.NewGuid().ToString();
            child.Name = "Child item";
            child.Parent = parent;

            var result = Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, parent);

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);

            var childResult = Player.ServiceMenuManager.GetById(child.Id);
            AimpAssert.NotNull(childResult.Result.Parent);
            AimpAssert.AreEqual(childResult.Result.Parent.Id, parent.Id);
        });
    }
}
