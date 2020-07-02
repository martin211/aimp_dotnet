namespace DefaultNamespace
{
    public class DefaultSettings
    {
        public GhprSettings Default { get; set; }
    }

    public class GhprSettings
    {
        public string OutputPath { get; set; }

        public string DataServiceFile { get; set; }

        public string LoggerFile { get; set; }

        public string Sprint { get; set; }

        public string ReportName { get; set; }

        public string ProjectName { get; set; }

        public string RunName { get; set; }

        public string RunGuid { get; set; }

        public string RealTimeGeneration { get; set; } = "True";

        public string RunsToDisplay { get; set; } = "5";

        public string TestsToDisplay { get; set; } = "5";

        public bool EscapeTestOutput { get; set; } = true;

        public Retention Retention { get; set; } = new Retention();
    }

    public class Retention
    {
        public int Amount { get; set; } = 1000;
        public string Till { get; set; } = "2010-08-20 10:00:00";
    }

    public class Project
    {
        public string Pattern { get; set; }


    }

    public class Setting
    {

    }
}