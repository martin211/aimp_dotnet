using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.MUIManager;
using AIMP.SDK.Options;
using AIMP.SDK.Player;

namespace dotnet_ExtendDialogWindow
{
    internal partial class SettingsForm : Form
    {
        //public PluginSettings Settings { get; set; }

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        public static string _settingButtonText = "Options";

        private IAimpPlayer _player;

        private IAimpOptionsDialogFrame _parentFrame;

        public SettingsForm(IntPtr parentWindow, IAimpPlayer player, IAimpOptionsDialogFrame parentFrame)
            : this()
        {
            SetParent(Handle, parentWindow);
            _parentFrame = parentFrame;

            var buttonCell = new DataGridViewDisableButtonColumn
            {
                Resizable = DataGridViewTriState.False,
                Width = 100,
                AutoSizeMode = DataGridViewAutoSizeColumnMode.None
            };

            dataGridView1.Columns.Insert(2, buttonCell);
            SetLocaleText(player.MUIManager);

            cbDebugMode.CheckedChanged += CbDebugModeOnCheckedChanged;

            _player = player;

            Show();

            WindowState = FormWindowState.Maximized;
        }

        private void CbDebugModeOnCheckedChanged(object sender, EventArgs eventArgs)
        {
            //Settings.IsDebugMode = cbDebugMode.Checked;
        }

        public SettingsForm()
        {
            InitializeComponent();

            dataGridView1.CellValueChanged += dataGridView1_CellValueChanged;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            dataGridView1.CurrentCellDirtyStateChanged += dataGridView1_CurrentCellDirtyStateChanged;
            dataGridView1.DataBindingComplete += dataGridView1_DataBindingComplete;
            dataGridView1.RowsAdded += dataGridView1_RowsAdded;
        }

        private void SetLocaleText(IAimpMUIManager muiManager)
        {
            lCaption.Text = muiManager.GetValue("DotNet.Plugins\\Caption");
            tabPlugins.Text = muiManager.GetValue("DotNet.Plugins\\Plugins");
            tabSettings.Text = muiManager.GetValue("DotNet.Plugins\\Settings");
            cbDebugMode.Text = muiManager.GetValue("DotNet.Settings\\DebugMode");

            var setText = muiManager.GetValue("DotNet.Plugins\\bSettings");
            if (!string.IsNullOrWhiteSpace(setText))
            {
                _settingButtonText = setText;
            }
        }

        public void ReloadSettings()
        {
            dataGridView1.Rows.Clear();

            //if (Settings != null && Settings.AimpPlugin != null)
            //{
            //    foreach (var plugin in Settings.AimpPlugin)
            //    {
            //        dataGridView1.Rows.Add(plugin.IsLoaded, new DisplayableForPlugins(plugin));
            //    }

            //    dataGridView1.Sort(dataGridView1.Columns[1], ListSortDirection.Ascending);

            //    cbDebugMode.Checked = Settings.IsDebugMode;
            //}
        }

        internal class DisplayableForPlugins
        {
            public DisplayableForPlugins(PluginInformation pi)
            {
                plugInfo = pi;
            }

            public PluginInformation plugInfo
            {
                get;
                set;
            }

            public override string ToString()
            {
                return plugInfo.PluginInfo.Name + " v" + plugInfo.PluginInfo.Version +
                    " (" + plugInfo.PluginInfo.Author + ")\n" +
                    "[" + plugInfo.AssemblyFileName + "] " + plugInfo.PluginInfo.Description; ;
            }
        }

        private void SettingsForm_Load(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 0 && e.RowIndex >= 0)
            {
                var plugin = (DisplayableForPlugins)dataGridView1.Rows[e.RowIndex].Cells[1].Value;
                DataGridViewCheckBoxCell cell = dataGridView1.Rows[e.RowIndex].Cells[0] as DataGridViewCheckBoxCell;
                if ((bool)cell.Value)
                {
                    if (!plugin.plugInfo.Load())
                    {
                        cell.Value = cell.FalseValue;
                    }
                }
                else
                {
                    plugin.plugInfo.Unload();
                }

                dataGridView1.Refresh();
            }
        }

