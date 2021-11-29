﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
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

namespace Aimp.TestRunner.UnitTests.MenuManager
{
    [TestFixture]
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

                var child = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
                child.Id = Guid.NewGuid().ToString();
                child.Name = "Child item";
                child.Parent = parent;

                var result = Player.ServiceMenuManager.Add(ParentMenuType.CommonUtilities, parent);

                this.AreEqual(ActionResultType.OK, result.ResultType, "Add item to menu");

                result = parent.DeleteChildren();
                this.AreEqual(ActionResultType.OK, result.ResultType, "Delete child items");
            });
        }
    }
}