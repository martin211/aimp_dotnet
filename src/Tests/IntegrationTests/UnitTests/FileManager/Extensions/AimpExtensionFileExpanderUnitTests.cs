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

using System;
using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.FileManager.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager.Extensions;

public class AimpExtensionFileExpander : IAimpExtensionFileExpander
{
    public AimpActionResult<IAimpObjectList<IAimpVirtualFile>> Expand(string fileName,
        IAimpProgressCallback progressCallback)
    {
        throw new NotImplementedException();
    }
}

[TestFixture]
public class AimpExtensionFileExpanderUnitTests : AimpIntegrationTest
{
    private AimpExtensionFileExpander _extension;

    [Test]
    [Order(1)]
    public void Register_ShouldBeOK()
    {
        ExecuteInMainThread(() =>
        {
            _extension = new AimpExtensionFileExpander();
            var res = Player.Core.RegisterExtension(_extension);
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
        });
    }

    [Test]
    [Ignore("Need investigation")]
    public void Expand_ShouldBeOK()
    {
        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            AssertOKResult(playlistResult);

            //var playlist = playlistResult.Result;
            //var itemResult = playlist.GetItem(0);
            //this.AreEqual(ActionResultType.OK, itemResult.ResultType);

            var virtualFileResult = Player.ServiceFileInfo.GetVirtualFile($"{TrackPath1}:02");
            AssertOKResult(virtualFileResult);
        });
    }
}
