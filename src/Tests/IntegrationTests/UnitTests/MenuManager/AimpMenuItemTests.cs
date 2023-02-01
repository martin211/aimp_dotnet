//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK;
using AIMP.SDK.MenuManager;
using AIMP.SDK.MenuManager.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.MenuManager;

[TestFixture(Category = "MenuItem")]
public class AimpMenuItemTests : AimpIntegrationTest
{
    [Test]
    public void DeleteChildren_ShouldDeleteChildrenItems()
    {
        ExecuteInMainThread(() =>
        {
            var parent = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            parent.Id = Guid.NewGuid().ToString();
            parent.Name = "Parent item";

            var result = Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, parent);

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Add item to menu");

            var child = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            child.Id = Guid.NewGuid().ToString();
            child.Name = "Child item";
            child.Parent = parent;

            result = parent.DeleteChildren();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Delete child items");
        });
    }

    [Test]
    public void Enabled_True_ShouldBeCorrect()
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            item.Id = Guid.NewGuid().ToString();
            item.Name = "Parent item";

            item.Enabled = true;
            AimpAssert.IsTrue(item.Enabled);
        });
    }

    [Test]
    public void Enabled_False_ShouldBeCorrect()
    {
        ExecuteInMainThread(() =>
        {
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            item.Id = Guid.NewGuid().ToString();
            item.Name = "Parent item";

            item.Enabled = false;
            AimpAssert.IsFalse(item.Enabled);
        });
    }
}
