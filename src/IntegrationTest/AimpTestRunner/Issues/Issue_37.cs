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
using System.IO;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using Aimp.TestRunner.UnitTests;
using NUnit.Framework;

namespace Aimp.TestRunner.Issues
{
    [TestFixture(
        Description = "Issue 37. The TagEditor is locks file until Aimp is closed",
        Category = "Issues")]
    public class Issue_37 : AimpIntegrationTest
    {
        [Test]
        public void EditFile()
        {
            ExecuteInMainThread(() =>
            {
                if (IsLock(TrackPath1))
                {
                    TestContext.Error.WriteLine("File is locked");
                    return;
                }

                var res = Player.ServiceFileTagEditor.EditFile(TrackPath1);
                this.AreEqual(ActionResultType.OK, res.ResultType);
                var editor = res.Result;

                var fileInfo = Player.Core.CreateAimpObject<IAimpFileInfo>().Result;
                fileInfo.Title = "Test";
                editor.SetToAll(fileInfo);
                var saveResult = editor.Save();
                this.AreEqual(ActionResultType.OK, saveResult.ResultType);
                fileInfo.Dispose();
                editor.Dispose();

                if (IsLock(TrackPath1))
                {
                    TestContext.Error.WriteLine("File is locked");
                }
            });
        }

        private bool IsLock(string fileName)
        {
            try
            {
                using var stream = File.Open(TrackPath1, FileMode.Open, FileAccess.Read, FileShare.None);
                stream.Close();
                return false;
            }
            catch (Exception e)
            {
                return true;
            }
        }
    }
}
