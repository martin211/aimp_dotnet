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
        ActionResultType GetChar(int index, out char c);

        string GetData();

        int GetLength();

        int GetHashCode();

        ActionResultType SetChar(int index, char c);

        ActionResultType SetData(string chars, int charsCount);

        ActionResultType Add(IAimpString str);

        ActionResultType Add(string chars, int charsCount);

        ActionResultType ChangeCase(AIMPStringCase mode);

        ActionResultType Clone(out IAimpString str);

        ActionResultType Compare(IAimpString str, out int compareResult, bool ignoreCase);

        ActionResultType Compare(string chars, int charsCount, out int compareResult, bool ignoreCase);

        ActionResultType Delete(int index, int count);

        ActionResultType Find(IAimpString str, out int index, AIMPStringFindFlags flags, int startFromIndex);

        ActionResultType Find(string chars, int charsCount, out int index, AIMPStringFindFlags flags, int startFromIndex);

        ActionResultType Insert(int index, IAimpString str);

        ActionResultType Insert(int index, string chars, int charsCount);

        ActionResultType Replace(IAimpString oldPattern, IAimpString newPattern, int flags);

        ActionResultType Replace(string oldPatternChars, int oldPatternCharsCount, string newPatternChars, int newPatternCharsCount, int flags);

        ActionResultType SubString(int index, int count, out IAimpString str);
    }
}