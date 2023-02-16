//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.IO;
using System.Linq;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Nuke.Common;
using Nuke.Common.IO;
using static Nuke.Common.IO.PathConstruction;
using static Nuke.Common.IO.TextTasks;

static class CustomDocFx
{
    public static void WriteCustomDocFx(string docFxFile, string docFxTemplateFile, string generationDirectory, AbsolutePath apiDirectory)
    {
        dynamic json = JObject.Parse(ReadAllText(docFxTemplateFile));

        var metadata = new JArray();
        //Directory.GetDirectories(generationDirectory)
        //    .ForEachLazy(x => Info($"Processing {x}..."))
        //    .Select(directory => CreateMetadataItem(directory, apiDirectory))
        //    .ForEach(metadata.Add);

        json.metadata = metadata;
        WriteAllText(docFxFile, json.ToString(Formatting.Indented));
    }

    static JObject CreateMetadataItem(string directory, AbsolutePath apiDirectory)
    {
        var framework = GetFrameworkToAnalyze(directory);
        var name = new DirectoryInfo(directory).Name;

        var rootDirectory = NukeBuild.RootDirectory;
        var src = (UnixRelativePath)GetRelativePath(rootDirectory, directory);
        var dest = (UnixRelativePath)GetRelativePath(rootDirectory, apiDirectory / name);
        var packages = (UnixRelativePath)GetRelativePath(rootDirectory, NukeBuild.TemporaryDirectory) / "packages";

        dynamic srcObject = new JObject();
        srcObject.src = src.ToString();
        srcObject.files = new JArray($"lib/{framework}/AIMP.SDK.dll");

        dynamic result = new JObject();
        result.src = srcObject;
        result.dest = dest.ToString();
        result.references = new JArray($"{packages}/System.ValueTuple/lib/netstandard1.0/System.ValueTuple.dll");

        return result;
    }

    static string GetFrameworkToAnalyze(string directory)
    {
        return Directory.GetDirectories(Combine(directory, "lib"))
            .Select(x => new DirectoryInfo(x).Name)
            .OrderBy(x => x.StartsWith("netcore") || x.StartsWith("netstandard") ? $"!{x}" : x)
            .Last();
    }
}
