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

using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager.Extensions;

public class AimpExtensionFileFormat : IAimpExtensionFileFormat
{
    public AimpActionResult<string> Description { get; } = new(ActionResultType.OK, "test");
    public AimpActionResult<string> ExtList { get; } = new(ActionResultType.OK, "test");

    public AimpActionResult<FileFormatsCategoryTypes> Flags { get; } = new(ActionResultType.OK,
        FileFormatsCategoryTypes.Audio | FileFormatsCategoryTypes.Playlists);
}

[TestFixture(Category = "ExtensionFileFormat")]
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
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
        });
    }
}
