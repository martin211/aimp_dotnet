// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.MenuManager;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.MenuManager
{
    [TestFixture]
    public class AimpServiceMenuManagerTests : AimpIntegrationTest
    {
        [Test]
        public void Add_NoParentMenu_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var item = Player.Core.CreateObject<IAimpMenuItem>();
                var menuItem = item.Result as IAimpMenuItem;
                menuItem.Id = System.Guid.NewGuid().ToString();
                var result = Player.MenuManager.Add(menuItem);
                this.AreEqual(ActionResultType.OK, result.ResultType);

                Player.MenuManager.Delete(menuItem);
                return result.ResultType;
            });
        }

        [TestCase(ParentMenuType.CommonUtilites, MenuItemStyle.CheckBox)]
        [TestCase(ParentMenuType.CommonUtilites, MenuItemStyle.Normal)]
        [TestCase(ParentMenuType.CommonUtilites, MenuItemStyle.RadioBox)]

        [TestCase(ParentMenuType.MlDeletion, MenuItemStyle.CheckBox)]
        [TestCase(ParentMenuType.MlDeletion, MenuItemStyle.Normal)]
        [TestCase(ParentMenuType.MlDeletion, MenuItemStyle.RadioBox)]

        [TestCase(ParentMenuType.MlMainDB, MenuItemStyle.CheckBox)]
        [TestCase(ParentMenuType.MlMainDB, MenuItemStyle.Normal)]
        [TestCase(ParentMenuType.MlMainDB, MenuItemStyle.RadioBox)]

        [TestCase(ParentMenuType.MlMainFuntions, MenuItemStyle.CheckBox)]
        [TestCase(ParentMenuType.MlMainFuntions, MenuItemStyle.Normal)]
        [TestCase(ParentMenuType.MlMainFuntions, MenuItemStyle.RadioBox)]

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
                var item = Player.Core.CreateObject<IAimpMenuItem>();
                var menuItem = item.Result as IAimpMenuItem;
                menuItem.Id = System.Guid.NewGuid().ToString();
                menuItem.Style = menuItemStyle;

                var result = Player.MenuManager.Add(parentMenuType, menuItem);
                this.AreEqual(ActionResultType.OK, result.ResultType);

                var getItemResult = Player.MenuManager.GetById(menuItem.Id);
                this.AreEqual(menuItemStyle, getItemResult.Result.Style);
                this.AreEqual(parentMenuType, getItemResult.Result.Parent.Style);

                Player.MenuManager.Delete(menuItem);
                return result.ResultType;
            });
        }

        [Test]
        public void Delete_Item_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var item = Player.Core.CreateObject<IAimpMenuItem>();
                var menuItem = item.Result as IAimpMenuItem;
                menuItem.Id = System.Guid.NewGuid().ToString();
                Player.MenuManager.Add(ParentMenuType.CommonUtilites, menuItem);
                var result = Player.MenuManager.Delete(menuItem);
                this.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });
        }

        [Test]
        public void Delete_Id_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var item = Player.Core.CreateObject<IAimpMenuItem>();
                var menuItem = item.Result as IAimpMenuItem;
                menuItem.Id = "id_for_test";
                Player.MenuManager.Add(ParentMenuType.CommonUtilites, menuItem);
                var result = Player.MenuManager.Delete("id_for_test");
                this.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });
        }

        [Test]
        public void GetById_Id_ShouldReturnItem()
        {
            ExecuteInMainThread(() =>
            {
                var item = Player.Core.CreateObject<IAimpMenuItem>();
                var menuItem = item.Result as IAimpMenuItem;
                menuItem.Id = "id_for_test";
                Player.MenuManager.Add(ParentMenuType.CommonUtilites, menuItem);
                var result = Player.MenuManager.GetById("id_for_test");
                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);
                Player.MenuManager.Delete(menuItem);
                return result.ResultType;
            });
        }

        [TestCase(ParentMenuType.CommonUtilites)]

        [TestCase(ParentMenuType.MlDeletion)]
        [TestCase(ParentMenuType.MlMainDB)]
        [TestCase(ParentMenuType.MlMainFuntions)]
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
                var result = Player.MenuManager.GetBuiltIn(menuType);
                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);

                return result.ResultType;
            });
        }
    }
}