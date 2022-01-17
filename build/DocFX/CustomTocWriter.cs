// Copyright Eugeniy Bogdan 2018.
// Distributed under the MIT License.
// https://github.com/nuke-build/web/blob/master/LICENSE

using System.Collections.Generic;
using System.IO;
using System.Linq;
using JetBrains.Annotations;
using Mono.Cecil;
using Nuke.Common.IO;
using Nuke.Common.Utilities.Collections;
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
        public IList<Item> Items { get; set; }
        public string Namespace { get; set; }
    }

    public static void WriteCustomTocs(
        AbsolutePath apiDirectory,
        AbsolutePath projectDirectory,
        IEnumerable<string> assemblyFiles)
    {
        var assemblies = assemblyFiles.ForEachLazy(x => Serilog.Log.Information($"Loading {x}")).Select(AssemblyDefinition.ReadAssembly).ToList();
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
                    var childItems = typeDefinitions
                        .Where(c => c.Key.Equals(item.Namespace))
                        .SelectMany(c => c.Value);

                    item.Items = childItems.Select(c => new Item
                    {
                        Name = c.Name,
                        Uid = c.FullName,
                        Namespace = c.Namespace
                    })
                        .ToList();
                }
            }

            var items = YamlDeserializeFromFile<Item[]>(projectDirectory / "toc.template.yml");

            foreach (var item in items)
            {
                var subItems = item.Items != null
                    ? item.Items.ToList()
                    : new List<Item>();

                ApplyName(item);

                if (subItems.Any())
                {
                    foreach (var subItem in subItems)
                    {
                        var itemSubItems = subItem.Items != null
                            ? subItem.Items.ToList()
                            : new List<Item>();

                        ApplyName(subItem);
                        item.Items.Insert(0, subItem);

                        if (itemSubItems.Any())
                        {
                            foreach (var subItemItem in itemSubItems)
                            {
                                ApplyName(subItemItem);
                                subItem.Items.Insert(0, subItemItem);
                            }
                        }
                    }
                }
            }

            //items.ForEach(ApplyName);
            if (!Directory.Exists(apiDirectory))
            {
                Directory.CreateDirectory(apiDirectory);
            }

            //if (!File.Exists(apiDirectory / "toc.yml"))
            //{
            //    File.Create(apiDirectory / "toc.yml");
            //}

            YamlSerializeToFile(items, apiDirectory / "toc.yml");
        }
        finally
        {
            assemblies.ForEach(x => x.Dispose());
        }
    }
}
