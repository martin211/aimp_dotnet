using System;
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
                var ex = Assert.Throws<ArgumentNullException>(() => Player.ActionManager.Register(action));
                Assert.True(ex.Message.Contains("Action name cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Register_EmptyId_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var action = Player.ActionManager.CreateAction();
                action.Name = "Test";
                var ex = Assert.Throws<ArgumentNullException>(() => Player.ActionManager.Register(action));
                Assert.True(ex.Message.Contains("Action id cannot be empty"));
                return ActionResultType.OK;
            });
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

                Assert.AreEqual("Test", action.Name);
                Assert.AreEqual("integration.action.1", action.Id);
                Assert.AreEqual("integration", action.GroupName);
                Assert.AreEqual("custom data", action.CustomData);
                Assert.IsFalse(action.Enabled);

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
                Assert.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });
        }

        [Test, Order(2)]
        public void GetById_ShouldReturnAction()
        {
            ExecuteInMainThread(() =>
            {
                var actionResult = Player.ActionManager.GetById("integration.test");
                Assert.AreEqual(ActionResultType.OK, actionResult.ResultType);
                Assert.NotNull(actionResult.Result);
                Assert.AreEqual("integration.test", actionResult.Result.Id);
                Assert.AreEqual("test action", actionResult.Result.Name);
                return actionResult.ResultType;
            });
        }
    }
}