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
using System.Reflection;
using System.Runtime.Remoting;
using System.Runtime.Serialization;
using Aimp.TestRunner.TestFramework;
using NUnit.Engine;
using NUnit.Engine.Extensibility;
using NUnit.Engine.Internal;
using NUnit.Framework.Api;

namespace Aimp.TestRunner.Engine
{
    public class CB : CallbackHandler
    {
        public override object InitializeLifetimeService()
        {
            return base.InitializeLifetimeService();
        }
    }

    public class AimpNUnit3FrameworkDriver : IFrameworkDriver
    {
        private const string LoadMessage = "Method called without calling Load first";

        private static readonly string CONTROLLER_TYPE = "NUnit.Framework.Api.FrameworkController";
        private static readonly string LOAD_ACTION = CONTROLLER_TYPE + "+LoadTestsAction";
        private static readonly string EXPLORE_ACTION = CONTROLLER_TYPE + "+ExploreTestsAction";
        private static readonly string COUNT_ACTION = CONTROLLER_TYPE + "+CountTestsAction";
        private static readonly string RUN_ACTION = CONTROLLER_TYPE + "+RunTestsAction";
        private static readonly string STOP_RUN_ACTION = CONTROLLER_TYPE + "+StopRunAction";

        static ILogger log = InternalTrace.GetLogger("AimpNUnit3FrameworkDriver");

        private string _testAssemblyPath;
        //AimpTestController _frameworkController;
        private FrameworkController _frameworkController;
        private AppDomain _testDomain;
        private AssemblyName _reference;

        public AimpNUnit3FrameworkDriver(AppDomain testDomain, AssemblyName reference)
        {
            _testDomain = testDomain;
            _reference = reference;
        }

        public string ID { get; set; }
        public string Load(string testAssemblyPath, IDictionary<string, object> settings)
        {
            _testDomain = AppDomain.CreateDomain("testDomain");

            var idPrefix = string.IsNullOrEmpty(ID) ? "" : ID + "-";
            _testAssemblyPath = testAssemblyPath;
            try
            {
                _frameworkController = new FrameworkController(testAssemblyPath, idPrefix, new Dictionary<string, string>());
                //_frameworkController = new AimpTestController(testAssemblyPath, idPrefix, new Dictionary<string, string>());
            }
            catch (SerializationException ex)
            {
                throw new NUnitEngineException("The NUnit 3 driver cannot support this test assembly. Use a platform specific runner.", ex);
            }

            CallbackHandler handler = new CallbackHandler();
            var fileName = Path.GetFileName(_testAssemblyPath);
            log.Info("Loading {0} - see separate log file", fileName);

            // ReSharper disable once ObjectCreationAsStatement
            new FrameworkController.LoadTestsAction(_frameworkController, handler);
            //new AimpTestController.AimpLoadTestsAction(_frameworkController, handler);
            log.Info("Loaded {0}", fileName);

            return handler.Result;
        }

        public int CountTestCases(string filter)
        {
            CheckLoadWasCalled();

            CallbackHandler handler = new CallbackHandler();
            // ReSharper disable once ObjectCreationAsStatement
            new FrameworkController.CountTestsAction(_frameworkController, filter, handler);

            return int.Parse(handler.Result);
        }

        public string Run(ITestEventListener listener, string filter)
        {
            CheckLoadWasCalled();
            var handler = new RunTestsCallbackHandler(listener);

            log.Info("Running {0} - see separate log file", Path.GetFileName(_testAssemblyPath));
            // ReSharper disable once ObjectCreationAsStatement
            new FrameworkController.RunTestsAction(_frameworkController, filter, handler);
            return handler.Result;
        }

        public string Explore(string filter)
        {
            CheckLoadWasCalled();

            CallbackHandler handler = new CallbackHandler();

            log.Info("Exploring {0} - see separate log file", Path.GetFileName(_testAssemblyPath));
            // ReSharper disable once ObjectCreationAsStatement
            new FrameworkController.ExploreTestsAction(_frameworkController, filter, handler);

            return handler.Result;
        }

        public void StopRun(bool force)
        {
            // ReSharper disable once ObjectCreationAsStatement
            new FrameworkController.StopRunAction(_frameworkController, force, new CallbackHandler());
        }

        private void CheckLoadWasCalled()
        {
            if (_frameworkController == null)
                throw new InvalidOperationException(LoadMessage);
        }
    }
}
