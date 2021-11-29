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

using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager.Extensions
{
    public class AimpExtensionFileFormat : IAimpExtensionFileFormat
    {
        public AimpActionResult<string> Description { get; } = new AimpActionResult<string>(ActionResultType.OK, "test");
        public AimpActionResult<string> ExtList { get; } = new AimpActionResult<string>(ActionResultType.OK, "test");

        public AimpActionResult<FileFormatsCategoryTypes> Flags { get; } = new AimpActionResult<FileFormatsCategoryTypes>(ActionResultType.OK, FileFormatsCategoryTypes.Audio | FileFormatsCategoryTypes.Playlists);
    }

    [TestFixture]
    public class AimpExtensionFileFormatUnitTests : AimpIntegrationTest
    {
        private AimpExtensionFileFormat _extension;

        [Test]
        [Order(1)]
        public void Register_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                _extension = new AimpExtensionFileFormat();
                var res = Player.Core.RegisterExtension(_extension);
                this.AreEqual(ActionResultType.OK, res.ResultType);
            });
        }
    }
}
