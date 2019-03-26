// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System;
using System.Runtime.InteropServices;

namespace AIMP.SDK.Objects
{
    public enum AIMPStringCase
    {
        Default = 0,
        Lower = 1,
        Upper = 2,
        AllWordsWithCapicalLetter = 3,
        FirstWordWithCapicalLetter = 4,
    }

    [Flags]
    public enum AIMPStringFindFlags
    {
        IgnoreCase = 1,
        WholeWord = 2,
    }

    public class MyOwnMarshalPtrToStringUni : ICustomMarshaler
    {
        public MyOwnMarshalPtrToStringUni(string value)
        {
        }

        public object MarshalNativeToManaged(IntPtr pNativeData)
        {
            throw new NotImplementedException();
        }

        public IntPtr MarshalManagedToNative(object ManagedObj)
        {
            throw new NotImplementedException();
        }

        public void CleanUpNativeData(IntPtr pNativeData)
        {
            throw new NotImplementedException();
        }

        public void CleanUpManagedData(object ManagedObj)
        {
            throw new NotImplementedException();
        }

        public int GetNativeDataSize()
        {
            throw new NotImplementedException();
        }

        public static ICustomMarshaler GetInstance(string value)
        {
            return new MyOwnMarshalPtrToStringUni(value);
        }
    }

    public interface IAimpString
    {
        AimpActionResult GetChar(int index, out char c);

        string GetData();

        int GetLength();

        int GetHashCode();

        AimpActionResult SetChar(int index, char c);

        AimpActionResult SetData(string chars, int charsCount);

        AimpActionResult Add(IAimpString str);

        AimpActionResult Add(string chars, int charsCount);

        AimpActionResult ChangeCase(AIMPStringCase mode);

        AimpActionResult Clone(out IAimpString str);

        AimpActionResult Compare(IAimpString str, out int compareResult, bool ignoreCase);

        AimpActionResult Compare(string chars, int charsCount, out int compareResult, bool ignoreCase);

        AimpActionResult Delete(int index, int count);

        AimpActionResult Find(IAimpString str, out int index, AIMPStringFindFlags flags, int startFromIndex);

        AimpActionResult Find(string chars, int charsCount, out int index, AIMPStringFindFlags flags, int startFromIndex);

        AimpActionResult Insert(int index, IAimpString str);

        AimpActionResult Insert(int index, string chars, int charsCount);

        AimpActionResult Replace(IAimpString oldPattern, IAimpString newPattern, int flags);

        AimpActionResult Replace(string oldPatternChars, int oldPatternCharsCount, string newPatternChars, int newPatternCharsCount, int flags);

        AimpActionResult SubString(int index, int count, out IAimpString str);
    }
}