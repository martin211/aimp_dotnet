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
using AIMP.SDK.MessageDispatcher;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.MessageDispatcher
{
    [TestFixture]
    public class AimpServiceMessageDispatcherTests : AimpIntegrationTest
    {
        private class TestHook : IAimpMessageHook
        {
            public AimpActionResult CoreMessage(AimpCoreMessageType message, int param1, int param2)
            {
                return new AimpActionResult(ActionResultType.OK);
            }
        }

        [Test]
        public void Send_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceMessageDispatcher.Send(AimpCoreMessageType.CmdPause, 0, IntPtr.Zero);
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        [Test]
        public void Register_EmptyMessage_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                this.Throw<ArgumentNullException>(() => Player.ServiceMessageDispatcher.Register(string.Empty));
            });
        }

        [Test]
        public void Register_ShouldReturnMessageId()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceMessageDispatcher.Register("Test");
                this.IsTrue(result > 0);
            });
        }

        [Test]
        public void Hook_Null_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                this.Throw<ArgumentNullException>(() => Player.ServiceMessageDispatcher.Hook(null));
            });
        }

        [Test]
        public void Hook_ShouldSetHook()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceMessageDispatcher.Hook(new TestHook());
                this.AreEqual(ActionResultType.OK, result.ResultType, "Cannot hook a new hook");
            });
        }

        [Test]
        public void Unhook_ShouldUnhook()
        {
            ExecuteInMainThread(() =>
            {
                var hook = new TestHook();

                Player.ServiceMessageDispatcher.Hook(hook);

                var result = Player.ServiceMessageDispatcher.Unhook(hook);
                this.AreEqual(ActionResultType.OK, result.ResultType, "Cannot unhook a hook");
            });
        }
    }
}