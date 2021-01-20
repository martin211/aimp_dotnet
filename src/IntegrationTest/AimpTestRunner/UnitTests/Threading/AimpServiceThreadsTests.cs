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
using System.Threading;
using AIMP.SDK;
using AIMP.SDK.Threading;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Threading
{
    [TestFixture]
    public class AimpServiceThreadsTests : AimpIntegrationTest
    {
        private class IntegrationTask : IAimpTask
        {
            private Action _action;

            public IntegrationTask()
            {
            }

            public IntegrationTask(Action action)
            {
                _action = action;
            }

            public AimpActionResult Execute(IAimpTaskOwner owner)
            {
                TestContext.WriteLine($"Execute task. IsCanceled: {owner.IsCanceled}");
                _action?.Invoke();

                return new AimpActionResult(ActionResultType.OK);
            }
        }

        [Test]
        public void ExecuteInMainThread_ShouldReturn_OK()
        {
            var task = new IntegrationTask();
            var r = Player.ServiceThreads.ExecuteInMainThread(task, true);
            this.AreEqual(ActionResultType.OK, r.ResultType, fieldName: "ExecuteInMainThread.ResultType");
        }

        [Test]
        public void ExecuteInThread_ShouldReturn_OK()
        {
            var task = new IntegrationTask();
            var r = Player.ServiceThreads.ExecuteInThread(task);
            this.AreEqual(ActionResultType.OK, r.ResultType, fieldName: "ExecuteInThread.ResultType");
        }

        [Test]
        public void Cancel_ShouldReturn_OK()
        {
            var task = new IntegrationTask(() =>
            {
                Thread.Sleep(TimeSpan.FromMinutes(2));
            });
            var r = Player.ServiceThreads.ExecuteInThread(task);
            this.AreEqual(ActionResultType.OK, r.ResultType, fieldName: "ExecuteInThread.ResultType");
            var cancelResult = Player.ServiceThreads.Cancel(r.Result, AimpServiceThreadPoolType.None);
            this.AreEqual(ActionResultType.OK, cancelResult.ResultType, fieldName: "ExecuteInThread.Cancel");
        }

        [Test]
        public void WaitFor_ShouldReturn_OK()
        {
            var task = new IntegrationTask(() =>
            {
                Thread.Sleep(TimeSpan.FromSeconds(5));
            });
            var r = Player.ServiceThreads.ExecuteInThread(task);
            this.AreEqual(ActionResultType.OK, r.ResultType, fieldName: "ExecuteInThread.ResultType");
            var waitResult = Player.ServiceThreads.WaitFor(r.Result);
            this.AreEqual(ActionResultType.OK, waitResult.ResultType, fieldName: "WaitFor.Cancel");
        }
    }
}