        private void dataGridView1_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            dataGridView1.CommitEdit(DataGridViewDataErrorContexts.Commit);
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 2)
            {
                var plugin = (DisplayableForPlugins)dataGridView1.Rows[e.RowIndex].Cells[1].Value;
                if (plugin.plugInfo.HasSettingDialog)
                {
                    plugin.plugInfo.ShowSettingDialog(this);
                }
            }
        }

        private void dataGridView1_RowsAdded(object sender, DataGridViewRowsAddedEventArgs e)
        {

        }

        private void dataGridView1_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
        {

        }

        private void cbDebugMode_CheckedChanged(object sender, EventArgs e)
        {
            _player.ServiceOptionsDialog.FrameModified(_parentFrame);
        }
    }

    public class DataGridViewDisableButtonColumn : DataGridViewButtonColumn
    {
        public DataGridViewDisableButtonColumn()
        {
            CellTemplate = new DataGridViewDisableButtonCell();
        }
    }

    public class DataGridViewDisableButtonCell : DataGridViewButtonCell
    {
        // Override the Clone method so that the Enabled property is copied. 
        public override object Clone()
        {
            DataGridViewDisableButtonCell cell = (DataGridViewDisableButtonCell)base.Clone();
            return cell;
        }

        public DataGridViewDisableButtonCell()
        {
        }

        protected override void Paint(
            Graphics graphics,
            Rectangle clipBounds,
            Rectangle cellBounds,
            int rowIndex,
            DataGridViewElementStates elementState,
            object value,
            object formattedValue,
            string errorText,
            DataGridViewCellStyle cellStyle,
            DataGridViewAdvancedBorderStyle advancedBorderStyle,
            DataGridViewPaintParts paintParts)
        {
            // The button cell is disabled, so paint the border,   
            // background, and disabled button for the cell. 
            var plugin = ((SettingsForm.DisplayableForPlugins)(DataGridView.Rows[RowIndex].Cells[1].Value)).plugInfo;
            if (plugin != null && !plugin.HasSettingDialog)
            {
                // Draw the cell background, if specified. 
                if ((paintParts & DataGridViewPaintParts.Background) == DataGridViewPaintParts.Background)
                {
                    SolidBrush cellBackground = new SolidBrush(cellStyle.BackColor);
                    graphics.FillRectangle(cellBackground, cellBounds);
                    cellBackground.Dispose();
                }
                // Draw the cell borders, if specified. 
                if ((paintParts & DataGridViewPaintParts.Border) == DataGridViewPaintParts.Border)
                {
                    PaintBorder(graphics, clipBounds, cellBounds, cellStyle, advancedBorderStyle);
                }

                // Calculate the area in which to draw the button.
                Rectangle buttonArea = cellBounds;
                Rectangle buttonAdjustment = BorderWidths(advancedBorderStyle);
                buttonArea.X += buttonAdjustment.X;
                buttonArea.Y += buttonAdjustment.Y;
                buttonArea.Height -= buttonAdjustment.Height;
                buttonArea.Width -= buttonAdjustment.Width;

                buttonArea.Height -= 1;

                graphics.FillRectangle(new SolidBrush(Color.White), buttonArea);
            }
            else
            {
                base.Paint(graphics, clipBounds, cellBounds, rowIndex, elementState, value, SettingsForm._settingButtonText, errorText, cellStyle, advancedBorderStyle, paintParts);
            }
        }
    }


    public class WindowHandleInfo
    {
        private delegate bool EnumWindowProc(IntPtr hwnd, IntPtr lParam);

        [DllImport("user32")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool EnumChildWindows(IntPtr window, EnumWindowProc callback, IntPtr lParam);

        private IntPtr _MainHandle;

        public WindowHandleInfo(IntPtr handle)
        {
            this._MainHandle = handle;
        }

        public List<IntPtr> GetAllChildHandles()
        {
            List<IntPtr> childHandles = new List<IntPtr>();

            GCHandle gcChildhandlesList = GCHandle.Alloc(childHandles);
            IntPtr pointerChildHandlesList = GCHandle.ToIntPtr(gcChildhandlesList);

            try
            {
                EnumWindowProc childProc = new EnumWindowProc(EnumWindow);
                EnumChildWindows(this._MainHandle, childProc, pointerChildHandlesList);
            }
            finally
            {
                gcChildhandlesList.Free();
            }

            return childHandles;
        }

        private bool EnumWindow(IntPtr hWnd, IntPtr lParam)
        {
            GCHandle gcChildhandlesList = GCHandle.FromIntPtr(lParam);

            if (gcChildhandlesList == null || gcChildhandlesList.Target == null)
            {
                return false;
            }

            List<IntPtr> childHandles = gcChildhandlesList.Target as List<IntPtr>;
            childHandles.Add(hWnd);

            return true;
        }
    }
}


