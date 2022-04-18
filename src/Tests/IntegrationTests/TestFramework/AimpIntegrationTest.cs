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
using System.Collections.Generic;
using System.IO;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Threading;
using Aimp.TestRunner.TestFramework.Assert;
using Aimp.TestRunner.UnitTests;
using NUnit.Engine;
using NUnit.Framework;
using NUnit.Framework.Interfaces;
using NUnit.Framework.Internal;

namespace Aimp.TestRunner.TestFramework;

[TestFixture]
public abstract class AimpIntegrationTest
{
    [OneTimeSetUp]
    public virtual void RunBeforeAnyTests()
    {
        NUnit.Framework.Assert.NotNull(Player);
        Asserts = new List<IMemberAssert>();
        ClearAimpBeforeTests();
    }

    [OneTimeTearDown]
    public virtual void AfterAllTests()
    {
    }

    [SetUp]
    public virtual void SetUp()
    {
        Asserts.Clear();
    }

    [TearDown]
    public virtual void TearDown()
    {
        if (Asserts != null && Asserts.Count > 0) Validate(this);
    }

    public bool IsValid { get; set; } = true;

    internal string RootPath { get; }

    internal string TmpPath { get; }

    internal string PlaylistPath { get; }

    internal string TrackPath1 { get; }

    internal string TrackPath2 { get; }

    internal string TrackPath3 { get; }

    internal string TrackPath4 { get; }

    internal string TrackUrl1 { get; }

    internal string ImagePath1 { get; }

    internal IList<IMemberAssert> Asserts { get; set; }

    protected IAimpPlayer Player { get; }

    protected AimpIntegrationTest()
    {
        Player = AimpTestContext.Instance.AimpPlayer;

        if (Player == null)
            throw new NUnitEngineException(
                "Unable to run unit tests. Check that file 'nunit.engine.addins' exists in plugin folder.");

        RootPath = Path.Combine(Player.Core.GetPath(AimpCorePathType.Plugins), "AimpTestRunner");
        PlaylistPath = Path.Combine(RootPath, "resources", "IntegrationTests.aimppl4");
        TrackPath1 = Path.Combine(RootPath, "resources", "01_atmosphere.mp3");
        TrackPath2 = Path.Combine(RootPath, "resources", "02_loop-mix.mp3");
        TrackPath3 = Path.Combine(RootPath, "resources", "03_atmosphere.mp3");
        TrackPath4 = Path.Combine(RootPath, "resources", "04_loop-mix.mp3");
        ImagePath1 = Path.Combine(RootPath, "resources", "img1.jpg");
        TrackUrl1 = "https://freesound.org/data/previews/514/514101_4397472-lq.mp3";
        TmpPath = Path.Combine(RootPath, "tmp");

        if (Directory.Exists(TmpPath))
        {
            var files = Directory.GetFiles(TmpPath);

            foreach (var file in files)
            {
                File.SetAttributes(file, FileAttributes.Normal);
                File.Delete(file);
            }

            Directory.Delete(TmpPath, true);
        }

        Directory.CreateDirectory(TmpPath);
        Asserts = new List<IMemberAssert>(5);
    }

