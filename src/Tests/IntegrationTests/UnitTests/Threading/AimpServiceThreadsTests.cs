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
using System.Threading;
using AIMP.SDK;
using AIMP.SDK.Threading;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Threading;

[TestFixture(Category = "ServiceThreads")]
public class AimpServiceThreadsTests : AimpIntegrationTest
{
    private class IntegrationTask : IAimpTask
    {
        private readonly Action _action;

        public IntegrationTask()
        {
        }

        public IntegrationTask(Action action)
        {
            _action = action;
        }

        public void Execute(IAimpTaskOwner owner)
        {
            TestContext.WriteLine($"Execute task. IsCanceled: {owner.IsCanceled}");
            _action?.Invoke();
        }
    }

    [Test]
    public void ExecuteInMainThread_ShouldReturn_OK()
    {
        var task = new IntegrationTask();
        var r = Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.None);
        AimpAssert.AreEqual(ActionResultType.OK, r.ResultType, "ExecuteInMainThread.ResultType");
    }

    [Test]
    public void ExecuteInThread_ShouldReturn_OK()
    {
        var task = new IntegrationTask();
        var r = Player.ServiceThreads.ExecuteInThread(task);
        AimpAssert.AreEqual(ActionResultType.OK, r.ResultType, "ExecuteInThread.ResultType");
    }

    [Test]
    public void Cancel_ShouldReturn_OK()
    {
        var task = new IntegrationTask(() => { Thread.Sleep(TimeSpan.FromMinutes(2)); });
        var r = Player.ServiceThreads.ExecuteInThread(task);
        AimpAssert.AreEqual(ActionResultType.OK, r.ResultType, "ExecuteInThread.ResultType");
        var cancelResult = Player.ServiceThreads.Cancel(r.Result, AimpServiceThreadPoolType.None);
        AimpAssert.AreEqual(ActionResultType.OK, cancelResult.ResultType, "ExecuteInThread.Cancel");
    }

    [Test]
    public void WaitFor_ShouldReturn_OK()
    {
        var task = new IntegrationTask(() => { Thread.Sleep(TimeSpan.FromSeconds(5)); });
        var r = Player.ServiceThreads.ExecuteInThread(task);
        AimpAssert.AreEqual(ActionResultType.OK, r.ResultType, "ExecuteInThread.ResultType");
        var waitResult = Player.ServiceThreads.WaitFor(r.Result);
        AimpAssert.AreEqual(ActionResultType.OK, waitResult.ResultType, "WaitFor.Cancel");
    }
}
