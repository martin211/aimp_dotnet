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
    /// <summary>
    /// Enum AimpStringCase
    /// </summary>
    public enum AimpStringCase
    {
        /// <summary>
        /// The default
        /// </summary>
        Default = 0,
        /// <summary>
        /// The lower
        /// </summary>
        Lower = 1,
        /// <summary>
        /// The upper
        /// </summary>
        Upper = 2,
        /// <summary>
        /// All words with capical letter
        /// </summary>
        AllWordsWithCapicalLetter = 3,
        /// <summary>
        /// The first word with capical letter
        /// </summary>
        FirstWordWithCapicalLetter = 4,
    }

    /// <summary>
    /// Enum AimpStringFindFlags
    /// </summary>
    [Flags]
    public enum AimpStringFindFlags
    {
        /// <summary>
        /// The ignore case
        /// </summary>
        IgnoreCase = 1,
        /// <summary>
        /// The whole word
        /// </summary>
        WholeWord = 2,
    }

    /// <summary>
    /// Interface IAimpString
    /// </summary>
    public interface IAimpString
    {
        /// <summary>
        /// Gets the character.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="c">The c.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType GetChar(int index, out char c);

        /// <summary>
        /// Gets the data.
        /// </summary>
        /// <returns>System.String.</returns>
        string GetData();

        /// <summary>
        /// Gets the length.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetLength();

        /// <summary>
        /// Returns a hash code for this instance.
        /// </summary>
        /// <returns>A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table.</returns>
        int GetHashCode();

        /// <summary>
        /// Sets the character.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="c">The c.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType SetChar(int index, char c);

        /// <summary>
        /// Sets the data.
        /// </summary>
        /// <param name="chars">The chars.</param>
        /// <param name="charsCount">The chars count.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType SetData(string chars, int charsCount);

        /// <summary>
        /// Adds the specified string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Add(IAimpString str);

        /// <summary>
        /// Adds the specified chars.
        /// </summary>
        /// <param name="chars">The chars.</param>
        /// <param name="charsCount">The chars count.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Add(string chars, int charsCount);

        /// <summary>
        /// Changes the case.
        /// </summary>
        /// <param name="mode">The mode.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType ChangeCase(AimpStringCase mode);

        /// <summary>
        /// Clones the specified string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Clone(out IAimpString str);

        /// <summary>
        /// Compares the specified string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <param name="compareResult">The compare result.</param>
        /// <param name="ignoreCase">if set to <c>true</c> [ignore case].</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Compare(IAimpString str, out int compareResult, bool ignoreCase);

        /// <summary>
        /// Compares the specified chars.
        /// </summary>
        /// <param name="chars">The chars.</param>
        /// <param name="charsCount">The chars count.</param>
        /// <param name="compareResult">The compare result.</param>
        /// <param name="ignoreCase">if set to <c>true</c> [ignore case].</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Compare(string chars, int charsCount, out int compareResult, bool ignoreCase);

        /// <summary>
        /// Deletes the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="count">The count.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Delete(int index, int count);

        /// <summary>
        /// Finds the specified string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <param name="index">The index.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="startFromIndex">The start from index.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Find(IAimpString str, out int index, AimpStringFindFlags flags, int startFromIndex);

        /// <summary>
        /// Finds the specified chars.
        /// </summary>
        /// <param name="chars">The chars.</param>
        /// <param name="charsCount">The chars count.</param>
        /// <param name="index">The index.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="startFromIndex">The start from index.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Find(string chars, int charsCount, out int index, AimpStringFindFlags flags, int startFromIndex);

        /// <summary>
        /// Inserts the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="str">The string.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Insert(int index, IAimpString str);

        /// <summary>
        /// Inserts the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="chars">The chars.</param>
        /// <param name="charsCount">The chars count.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Insert(int index, string chars, int charsCount);

        /// <summary>
        /// Replaces the specified old pattern.
        /// </summary>
        /// <param name="oldPattern">The old pattern.</param>
        /// <param name="newPattern">The new pattern.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Replace(IAimpString oldPattern, IAimpString newPattern, int flags);

        /// <summary>
        /// Replaces the specified old pattern chars.
        /// </summary>
        /// <param name="oldPatternChars">The old pattern chars.</param>
        /// <param name="oldPatternCharsCount">The old pattern chars count.</param>
        /// <param name="newPatternChars">The new pattern chars.</param>
        /// <param name="newPatternCharsCount">The new pattern chars count.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType Replace(string oldPatternChars, int oldPatternCharsCount, string newPatternChars, int newPatternCharsCount, int flags);

        /// <summary>
        /// Subs the string.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="count">The count.</param>
        /// <param name="str">The string.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType SubString(int index, int count, out IAimpString str);
    }
}