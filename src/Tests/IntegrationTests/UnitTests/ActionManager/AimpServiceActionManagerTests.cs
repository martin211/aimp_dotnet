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
using AIMP.SDK.Actions.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.ActionManager;

[TestFixture(Category = "ServiceActionManager")]
public class AimpServiceActionManagerTests : AimpIntegrationTest
{
    [Test]
    public void CreateAction_ShouldReturnEmptyAction()
    {
        ExecuteInMainThread(() =>
        {
            var actionResult = Player.Core.CreateObject<IAimpAction>();
            AssertOKResult(actionResult);

            var action = actionResult.Result as IAimpAction;
            AimpAssert.NotNull(action);
        });
    }

    [Test]
    public void Register_EmptyName_ShouldThrowException()
    {
        ExecuteInMainThread(() =>
        {
            var actionResult = Player.Core.CreateObject<IAimpAction>();
            AssertOKResult(actionResult);

            var action = actionResult.Result as IAimpAction;
            AimpAssert.NotNull(action);

            var exception = AimpAssert.Throw<ArgumentNullException>(() => Player.ServiceActionManager.Register(action));
            AimpAssert.IsTrue(exception.Message.Contains("Action name cannot be empty"));
        });
    }

    [Test]
    public void Register_EmptyId_ShouldThrowException()
    {
        ExecuteInMainThread(() =>
        {
            var actionResult = Player.Core.CreateObject<IAimpAction>();
            AssertOKResult(actionResult);

            var action = actionResult.Result as IAimpAction;
            AimpAssert.NotNull(action);

            action.Name = "Test";
            var exception = AimpAssert.Throw<ArgumentNullException>(() => Player.ServiceActionManager.Register(action));
            AimpAssert.IsTrue(exception.Message.Contains("Action id cannot be empty"));
        });
    }

    [Test(Description = "Set and get all properties. Ensure that they all are correct.")]
    public void AimpAction_EnsureThatAllFieldsCorrect()
    {
        ExecuteInMainThread(() =>
        {
            var actionResult = Player.Core.CreateObject<IAimpAction>();
            var action = actionResult.Result as IAimpAction;
            AimpAssert.NotNull(action);

            action.Name = "Test";
            action.Id = "integration.action.1";
            action.GroupName = "integration";
            action.Enabled = false;
            action.OnExecute += (sender, args) => { };
            action.CustomData = "custom data";

            AimpAssert.AreEqual("Test", () => action.Name);
            AimpAssert.AreEqual("integration.action.1", () => action.Id);
            AimpAssert.AreEqual("integration", () => action.GroupName);
            AimpAssert.AreEqual("custom data", () => action.CustomData);
        });
    }

    [Test]
    [Order(1)]
    public void Register_ShouldRegisterAction()
    {
        ExecuteInMainThread(() =>
        {
            var actionResult = Player.Core.CreateObject<IAimpAction>();
            var action = actionResult.Result as IAimpAction;
            AimpAssert.NotNull(action);

            //var action = Player.ActionManager.CreateAction();
            action.Name = "test action";
            action.Id = "integration.test";

            var result = Player.ServiceActionManager.Register(action);

            AimpAssert.AreEqual(ActionResultType.OK, () => result.ResultType);
        });
    }

    [Test]
    [Order(2)]
    public void GetById_ShouldReturnAction()
    {
        ExecuteInMainThread(() =>
        {
            var actionResult = Player.ServiceActionManager.GetById("integration.test");
            AssertOKResult(actionResult);
            AimpAssert.AreEqual("integration.test", () => actionResult.Result.Id);
            AimpAssert.AreEqual("test action", () => actionResult.Result.Name);
        });
    }
}
