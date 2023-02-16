//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Drawing;
using AIMP.SDK;
using AIMP.SDK.AlbumArt;
using AIMP.SDK.AlbumArt.Extensions;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.AlbumArtManager.Extension;

public class CustomAlbumArtProvider : IAimpExtensionAlbumArtProvider3
{
    private readonly IAimpCore _core;

    public CustomAlbumArtProvider(IAimpCore core)
    {
        _core = core;
    }

    public AimpActionResult<IAimpImageContainer> Get(IAimpFileInfo file, IAimpAlbumArtRequest requestOption)
    {
        var container = _core.CreateObject<IAimpImageContainer>();
        return new AimpActionResult<IAimpImageContainer>((IAimpImageContainer)container.Result);
    }

    public AimpAlbumArtProviderCategory GetCategory()
    {
        return AimpAlbumArtProviderCategory.Tags;
    }
}

[TestFixture(Category = "ExtensionAlbumArtProvider")]
public class AimpExtensionAlbumArtProviderTests : AimpIntegrationTest
{
    [Test]
    public void Register_OK()
    {
        ExecuteInMainThread(() =>
        {
            var extension = new CustomAlbumArtProvider(Player.Core);
            var result = Player.Core.RegisterExtension(extension);
            AssertOKResult(result);
        });
    }
}