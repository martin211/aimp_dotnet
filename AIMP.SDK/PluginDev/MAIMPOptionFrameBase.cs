using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace dotNetInteropPlugin.PluginDev
{
    public abstract class MAIMPOptionFrameBase: MarshalByRefObject
    {
        public MAIMPOptionFrameBase()
        {
            ControlsContainer = new Control();
            ControlsContainer.Width = 1000;
            ControlsContainer.Height = 1000;
            ControlsContainer.BackColor = System.Drawing.Color.FromArgb(227, 223, 224);
        }

        /// <summary>
        /// Option frame controls container
        /// </summary>
        public Control ControlsContainer
        {
            get;
            private set;
        }

        /// <summary>
        /// Raised on loading configuration parameters
        /// </summary>
        public event EventHandler LoadParameters;

        protected virtual void OnLoadParameters()
        {
            EventHandler Hndl = LoadParameters;
            if (Hndl != null)
                Hndl(this, EventArgs.Empty);
        }

        /// <summary>
        /// Raised on saving configuration parameters
        /// </summary>
        public event EventHandler SaveParameters;

        protected virtual void OnSaveParameters()
        {
            EventHandler Hndl = SaveParameters;
            if (Hndl != null)
                Hndl(this, EventArgs.Empty);
        }
    }
}
