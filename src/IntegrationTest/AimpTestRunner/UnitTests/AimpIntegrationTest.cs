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
using System.Linq.Expressions;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Player;
using AIMP.SDK.Threading;
using NUnit.Engine;
using NUnit.Framework;
using NUnit.Framework.Constraints;

namespace Aimp.TestRunner.UnitTests
{
    public static class AssertExtension
    {
        public static EqualAssert AreEqual<TResult>(this AimpIntegrationTest testClass, object expected, Expression<Func<TResult>> current, string message = null)
        {
            var assert = new EqualAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), expected,
                message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static EqualAssert AreEqual(this AimpIntegrationTest testClass,
            object expected,
            object current,
            string fieldName = null,
            string message = null)
        {
            var assert = new EqualAssert(fieldName, current, expected, message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static EqualAssert AreEqual(this AimpIntegrationTest testClass,
            object expected,
            object current,
            string message)
        {
            return testClass.AreEqual(expected, current, string.Empty, message);
        }

        public static NotNullAssert NotNull<TResult>(this AimpIntegrationTest testClass, Expression<Func<TResult>> current, string message = null)
        {
            var assert = new NotNullAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static NotNullAssert NotNull(this AimpIntegrationTest testClass, object current, string fieldName = null,
            string message = null)
        {
            var assert = new NotNullAssert(fieldName, current, message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static NotEqualAssert AreNotEqual(this AimpIntegrationTest testClass, object expected,
            object current,
            string fieldName = null,
            string message = null)
        {
            var assert = new NotEqualAssert(fieldName, current, expected, message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static NotEqualAssert AreNotEqual<TResult>(this AimpIntegrationTest testClass, object expected,
            Expression<Func<TResult>> current, string message = null)
        {
            var assert = new NotEqualAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), expected,
                message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static void IsTrue(this AimpIntegrationTest testClass, bool value)
        {
            testClass.Asserts.Add(new TrueAssert(null, value, null));
        }

        public static void IsFalse(this AimpIntegrationTest testClass, bool value)
        {
            testClass.Asserts.Add(new FalseAssert(null, value, null));
        }

        public static TException Throw<TException>(this AimpIntegrationTest testClass, TestDelegate action)
            where TException : Exception
        {
            var assert = new ThrowAssert<TException>(action);
            testClass.Asserts.Add(assert);
            return (TException) assert.CatchedException;
        }

        public static void Null<TResult>(this AimpIntegrationTest testClass, Expression<Func<TResult>> current)
        {
            testClass.Asserts.Add(new NullAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), null));
        }

        private static string GetExpressionMemberName<TResult>(this Expression<Func<TResult>> expression)
        {
            string memberName = string.Empty;

            if (expression is MemberExpression memberExpression)
            {
                memberName = memberExpression.Member.Name;
            }
            else if (expression is LambdaExpression lambdaExpression)
            {
                if (lambdaExpression.Body is MemberExpression me)
                {
                    memberName = me.Member.Name;
                }
                else
                {
                    throw new ArgumentException(
                        $"Expression '{expression}' refers to a method, not a property.");
                }
                memberName = lambdaExpression.Name;
            }

            return memberName;
        }

        private static object GetExpressionValue<TResult>(this Expression<Func<TResult>> expression)
        {
            var valueGetter = expression.Compile();
            try
            {
                return valueGetter();
            }
            catch (Exception ex)
            {
                TestContext.Error.WriteLine(ex.ToString());
                return default;
            }
        }
    }

    public abstract class AimpAssert
    {
        public abstract void Validate();
    }

    public abstract class MemberAssert : MemberAssert<object>
    {
        protected MemberAssert(string name, object value, string message)
            : base(name, value, message)
        {
            FieldName = name;
            Value = value;
            Message = message;
        }

        public abstract override void Validate();

    }

    public abstract class MemberAssert<TValue> : AimpAssert
    {
        public string FieldName { get; set; }

        public TValue Value { get; set; }

        public string Message { get; set; }

        protected MemberAssert(string name, TValue value, string message)
        {
            FieldName = name ?? "Field";
            Value = value;
            Message = message;
        }

        public abstract override void Validate();
    }

    public class NotNullAssert : MemberAssert
    {
        public NotNullAssert(string name, object value, string message) : base(name, value, message)
        {
        }

        public override void Validate()
        {
            Assert.NotNull(Value, FieldName);
        }
    }

    public class NullAssert : MemberAssert
    {
        public NullAssert(string name, object value, string message) : base(name, value, message)
        {
        }

        public override void Validate()
        {
            Assert.Null(Value, FieldName);
        }
    }

    public class EqualAssert : MemberAssert
    {
        public object Expected { get; }

        public EqualAssert(string name, object value, object expected, string message)
            : base(name, value, message)
        {
            Expected = expected;
        }

        public override void Validate()
        {
            Assert.AreEqual(Expected, Value, Message ?? $"'{FieldName}' do not equal '{Value}'");
        }
    }

    public class NotEqualAssert : MemberAssert
    {
        public object Expected { get; }

        public NotEqualAssert(string name, object value, object expected, string message)
            : base(name, value, message)
        {
            Expected = expected;
        }

        public override void Validate()
        {
            Assert.AreNotEqual(Expected, Value, Message ?? $"{FieldName} do not equal {Value}");
        }
    }

    public class ThrowAssert<TException> : AimpAssert where TException : Exception
    {
        public Exception CatchedException;
        private TestDelegate _action;

        public ThrowAssert(TestDelegate action)
        {
            try
            {
                action();
            }
            catch (Exception e)
            {
                CatchedException = e;
            }
        }

        public override void Validate()
        {
            var expectedType = typeof(TException);
            Assert.That(CatchedException, new ExceptionTypeConstraint(expectedType));
        }
    }

    public class TrueAssert : MemberAssert<bool>
    {
        public TrueAssert(string name, bool value, string message)
            : base(name, value, message)
        {
        }

        public override void Validate()
        {
            Assert.True(Value, $"Expected 'true' but was '{Value}'");
        }
    }

    public class FalseAssert : MemberAssert<bool>
    {
        public FalseAssert(string name, bool value, string message)
            : base(name, value, message)
        {
        }

        public override void Validate()
        {
            Assert.False(Value, $"Expected 'False' but was '{Value}'");
        }
    }

    public abstract class AimpIntegrationTest
    {
        internal string RootPath { get; }

        internal string PlaylistPath { get; }

        internal string TrackPath1 { get; }

        internal string TrackPath2 { get; }

        internal string TrackPath3 { get; }

        internal string TrackPath4 { get; }

        internal string TrackUrl1 { get; }

        internal IList<AimpAssert> Asserts { get; set; }

        protected IAimpPlayer Player { get; }

        protected AimpIntegrationTest()
        {
            Player = AimpTestContext.Instance.AimpPlayer;

            if (Player == null)
            {
                throw new NUnitEngineException("Unable to run unit tests. Check that file 'nunit.engine.addins' exists in plugin folder.");
            }

            RootPath = Path.Combine(Player.Core.GetPath(AimpCorePathType.AIMP_CORE_PATH_PLUGINS), "AimpTestRunner");
            PlaylistPath = Path.Combine(RootPath, "resources", "IntegrationTests.aimppl4");
            TrackPath1 = Path.Combine(RootPath, "resources", "01_atmosphere.mp3");
            TrackPath2 = Path.Combine(RootPath, "resources", "02_loop-mix.mp3");
            TrackPath3 = Path.Combine(RootPath, "resources", "03_atmosphere.mp3");
            TrackPath4 = Path.Combine(RootPath, "resources", "04_loop-mix.mp3");
            TrackUrl1 = "https://freesound.org/data/previews/514/514101_4397472-lq.mp3";
        }

        [OneTimeSetUp]
        public virtual void RunBeforeAnyTests()
        {
            Assert.NotNull(Player);
            Asserts = new List<AimpAssert>();
        }

        [SetUp]
        public virtual void SetUp()
        {
            Asserts.Clear();
        }

        [TearDown]
        public virtual void TearDown()
        {
            if (Asserts.Count > 0)
            {
                Validate();
            }
        }

        protected object ExecuteInMainThread2(Func<object> func)
        {
            var task = new AimpTask2(func);
            Player.ServiceSynchronizer.ExecuteInMainThread(task, true);
            return task.Result;
        }

        protected ActionResultType ExecuteInMainThread(Func<ActionResultType> testFunc)
        {
            var task = new AimpTask(testFunc);
            return Player.ServiceSynchronizer.ExecuteInMainThread(task, true);
        }

        protected ActionResultType ExecuteInThread(Func<ActionResultType> func)
        {
            var t =  new AimpTask(func);
            return Player.ServiceThreadPool.Execute(t, out _);
        }

        public ActionResultType ExecuteAndWait(Func<ActionResultType> func)
        {
            var t = new AimpTask(func);
            var r = Player.ServiceThreadPool.Execute(t, out var id);
            r = Player.ServiceThreadPool.WaitFor(id);
            return r;
        }

        internal void Validate()
        {
            foreach (var fieldValidator in Asserts)
            {
                fieldValidator.Validate();
            }
        }

        protected AimpAssert AssertOKResult(ActionResultType current, string message = null)
        {
            return this.AreEqual(ActionResultType.OK, current, null, message);
        }

        private class AimpTask : IAimpTask
        {
            private readonly Func<ActionResultType> _task;

            public AimpTask(Func<ActionResultType> task)
            {
                _task = task;
            }

            public ActionResultType Execute(IAimpTaskOwner owner)
            {
                return _task();
            }
        }

        private class AimpTask2 : IAimpTask
        {
            private Func<object> _task;

            public object Result { get; set; }

            public AimpTask2(Func<object> task)
            {
                _task = task;
            }

            public ActionResultType Execute(IAimpTaskOwner owner)
            {
                Result = _task();
                return ActionResultType.OK;
            }
        }
    }
}