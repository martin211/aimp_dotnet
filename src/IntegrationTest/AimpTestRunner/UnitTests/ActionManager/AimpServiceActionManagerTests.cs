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
using System.Linq;
using AIMP.SDK;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.ActionManager
{
    [TestFixture]
    public class AimpServiceActionManagerTests : AimpIntegrationTest
    {
        [Test]
        public void CreateAction_ShouldReturnEmptyAction()
        {
            var action = Player.ActionManager.CreateAction();
            Assert.NotNull(action);
        }

        [Test]
        public void Register_EmptyName_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var action = Player.ActionManager.CreateAction();
                this.Throw<ArgumentNullException>(() => Player.ActionManager.Register(action));

                return ActionResultType.OK;
            });

            Validate();
            Assert.True((Asserts.First() as ThrowAssert<ArgumentNullException>)?.CatchedException.Message.Contains("Action name cannot be empty"));
        }

        [Test]
        public void Register_EmptyId_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var action = Player.ActionManager.CreateAction();
                action.Name = "Test";
                this.Throw<ArgumentNullException>(() => Player.ActionManager.Register(action));
                return ActionResultType.OK;
            });

            Validate();
            Assert.True((Asserts.First() as ThrowAssert<ArgumentNullException>)?.CatchedException.Message.Contains("Action id cannot be empty"));
        }

        [Test(Description = "Set and get all properties. Ensure that they all are correct.")]
        public void AimpAction_EnsureThatAllFieldsCorrect()
        {
            ExecuteInMainThread(() =>
            {
                var action = Player.ActionManager.CreateAction();
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

                return ActionResultType.OK;
            });
        }

        [Test, Order(1)]
        public void Register_ShouldRegisterAction()
        {
            ExecuteInMainThread(() =>
            {
                var action = Player.ActionManager.CreateAction();
                action.Name = "test action";
                action.Id = "integration.test";

                var result = Player.ActionManager.Register(action);

                this.AreEqual(ActionResultType.OK, () => result.ResultType);

                return result.ResultType;
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

                return actionResult.ResultType;
            });
        }
    }
}