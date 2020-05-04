using Nuke.Common;
using Nuke.Common.Tools.DocFX;
using Nuke.Common.Tools.Git;

public class Documentation : NukeBuild
{
    string DocFxFile => RootDirectory / "documentation" / "docfx.json";

    Target CheckoutDocumentation => _ => _
        .Executes(() =>
        {
            
        });

    Target BuildDocumentation => _ => _
        .Executes(() =>
        {
            DocFXTasks.DocFXBuild(s => s
                .SetConfigFile(DocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose)
            );
        });
}
