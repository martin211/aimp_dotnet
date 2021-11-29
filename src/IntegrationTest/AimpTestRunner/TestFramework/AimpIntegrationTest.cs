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
using System.Collections.Generic;
using System.IO;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Player;
using AIMP.SDK.Threading;
using Aimp.TestRunner.TestFramework.Assert;
using Aimp.TestRunner.UnitTests;
using NUnit.Engine;
using NUnit.Framework;
using NUnit.Framework.Interfaces;
using NUnit.Framework.Internal;

namespace Aimp.TestRunner.TestFramework
{
    public abstract class AimpIntegrationTest
    {
        public bool IsValid { get; set; } = true;

        internal string RootPath { get; }

        internal string TmpPath { get; }

        internal string PlaylistPath { get; }

        internal string TrackPath1 { get; }

        internal string TrackPath2 { get; }

        internal string TrackPath3 { get; }

        internal string TrackPath4 { get; }

        internal string TrackUrl1 { get; }

        internal IList<IMemberAssert> Asserts { get; set; }

        protected IAimpPlayer Player { get; }

        protected AimpIntegrationTest()
        {
            Player = AimpTestContext.Instance.AimpPlayer;

            if (Player == null)
            {
                throw new NUnitEngineException("Unable to run unit tests. Check that file 'nunit.engine.addins' exists in plugin folder.");
            }

            RootPath = Path.Combine(Player.Core.GetPath(AimpCorePathType.Plugins), "AimpTestRunner");
            PlaylistPath = Path.Combine(RootPath, "resources", "IntegrationTests.aimppl4");
            TrackPath1 = Path.Combine(RootPath, "resources", "01_atmosphere.mp3");
            TrackPath2 = Path.Combine(RootPath, "resources", "02_loop-mix.mp3");
            TrackPath3 = Path.Combine(RootPath, "resources", "03_atmosphere.mp3");
            TrackPath4 = Path.Combine(RootPath, "resources", "04_loop-mix.mp3");
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
        }

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
            if (Asserts != null && Asserts.Count > 0)
            {
                Validate(this);
            }
        }

        protected AimpActionResult ExecuteInMainThreadAndWait(Func<AimpActionResult> testFunc)
        {
            var task = new AimpTask(testFunc);
            var result = Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.WaitFor);
            return new AimpActionResult(result.ResultType);
        }

        protected AimpActionResult ExecuteInMainThread(Func<AimpActionResult> testFunc)
        {
            var task = new AimpTask(testFunc);
            return Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.None);
        }
        
        //protected AimpActionResult<T> ExecuteInMainThread<T>(Func<AimpActionResult<T>> testFunc)
        //{
        //    var task = new AimpTask(testFunc);
        //    return Player.ServiceThreads
        //        .ExecuteInMainThread(task, AimpServiceThreadPoolType.None);
        //}

        protected AimpActionResult ExecuteInMainThread(Action testFunc)
        {
            var task = new AimpTask(testFunc);
            return Player.ServiceThreads.ExecuteInMainThread(task, AimpServiceThreadPoolType.None);
        }

        protected AimpActionResult ExecuteInThread(Func<AimpActionResult> func)
        {
            var t =  new AimpTask(func);
            return Player.ServiceThreadPool.Execute(t);
        }

        public AimpActionResult ExecuteAndWait(Func<AimpActionResult> func)
        {
            var t = new AimpTask(func);
            var r = Player.ServiceThreadPool.Execute(t);
            var res = Player.ServiceThreadPool.WaitFor(r.Result);
            return res;
        }

        internal void Validate(AimpIntegrationTest testClass)
        {
            foreach (var fieldValidator in Asserts)
            {
                fieldValidator.Validate(testClass);
            }
        }

        protected IMemberAssert AssertOKResult(ActionResultType current, string message = null)
        {
            return this.AreEqual(ActionResultType.OK, current, null, message);
        }

        private void ClearAimpBeforeTests()
        {
            TestContext.WriteLine("Clear existing playlist");
            var playlistPath = Player.Core.GetPath(AimpCorePathType.Playlists);
            foreach (var file in new DirectoryInfo(playlistPath).GetFiles())
            {
                file.Delete();
            }
        }

        private class AimpTask : IAimpTask
        {
            private readonly Func<AimpActionResult> _task;
            private readonly Action _action;

            public AimpTask(Action action)
            {
                _action = action;
            }

            public AimpTask(Func<AimpActionResult> task)
            {
                _task = task;
            }

            public AimpActionResult Execute(IAimpTaskOwner owner)
            {
                try
                {
                    if (_task != null)
                        return _task();

                    if (_action != null)
                    {
                        _action();
                        return new AimpActionResult(ActionResultType.OK);
                    }
                }
                catch (Exception e)
                {
                    TestContext.WriteLine(e.ToString());
                    TestContext.Error.WriteLine(e.ToString());
                    TestContext.Out.WriteLine(e.ToString());
                }

                return new AimpActionResult(ActionResultType.Fail);
            }
        }

        //private class AimpTask<T> : IAimpTask
        //{
        //    private readonly Func<AimpActionResult<T>> _task;

        //    public AimpTask(Func<AimpActionResult<T>> task)
        //    {
        //        _task = task;
        //    }

        //    public AimpActionResult Execute(IAimpTaskOwner owner)
        //    {
        //        return
        //    }
        //}

        private class AimpTask2 : IAimpTask
        {
            private Func<object> _task;

            public object Result { get; set; }

            public AimpTask2(Func<object> task)
            {
                _task = task;
            }

            public AimpActionResult Execute(IAimpTaskOwner owner)
            {
                try
                {
                    _task();
                    return new AimpActionResult(ActionResultType.OK);
                }
                catch (Exception e)
                {
                    var result = TestExecutionContext.CurrentContext.CurrentResult;
                    result.RecordAssertion(AssertionStatus.Failed, "", Environment.StackTrace);
                    result.RecordTestCompletion();

                    //TestContext.WriteLine(e.ToString());
                    //TestContext.Error.WriteLine(e.ToString());
                    //TestContext.Out.WriteLine(e.ToString());
                }

                return new AimpActionResult(ActionResultType.Fail);
            }
        }
    }
}