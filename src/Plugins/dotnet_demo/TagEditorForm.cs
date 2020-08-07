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

using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Playlist;

namespace DemoPlugin
{
    public partial class TagEditorForm : Form
    {
        public TagEditorForm(IAimpPlaylistItem item, IAimpPlayer player)
        {
            InitializeComponent();

            var fileName = item.FileName;
            fileName = fileName.EndsWith(":0") ? fileName.Replace(":0", string.Empty) : fileName;
            var result = player.ServiceFileTagEditor.EditFile(fileName);
            if (result.ResultType == ActionResultType.OK)
            {
                var editor = result.Result;
                var mixedResult = editor.GetMixedInfo();

                if (mixedResult.ResultType == ActionResultType.OK)
                {
                    lTitle.Text = mixedResult.Result.Title;
                    lAlbum.Text = mixedResult.Result.Album;
                    lArtist.Text = mixedResult.Result.Artist;
                    lGenre.Text = mixedResult.Result.Genre;

                    if (mixedResult.Result.AlbumArt != null)
                    {
                        cover.Image = mixedResult.Result.AlbumArt;
                    }
                }

                var count = editor.GetTagCount();
                for (var i = 0; i < count; i++)
                {
                    var r = editor.GetTag(i);
                    if (r.ResultType == ActionResultType.OK)
                    {
                        var tab = new TabPage(r.Result.TagId.ToString())
                        {
                            Text = r.Result.TagId.ToString(),
                            Tag = r.Result
                        };

                        var editorControl = new TagEditControl(r.Result);
                        tab.Controls.Add(editorControl);
                        tabControl1.TabPages.Add(tab);
                    }
                }
            }
        }
    }
}
