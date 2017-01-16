using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            var drive = 'C';

            var r = drive < 'Z';
            if (r)
            {
                drive = Convert.ToChar(Convert.ToByte(drive) + 1);
                Console.WriteLine(drive);
            }
        }
    }
}
