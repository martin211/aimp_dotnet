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

using System.Collections.Generic;
using System.Xml;
using NUnit;

namespace Aimp.TestRunner.Engine;

/// <summary>
///     ConsoleTestResult represents the result of one test being
///     displayed in the console report.
/// </summary>
public class ConsoleTestResult
{
    private static readonly char[] EOL_CHARS = { '\r', '\n' };

    private readonly XmlNode _resultNode;

    private List<AssertionResult> _assertions;

    /// <summary>
    ///     ConsoleTestResult represents the result of a test in the console runner.
    /// </summary>
    /// <param name="resultNode">An XmlNode representing the result</param>
    /// <param name="reportIndex">Integer index used in the report listing</param>
    public ConsoleTestResult(XmlNode resultNode, int reportIndex)
    {
        _resultNode = resultNode;
        ReportID = reportIndex.ToString();

        Result = resultNode.GetAttribute("result");
        Label = resultNode.GetAttribute("label");
        Site = resultNode.GetAttribute("site");

        Status = Label ?? Result;
        if (Status == "Failed" || Status == "Error")
            if (Site == "SetUp" || Site == "TearDown")
                Status = Site + " " + Status;

        FullName = resultNode.GetAttribute("fullname");
    }

    public string Result { get; }
    public string Label { get; }
    public string Site { get; }
    public string FullName { get; }

    public string ReportID { get; }
    public string Status { get; }

    public string Message =>
        GetTrimmedInnerText(_resultNode.SelectSingleNode("failure/message")) ??
        GetTrimmedInnerText(_resultNode.SelectSingleNode("reason/message"));

    public string StackTrace => GetTrimmedInnerText(_resultNode.SelectSingleNode("failure/stack-trace"));

    public List<AssertionResult> Assertions
    {
        get
        {
            if (_assertions == null)
            {
                _assertions = new List<AssertionResult>();
                foreach (XmlNode assertion in _resultNode.SelectNodes("assertions/assertion"))
                    Assertions.Add(new AssertionResult(assertion));
            }

            return _assertions;
        }
    }

    public void WriteResult(ExtendedTextWriter writer)
    {
        var numAsserts = Assertions.Count;

        if (numAsserts > 0)
        {
            var assertionCounter = 0;
            var assertID = ReportID;

            foreach (var assertion in Assertions)
            {
                if (numAsserts > 1)
                    assertID = string.Format("{0}-{1}", ReportID, ++assertionCounter);

                WriteResult(writer, assertID, Status, FullName, assertion.Message, assertion.StackTrace);
            }
        }
        else
        {
            WriteResult(writer, ReportID, Status, FullName, Message, StackTrace);
        }
    }

    private void WriteResult(ExtendedTextWriter writer, string reportID, string status, string fullName,
        string message,
        string stackTrace)
    {
        var style = GetColorStyle();

        writer.WriteLine(style,
            string.Format("{0}) {1} : {2}", reportID, status, fullName));

        if (!string.IsNullOrEmpty(message))
            writer.WriteLine(ColorStyle.Output, message);

        if (!string.IsNullOrEmpty(stackTrace))
            writer.WriteLine(ColorStyle.Output, stackTrace);

        writer.WriteLine(); // Skip after each item
    }

    private ColorStyle GetColorStyle()
    {
        return Result == "Failed"
            ? ColorStyle.Failure
            : Result == "Warning" || Status == "Ignored"
                ? ColorStyle.Warning
                : ColorStyle.Output;
    }

    private static string GetTrimmedInnerText(XmlNode node)
    {
        // In order to control the format, we trim any line-end chars
        // from end of the strings we write and supply them via calls
        // to WriteLine(). Newlines within the strings are retained.
        return node != null
            ? node.InnerText.TrimEnd(EOL_CHARS)
            : null;
    }

    public struct AssertionResult
    {
        public AssertionResult(XmlNode assertion)
        {
            Message = GetTrimmedInnerText(assertion.SelectSingleNode("message"));
            StackTrace = GetTrimmedInnerText(assertion.SelectSingleNode("stack-trace"));
        }

        public string Message { get; }
        public string StackTrace { get; }
    }
}
