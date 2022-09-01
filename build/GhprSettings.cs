//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace DefaultNamespace
{
    public class DefaultSettings
    {
        [JsonProperty(PropertyName = "default")]
        public GhprSettings Default { get; set; }

        [JsonProperty(PropertyName = "projects")]
        public IList<Project> Projects { get; set; }
    }

    public class GhprSettings
    {
        [JsonProperty(PropertyName = "outputPath")]
        public string OutputPath { get; set; }

        [JsonProperty(PropertyName = "dataServiceFile")]
        public string DataServiceFile { get; set; }

        [JsonProperty(PropertyName = "loggerFile")]
        public string LoggerFile { get; set; }

        [JsonProperty(PropertyName = "sprint")]
        public string Sprint { get; set; }

        [JsonProperty(PropertyName = "reportName")]
        public string ReportName { get; set; }

        [JsonProperty(PropertyName = "projectName")]
        public string ProjectName { get; set; }

        [JsonProperty(PropertyName = "runName")]
        public string RunName { get; set; }

        [JsonProperty(PropertyName = "runGuid")]
        public string RunGuid { get; set; }

        [JsonProperty(PropertyName = "realTimeGeneration")]
        public string RealTimeGeneration { get; set; } = "True";

        [JsonProperty(PropertyName = "runsToDisplay")]
        public string RunsToDisplay { get; set; } = "5";

        [JsonProperty(PropertyName = "testsToDisplay")]
        public string TestsToDisplay { get; set; } = "5";

        [JsonProperty(PropertyName = "escapeTestOutput")]
        public bool EscapeTestOutput { get; set; } = true;

        [JsonProperty(PropertyName = "retention")]
        public Retention Retention { get; set; } = new Retention();
    }

    public class Retention
    {
        [JsonProperty(PropertyName = "amount")]
        public int Amount { get; set; } = 1000;

        [JsonProperty(PropertyName = "till")]
        public string Till { get; set; } = "2010-08-20 10:00:00";
    }

    public class Project
    {
        [JsonProperty(PropertyName = "pattern")]
        public string Pattern { get; set; }

        [JsonProperty(PropertyName = "settings")]
        public IList<Setting> Settings { get; set; }
    }

    public class Setting
    {
        [JsonProperty(PropertyName = "outputPath")]
        public string OutputPath { get; set; }
    }
}