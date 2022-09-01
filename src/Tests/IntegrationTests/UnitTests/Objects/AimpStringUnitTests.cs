using AIMP.SDK;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Objects;

[TestFixture(Category = "String")]
public class AimpStringUnitTests : AimpIntegrationTest
{
    [Test]
    [Ignore("GetChar not working")]
    public void GetChar_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");
            var getCharResult = aimpString.GetChar(1);
            AssertOKResult(getCharResult);
            AimpAssert.AreEqual("2", getCharResult.Result);
        });
    }

    [Test]
    public void GetData_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");

            var data = aimpString.GetData();
            AimpAssert.AreEqual("12345", data);
        });
    }

    [Test]
    public void GetLength_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");

            var length = aimpString.GetLength();
            AimpAssert.AreEqual(5, length);
        });
    }

    [Test]
    public void GetHashCode_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");

            var hashCode = aimpString.GetHashCode();
            AimpAssert.IsTrue(hashCode > 0);
        });
    }

    [Test]
    public void SetChar_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");

            var setCharResult = aimpString.SetChar(1, '1');
            AssertOKResult(setCharResult);

            var data = aimpString.GetData();
            AimpAssert.AreEqual("11345", data);
        });
    }

    [Test]
    public void Add_String_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var originString = CreateAndFill("12345");
            using var addString = CreateAndFill("67890");

            var addResult = originString.Add(addString);
            AssertOKResult(addResult);

            var data = originString.GetData();
            AimpAssert.AreEqual("1234567890", data);
        });
    }

    [Test]
    public void Add_Char_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");
            var addResult = aimpString.Add("67890", 5);
            AssertOKResult(addResult);

            var data = aimpString.GetData();
            AimpAssert.AreEqual("1234567890", data);
        });
    }

    [TestCase(AimpStringCase.AllWordsWithCapitalLetter, "abcdef abcdef", "Abcdef Abcdef")]
    [TestCase(AimpStringCase.FirstWordWithCapitalLetter, "abcdef abcdef", "Abcdef abcdef")]
    [TestCase(AimpStringCase.Lower, "ABCDEF ABCDEF", "abcdef abcdef")]
    [TestCase(AimpStringCase.Upper, "abcdef abcdef", "ABCDEF ABCDEF")]
    public void ChangeCase_OK(AimpStringCase stringCase, string source, string expected)
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill(source);
            var result = aimpString.ChangeCase(stringCase);
            AssertOKResult(result);

            var data = aimpString.GetData();
            AimpAssert.AreEqual(expected, data);
        });
    }

    [Test]
    public void Clone_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");
            var cloneResult = aimpString.Clone();
            AssertOKResult(cloneResult);

            var data = cloneResult.Result.GetData();
            AimpAssert.AreEqual("12345", data);

            cloneResult.Result.Dispose();
        });
    }

    [TestCase("abcdef", "abcdef", false, 0)]
    [TestCase("abcdef", "abcdef", true, 0)]
    [TestCase("abcdef", "ABCDEF", false, -1)]
    [TestCase("abcdef", "ABCDEF", true, 0)]
    [TestCase("abcdef", "12345", false, 1)]
    [TestCase("abcdef", "12345", true, 1)]
    public void Compare_String_OK(string source, string compare, bool ignoreCase, int expected)
    {
        ExecuteInMainThread(() =>
        {
            using var sourceString = CreateAndFill(source);
            using var compareString = CreateAndFill(compare);

            var compareResult = sourceString.Compare(compareString, ignoreCase);
            AssertOKResult(compareResult);
            AimpAssert.AreEqual(expected, compareResult.Result);
        });
    }

    [TestCase("abcdef", "abcdef", false, 0)]
    [TestCase("abcdef", "abcdef", true, 0)]
    [TestCase("abcdef", "ABCDEF", false, -1)]
    [TestCase("abcdef", "ABCDEF", true, 0)]
    [TestCase("abcdef", "12345", false, 1)]
    [TestCase("abcdef", "12345", true, 1)]
    public void Compare_Char_OK(string source, string compare, bool ignoreCase, int expected)
    {
        ExecuteInMainThread(() =>
        {
            using var sourceString = CreateAndFill(source);

            var compareResult = sourceString.Compare(compare, ignoreCase);
            AssertOKResult(compareResult);
            AimpAssert.AreEqual(expected, compareResult.Result);
        });
    }

    [Test]
    public void Delete_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("12345");
            var deleteResult = aimpString.Delete(0, 1);
            AssertOKResult(deleteResult);

            var data = aimpString.GetData();
            AimpAssert.AreEqual("2345", data);
        });
    }

    [TestCase("abcdef", "q", AimpStringFindFlags.IgnoreCase, -1)]
    [TestCase("abcdef", "b", AimpStringFindFlags.IgnoreCase, 1)]
    [TestCase("abcdef", "b", AimpStringFindFlags.WholeWord, -1)]
    [TestCase("abcdef qwerty", "abcdef", AimpStringFindFlags.WholeWord, 0)]
    public void Find_String_OK(string source, string find, AimpStringFindFlags flags, int expected)
    {
        ExecuteInMainThread(() =>
        {
            var aimpString = CreateAndFill(source);
            var findString = CreateAndFill(find);
            var findResult = aimpString.Find(findString, flags, 0);
            AssertOKResult(findResult);
            AimpAssert.AreEqual(expected, findResult.Result);
        });
    }
    
    [TestCase("abcdef", "q", AimpStringFindFlags.IgnoreCase, -1)]
    [TestCase("abcdef", "b", AimpStringFindFlags.IgnoreCase, 1)]
    [TestCase("abcdef", "b", AimpStringFindFlags.WholeWord, -1)]
    [TestCase("abcdef qwerty", "abcdef", AimpStringFindFlags.WholeWord, 0)]
    public void Find_Char_OK(string source, string find, AimpStringFindFlags flags, int expected)
    {
        ExecuteInMainThread(() =>
        {
            var aimpString = CreateAndFill(source);
            var findResult = aimpString.Find(find, flags, 0);
            AssertOKResult(findResult);
            AimpAssert.AreEqual(expected, findResult.Result);
        });
    }

    [Test]
    public void Insert_String_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("source");
            using var insertString = CreateAndFill("insert");

            var insertResult = aimpString.Insert(0, insertString);
            AssertOKResult(insertResult);

            var data = aimpString.GetData();
            AimpAssert.AreEqual("insertsource", data);
        });
    }

    [Test]
    public void Insert_Chars_OK()
    {
        ExecuteInMainThread(() =>
        {
            using var aimpString = CreateAndFill("source");

            var insertResult = aimpString.Insert(0, "insert");
            AssertOKResult(insertResult);

            var data = aimpString.GetData();
            AimpAssert.AreEqual("insertsource", data);
        });
    }

    [TestCase(AimpStringFindFlags.IgnoreCase, "sourcestring", "string", "replaced", "sourcereplaced")]
    [TestCase(AimpStringFindFlags.WholeWord, "source string", "string", "replaced", "source replaced")]
    public void Replace_String_OK(AimpStringFindFlags flags, string source, string search, string newString, string expected)
    {
        ExecuteInMainThread(() =>
        {
            using var sourceString = CreateAndFill(source);
            using var searchString = CreateAndFill(search);
            using var replaceString = CreateAndFill(newString);

            var sourceResult = sourceString.Replace(searchString, replaceString, flags);
            AssertOKResult(sourceResult);

            var data = sourceString.GetData();
            AimpAssert.AreEqual(expected, data);
        });
    }

    [TestCase(AimpStringFindFlags.IgnoreCase, "sourcestring", "string", "replaced", "sourcereplaced")]
    [TestCase(AimpStringFindFlags.WholeWord, "source string", "string", "replaced", "source replaced")]
    public void Replace_Chars_OK(AimpStringFindFlags flags, string source, string search, string newString, string expected)
    {
        ExecuteInMainThread(() =>
        {
            using var sourceString = CreateAndFill(source);

            var sourceResult = sourceString.Replace(search, newString, flags);
            AssertOKResult(sourceResult);

            var data = sourceString.GetData();

            AimpAssert.AreEqual(expected, data);
        });
    }

    [Test]
    public void SubString_OK()
    {
        ExecuteInMainThread(() =>
        {
            var aimpString = CreateAndFill("123sub456");

            var subStringResult = aimpString.SubString(3, 3);
            AssertOKResult(subStringResult);

            AimpAssert.AreEqual("sub", subStringResult.Result.GetData());
        });
    }

    [Test]
    public void GetAimpHashCode_OK()
    {
        ExecuteInMainThread(() =>
        {
            var aimpString = CreateAndFill("string");
            var hash = aimpString.GetAimpHashCode();
            AimpAssert.IsTrue(hash != 0);
        });
    }

    [Test]
    public void Recalculate_OK()
    {
        ExecuteInMainThread(() =>
        {
            var aimpString = CreateAndFill("string");
            var hash = aimpString.GetAimpHashCode();
            AimpAssert.IsTrue(hash != 0);

            aimpString.Recalculate();
            hash = aimpString.GetAimpHashCode();
            AimpAssert.IsTrue(hash != 0);
        });
    }

    private IAimpString CreateAndFill(string data)
    {
        var stringResult = Player.Core.CreateAimpObject<IAimpString>(AimpObjectType.AimpString);
        AssertOKResult(stringResult);

        var aimpString = stringResult.Result;

        var setDataResult = aimpString.SetData(data, data.Length);
        AssertOKResult(setDataResult);

        return aimpString;
    }
}