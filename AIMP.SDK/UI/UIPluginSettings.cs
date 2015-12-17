using System;
using System.Runtime.InteropServices;

namespace AIMP.SDK.UI
{
    using System.ComponentModel;
    using System.Windows.Forms;

    public partial class UIPluginSettings : Form
    {
        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        public UIPluginSettings(IntPtr parent) : this()
        {
            SetParent(Handle, parent);
        }

        public UIPluginSettings()
        {
            InitializeComponent();
        }

        public void ReloadInfo()
        {
            dataGridView1.Rows.Clear();
			dataGridView2.Rows.Clear();

            if (pluginsCollection != null)
            {
                foreach (PluginInformation pinf in pluginsCollection)
                {
                    if (pinf.IsLoaded)
                        dataGridView2.Rows.Add(true, new DisplayableForPlugins(pinf));
                    else
                        dataGridView1.Rows.Add(false, new DisplayableForPlugins(pinf));
                }

                dataGridView1.Sort(dataGridView1.Columns[1], ListSortDirection.Ascending);
                dataGridView2.Sort(dataGridView2.Columns[1], ListSortDirection.Ascending);
            }
        }

        public PluginInfoCollection pluginsCollection
        {
            get;
            set;
        }

        private void dataGridView1_CellValueChanged(System.Object sender, System.Windows.Forms.DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 0 && e.RowIndex >= 0)
            {
                DisplayableForPlugins PlgInf = (DisplayableForPlugins)dataGridView1.Rows[e.RowIndex].Cells[1].Value;
                if (PlgInf.plugInfo.Load())
                {
                    dataGridView1.Rows.RemoveAt(e.RowIndex);
                    dataGridView2.Rows.Add(true, PlgInf);
                }
            }
        }
        private void dataGridView2_CellValueChanged(System.Object sender, System.Windows.Forms.DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 0 && e.RowIndex >= 0)
            {
                DisplayableForPlugins PlgInf = (DisplayableForPlugins)dataGridView2.Rows[e.RowIndex].Cells[1].Value;
                if (PlgInf.plugInfo.Unload())
                {
                    dataGridView2.Rows.RemoveAt(e.RowIndex);
                    dataGridView1.Rows.Add(false, PlgInf);
                    if (dataGridView2.Rows.Count == 0)
                        button2.Enabled = false;
                }
            }
        }
        private void dataGridView1_CurrentCellDirtyStateChanged(System.Object sender, System.EventArgs e)
        {
            if (dataGridView1.CurrentCell is DataGridViewCheckBoxCell)
                dataGridView1.CommitEdit(DataGridViewDataErrorContexts.Commit);
        }
        private void dataGridView2_CurrentCellDirtyStateChanged(System.Object sender, System.EventArgs e)
        {
            if (dataGridView2.CurrentCell is DataGridViewCheckBoxCell)
                dataGridView2.CommitEdit(DataGridViewDataErrorContexts.Commit);
        }
        private void dataGridView2_SelectionChanged(System.Object sender, System.EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count > 0)
            {
                DisplayableForPlugins PlgInf = (DisplayableForPlugins)dataGridView2.SelectedRows[0].Cells[1].Value;
                button2.Enabled = PlgInf.plugInfo.HasSettingDialog;
            }
        }
        private void button2_Click(System.Object sender, System.EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count > 0)
            {
                DisplayableForPlugins PlgInf = (DisplayableForPlugins)dataGridView2.SelectedRows[0].Cells[1].Value;
                if (PlgInf.plugInfo.HasSettingDialog)
                    PlgInf.plugInfo.ShowSettingDialog(this);
            }
        }
    }

    public class DisplayableForPlugins
    {
        public DisplayableForPlugins(PluginInformation pi)
        {
            plugInfo = pi;
            inFullDescStr = plugInfo.PluginInfo.Name + " v" + plugInfo.PluginInfo.Version +
                "(" + plugInfo.PluginInfo.Author + ")\n" +
                "[" + plugInfo.AssemblyFileName + "] " + plugInfo.PluginInfo.Description;
        }

        private string inFullDescStr = "";
        public PluginInformation plugInfo
        {
            get;
            set;
        }

        public override string ToString()
        {
            return inFullDescStr;
        }
    }
}
