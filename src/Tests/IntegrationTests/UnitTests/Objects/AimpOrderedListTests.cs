//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Objects;

[TestFixture(Category = "OrderedList")]
public class AimpOrderedListTests : AimpIntegrationTest
{
    [Test]
    [Order(1)]
    public void Create_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpOrderedObjectList>(AimpObjectType.AimpOrderedList);
        AssertOKResult(res);
        res.Result.Dispose();
    }

    [Test(Description = "Should create a new item for list that can be added to collection.")]
    public void CreateItem_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.CreateAimpObject<IAimpOrderedObjectList>(AimpObjectType.AimpOrderedList);
            AssertOKResult(res);

            var item = res.Result.Create("Item1", SortDirectionType.Ascending);
            AimpAssert.NotNull(item);
            AimpAssert.NotNull(item.Name);
            AimpAssert.NotNull(item.Value);
            AimpAssert.AreEqual(SortDirectionType.Ascending, item.Value);

            AimpAssert.AreEqual("Item1", item.Name.GetData());

            var edited = "edited_item";
            var editResponse = item.Name.SetData(edited, edited.Length);
            AssertOKResult(editResponse);
            AimpAssert.AreEqual(edited, item.Name.GetData());

            item.Value = SortDirectionType.Descending;
            AimpAssert.AreEqual(SortDirectionType.Descending, item.Value);
        });
    }

    [Test(Description = "Should return count of items")]
    public void Count_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.CreateAimpObject<IAimpOrderedObjectList>(AimpObjectType.AimpOrderedList);
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

            AimpAssert.AreEqual(0, res.Result.Count);

            var item = res.Result.Create("Item1", SortDirectionType.Undefined);

            res.Result.Add(item);

            AimpAssert.AreEqual(1, res.Result.Count);
        });
    }

    [Test]
    public void Clear_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.CreateAimpObject<IAimpOrderedObjectList>(AimpObjectType.AimpOrderedList);
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

            var collection = res.Result;

            AimpAssert.NotNull(collection);

            var item = collection.Create("item1", SortDirectionType.Undefined);
            collection.Add(item);

            AimpAssert.AreEqual(1, collection.Count);

            collection.Clear();
            AimpAssert.AreEqual(0, collection.Count);
        });
    }

    [Test]
    public void Delete_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.CreateAimpObject<IAimpOrderedObjectList>(AimpObjectType.AimpOrderedList);
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

            var collection = res.Result;

            AimpAssert.NotNull(collection);

            var item = collection.Create("item1", SortDirectionType.Undefined);
            collection.Add(item);

            var item2 = collection.Create("item1", SortDirectionType.Undefined);
            collection.Add(item2);

            AimpAssert.AreEqual(2, collection.Count);

            var deleteResult = collection.Delete(0);
            AimpAssert.AreEqual(ActionResultType.OK, deleteResult.ResultType);
            AimpAssert.AreEqual(1, collection.Count);
        });
    }
}