    protected AimpActionResult ExecuteInMainThreadAndWait(Action action)
    {
        var task = new AimpTask(action);
        var result = Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.WaitFor);
        return result;
    }

    protected AimpActionResult ExecuteInMainThread(Func<AimpActionResult> testFunc)
    {
        var task = new AimpTask(testFunc);
        //Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.WaitFor);
        var result = Player.ServiceSynchronizer.ExecuteInMainThread(task, true);

        if (task.TaskResult.ResultType != ActionResultType.OK)
        {
            if (task.Exception != null)
                AddFailedResult(exception: task.Exception);
            else
                AddFailedResult("Unable to execute task");
        }

        return result;
        //return Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.WaitFor);
    }

    protected AimpActionResult ExecuteInMainThread(Action testFunc)
    {
        var task = new AimpTask(testFunc);
        var result = Player.ServiceSynchronizer.ExecuteInMainThread(task, true);

        if (task.TaskResult.ResultType != ActionResultType.OK)
        {
            if (task.Exception != null)
                AddFailedResult(exception: task.Exception);
            else
                AddFailedResult("Unable to execute task");
        }


        return result;
        //return Player.ServiceThreadPool.Validate(task);
        //return Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.None);
    }

    protected AimpActionResult ExecuteInThread(Func<AimpActionResult> func)
    {
        var t = new AimpTask(func);
        var taskId = UIntPtr.Zero;
        t.Aborting += (sender, args) =>
        {
            if (taskId != UIntPtr.Zero) Player.ServiceThreadPool.Cancel(taskId, AimpServiceThreadPoolType.None);
        };

        var taskResult = Player.ServiceThreadPool.Execute(t);
        taskId = taskResult.Result;

        return taskResult;
        //return Player.ServiceThreadPool.Validate(t);
    }

    [Obsolete("Uses obsolete service")]
    public AimpActionResult ExecuteAndWait(Func<AimpActionResult> func)
    {
        var t = new AimpTask(func);
        var r = Player.ServiceThreadPool.Execute(t);
        var res = Player.ServiceThreadPool.WaitFor(r.Result);
        return res;
    }

    public AimpActionResult ExecuteAndWait2(Func<AimpActionResult> func)
    {
        var t = new AimpTask(func);
        var r = Player.ServiceThreads.ExecuteInThread(t);
        var res = Player.ServiceThreads.WaitFor(r.Result);
        return res;
    }

    internal void Validate(AimpIntegrationTest testClass)
    {
        foreach (var fieldValidator in Asserts) fieldValidator.Validate();
    }

    protected void AssertOKResult(AimpActionResult result, string message = null)
    {
        AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Wrong ActionResultType");
    }

    protected void AssertOKResult<TResult>(AimpActionResult<TResult> result)
    {
        AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Wrong ActionResultType");
        AimpAssert.NotNull(result.Result, "Result is empty");
    }

    private void ClearAimpBeforeTests()
    {
        TestContext.WriteLine("Clear existing playlist");
        var playlistPath = Player.Core.GetPath(AimpCorePathType.Playlists);
        foreach (var file in new DirectoryInfo(playlistPath).GetFiles()) file.Delete();
    }

    private static void AddFailedResult(string message = null, Exception exception = null)
    {
        var msg = message ?? exception?.Message;
        var result = TestExecutionContext.CurrentContext.CurrentResult;
        result.RecordAssertion(AssertionStatus.Failed, msg, exception?.StackTrace ?? Environment.StackTrace);
        result.RecordTestCompletion();
    }

    private class AimpTask : IAimpTask
    {
        private readonly Action _action;
        private readonly Func<AimpActionResult> _task;

        public AimpTask(Action action)
        {
            _action = action;
        }

        public AimpTask(Func<AimpActionResult> task)
        {
            _task = task;
        }

        public AimpActionResult TaskResult { get; private set; }
        public Exception Exception { get; private set; }

        public void Execute(IAimpTaskOwner owner)
        {
            TaskResult = new AimpActionResult(ActionResultType.Fail);

            if (_task != null)
                try
                {
                    var result = _task();
                    TaskResult = result;
                }
                catch (AssertionException e)
                {
                    Exception = e;
                }
                catch (Exception e)
                {
                    Exception = e;
                    Aborting?.Invoke(this, EventArgs.Empty);
                }

            if (_action != null)
                try
                {
                    _action();
                    TaskResult = new AimpActionResult(ActionResultType.OK);
                }
                catch (Exception e)
                {
                    Exception = e;
                    Aborting?.Invoke(this, EventArgs.Empty);
                }
        }

        public event EventHandler Aborting;
    }
}
