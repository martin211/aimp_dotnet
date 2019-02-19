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
            if (player.ServiceFileTagEditor.EditFile(fileName, out var editor) == AimpActionResult.Ok)
            {
                if (editor.GetMixedInfo(out var fileInfo) == AimpActionResult.OK)
                {
                    lTitle.Text = fileInfo.Title;
                    lAlbum.Text = fileInfo.Album;
                    lArtist.Text = fileInfo.Artist;
                    lGenre.Text = fileInfo.Genre;

                    if (fileInfo.AlbumArt != null)
                    {
                        cover.Image = fileInfo.AlbumArt;
                    }
                }

                var count = editor.GetTagCount();
                for (var i = 0; i < count; i++)
                {
                    if (editor.GetTag(i, out var tag) == AimpActionResult.OK)
                    {
                        var tab = new TabPage(tag.TagId.ToString())
                        {
                            Text = tag.TagId.ToString(),
                            Tag = tag
                        };

                        var editorControl = new TagEditControl(tag);
                        tab.Controls.Add(editorControl);
                        tabControl1.TabPages.Add(tab);
                    }
                }
            }
        }
    }
}
