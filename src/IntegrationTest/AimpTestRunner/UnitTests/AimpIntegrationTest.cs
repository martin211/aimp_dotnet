using System;
using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Threading;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests
{
    public abstract class AimpIntegrationTest
    {
        protected IAimpPlayer Player { get; }

        protected AimpIntegrationTest()
        {
            Player = AimpTestContext.Instance.AimpPlayer;
        }

        [OneTimeSetUp]
        public void RunBeforeAnyTests()
        {
            Assert.NotNull(Player);
        }

        protected ActionResultType ExecuteInMainThread(Func<ActionResultType> testFunc)
        {
            var task = new AimpTask(testFunc);
            return Player.ServiceSynchronizer.ExecuteInMainThread(task, true);
        }

        private class AimpTask : IAimpTask
        {
            private Func<ActionResultType> _task;

            public AimpTask(Func<ActionResultType> task)
            {
                _task = task;
            }

            public ActionResultType Execute(IAimpTaskOwner owner)
            {
                return _task();
            }
        }
    }
}