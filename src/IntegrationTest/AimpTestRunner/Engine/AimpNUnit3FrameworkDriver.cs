using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.Serialization;
using NUnit.Engine;
using NUnit.Engine.Extensibility;
using NUnit.Engine.Internal;
using NUnit.Framework.Api;

namespace Aimp.TestRunner.Engine
{
    public class AimpNUnit3FrameworkDriver : IFrameworkDriver
    {
        private const string LoadMessage = "Method called without calling Load first";

        static ILogger log = InternalTrace.GetLogger("AimpNUnit3FrameworkDriver");

        private string _testAssemblyPath;
        FrameworkController _frameworkController;

        public AimpNUnit3FrameworkDriver(AppDomain testDomain, AssemblyName reference)
        {
        }

        public string ID { get; set; }
        public string Load(string testAssemblyPath, IDictionary<string, object> settings)
        {
            var idPrefix = string.IsNullOrEmpty(ID) ? "" : ID + "-";
            _testAssemblyPath = testAssemblyPath;
            try
            {
                _frameworkController = new FrameworkController(testAssemblyPath, idPrefix, new Dictionary<string, string>());
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
