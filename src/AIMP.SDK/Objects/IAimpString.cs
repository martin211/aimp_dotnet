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
using System.Runtime.InteropServices;

namespace AIMP.SDK.Objects
{
    public enum AimpStringCase
    {
        Default = 0,
        Lower = 1,
        Upper = 2,
        AllWordsWithCapicalLetter = 3,
        FirstWordWithCapicalLetter = 4,
    }

    [Flags]
    public enum AimpStringFindFlags
    {
        IgnoreCase = 1,
        WholeWord = 2,
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

        ActionResultType ChangeCase(AimpStringCase mode);

        ActionResultType Clone(out IAimpString str);

        ActionResultType Compare(IAimpString str, out int compareResult, bool ignoreCase);

        ActionResultType Compare(string chars, int charsCount, out int compareResult, bool ignoreCase);

        ActionResultType Delete(int index, int count);

        ActionResultType Find(IAimpString str, out int index, AimpStringFindFlags flags, int startFromIndex);

        ActionResultType Find(string chars, int charsCount, out int index, AimpStringFindFlags flags, int startFromIndex);

        ActionResultType Insert(int index, IAimpString str);

        ActionResultType Insert(int index, string chars, int charsCount);

        ActionResultType Replace(IAimpString oldPattern, IAimpString newPattern, int flags);

        ActionResultType Replace(string oldPatternChars, int oldPatternCharsCount, string newPatternChars, int newPatternCharsCount, int flags);

        ActionResultType SubString(int index, int count, out IAimpString str);
    }
}