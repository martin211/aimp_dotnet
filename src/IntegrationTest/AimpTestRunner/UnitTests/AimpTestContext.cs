using System;
using AIMP.SDK.Player;

namespace Aimp.TestRunner.UnitTests
{
    public class AimpTestContext : MarshalByRefObject
    {
        private static AimpTestContext _instance;
        public static AimpTestContext Instance => _instance ?? (_instance = new AimpTestContext());

        public IAimpPlayer AimpPlayer { get; set; }
    }
}