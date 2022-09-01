//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.TagEditor;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.TagEditor;

[TestFixture(Category = "ServiceFileTagEditor")]
public class AimpServiceFileTagEditorTests : AimpIntegrationTest
{
    [Test]
    public void EditFile_ShouldReturnTagEditorForFile()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileTagEditor.EditFile(TrackPath1);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Unable to get tag editor for file.");
            AimpAssert.NotNull(result.Result);
            result.Result.Dispose();
        });
    }


    [TestCase(TagType.ID3v1)]
    [TestCase(TagType.ID3v2)]
    public void EditTag_FilePath_ShouldBeOK(TagType tag)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileTagEditor.EditTag(TrackPath1, tag);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Unable to edit tag for file.");
            AimpAssert.NotNull(result.Result);
            result.Result.Dispose();
        });
    }

    [TestCase(TagType.ApeV2)]
    [TestCase(TagType.M4A)]
    [TestCase(TagType.Vorbis)]
    [TestCase(TagType.WMA)]
    public void EditTag_FilePath_ShouldBeFailForWrongFileFormat(TagType tag)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileTagEditor.EditTag(TrackPath1, tag);
            AimpAssert.AreEqual(ActionResultType.Fail, result.ResultType, "Unable to edit tag for file.");
            AimpAssert.Null(() => result.Result);
        });
    }

    [Test]
    public void FindAlbums_()
    {
        ExecuteInMainThread(() =>
        {
            
        });
    }
}
