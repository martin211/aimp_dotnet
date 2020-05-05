// Copyright Eugeniy Bogdan 2018.
// Distributed under the MIT License.
// https://github.com/nuke-build/web/blob/master/LICENSE

using System.Collections.Generic;
using System.Linq;
using JetBrains.Annotations;
using Mono.Cecil;
using Nuke.Common.IO;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.Logger;
using static Nuke.Common.IO.SerializationTasks;

static class CustomTocWriter
{
    [UsedImplicitly(ImplicitUseKindFlags.Access, ImplicitUseTargetFlags.WithMembers)]
    class Item
    {
        public string Uid { get; set; }
        public string Name { get; set; }
        public string Href { get; set; }
        public string Icon { get; set; }
        public string TopicUid { get; set; }
        public string Separator { get; set; }
        public Item[] Items { get; set; }
        public string Namespace { get; set; }
    }

    public static void WriteCustomTocs(
        AbsolutePath apiDirectory,
        AbsolutePath projectDirectory,
        IEnumerable<string> assemblyFiles)
    {
        var assemblies = assemblyFiles.ForEachLazy(x => Info($"Loading {x}")).Select(AssemblyDefinition.ReadAssembly).ToList();
        try
        {
            var typeDefinitions = assemblies
                .SelectMany(x => x.MainModule.Types)
                .GroupBy(c => c.Namespace)
                .ToDictionary(c => c.Key, c => c.ToList());

            void ApplyName(Item item)
            {
                if (!string.IsNullOrWhiteSpace(item.Namespace))
                {
                    var childItems = typeDefinitions.Where(c => c.Key.Contains(item.Namespace)).SelectMany(c => c.Value);
                    item.Items = childItems.Select(c => new Item
                    {
                        Name = c.Name,
                        Uid = c.FullName
                    })
                        .ToArray();
                }

                if (item.Items == null)
                    return;

                foreach (var subItem in item.Items)
                    ApplyName(subItem);
            }

            var items = YamlDeserializeFromFile<Item[]>(projectDirectory / "toc.template.yml");
            items.ForEach(ApplyName);
            YamlSerializeToFile(items, apiDirectory / "toc.yml");
        }
        finally
        {
            assemblies.ForEach(x => x.Dispose());
        }
    }
}
