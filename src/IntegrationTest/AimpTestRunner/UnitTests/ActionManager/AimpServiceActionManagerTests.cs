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

using System;
using AIMP.SDK;
using AIMP.SDK.ActionManager;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.ActionManager
{
    [TestFixture]
    public class AimpServiceActionManagerTests : AimpIntegrationTest
    {
        [Test]
        public void CreateAction_ShouldReturnEmptyAction()
        {
            var actionResult = Player.Core.CreateObject<IAimpAction>();
            var action = actionResult.Result as IAimpAction;
            this.NotNull(action);

            Assert.NotNull(action);
        }

        [Test]
        public void Register_EmptyName_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var actionResult = Player.Core.CreateObject<IAimpAction>();
                var action = actionResult.Result as IAimpAction;
                this.NotNull(action);

                var exception = this.Throw<ArgumentNullException>(() => Player.ActionManager.Register(action));
                this.IsTrue(exception.Message.Contains("Action name cannot be empty"));
            });
        }

        [Test]
        public void Register_EmptyId_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var actionResult = Player.Core.CreateObject<IAimpAction>();
                var action = actionResult.Result as IAimpAction;
                this.NotNull(action);

                action.Name = "Test";
                var exception = this.Throw<ArgumentNullException>(() => Player.ActionManager.Register(action));
                this.IsTrue(exception.Message.Contains("Action id cannot be empty"));
            });
        }

        [Test(Description = "Set and get all properties. Ensure that they all are correct.")]
        public void AimpAction_EnsureThatAllFieldsCorrect()
        {
            ExecuteInMainThread(() =>
            {
                var actionResult = Player.Core.CreateObject<IAimpAction>();
                var action = actionResult.Result as IAimpAction;
                this.NotNull(action);

                action.Name = "Test";
                action.Id = "integration.action.1";
                action.GroupName = "integration";
                action.Enabled = false;
                action.OnExecute += (sender, args) => { };
                action.CustomData = "custom data";

                this.AreEqual("Test", () => action.Name);
                this.AreEqual("integration.action.1", () => action.Id);
                this.AreEqual("integration", () => action.GroupName);
                this.AreEqual("custom data", () => action.CustomData);
            });
        }

        [Test, Order(1)]
        public void Register_ShouldRegisterAction()
        {
            ExecuteInMainThread(() =>
            {
                var actionResult = Player.Core.CreateObject<IAimpAction>();
                var action = actionResult.Result as IAimpAction;
                this.NotNull(action);

                //var action = Player.ActionManager.CreateAction();
                action.Name = "test action";
                action.Id = "integration.test";

                var result = Player.ActionManager.Register(action);

                this.AreEqual(ActionResultType.OK, () => result.ResultType);
            });
        }

        [Test, Order(2)]
        public void GetById_ShouldReturnAction()
        {
            ExecuteInMainThread(() =>
            {
                var actionResult = Player.ActionManager.GetById("integration.test");

                this.AreEqual(ActionResultType.OK, () => actionResult.ResultType);
                this.NotNull(() => actionResult.Result);
                this.AreEqual("integration.test", () => actionResult.Result.Id);
                this.AreEqual("test action", () => actionResult.Result.Name);
            });
        }
    }
}