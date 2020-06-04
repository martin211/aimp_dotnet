using System;
using System.Collections.Generic;
using System.Text;
using Nuke.Common;

partial class Build
{
    Target DownloadAIMP => _ => _
        .Executes();
}
