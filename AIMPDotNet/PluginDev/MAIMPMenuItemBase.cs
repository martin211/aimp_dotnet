using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Collections.ObjectModel;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Menu element
    /// </summary>
    public abstract class MAIMPMenuItemBase: MarshalByRefObject
    {
        public MAIMPMenuItemBase()
        {

        }
        public MAIMPMenuItemBase(MAIMPMenuItemBase mi)
        {
            inItemType = mi.inItemType;
            inIsChecked = mi.inIsChecked;
            inIsEnabled = mi.inIsEnabled;
            inText = mi.inText;
            inBmpImage = mi.inBmpImage;
            Click = mi.Click;
        }

        private AIMPMenuItemType inItemType = AIMPMenuItemType.Normal;
        /// <summary>
        /// Type of menu item
        /// </summary>
        public AIMPMenuItemType ItemType
        {
            get { return inItemType; }
            set
            {
                if (inItemType != value)
                {
                    inItemType = value;
                    UpdateData();
                }
            }
        }

        private bool inIsChecked = false;
        /// <summary>
        /// Is menu item checked
        /// </summary>
        public bool IsChecked
        {
            get { return inIsChecked; }
            set
            {
                if (inIsChecked != value)
                {
                    inIsChecked = value;
                    UpdateData();
                }
            }
        }

        private Bitmap inBmpImage = null;
        /// <summary>
        /// Image for menu item
        /// </summary>
        public Bitmap BmpImage
        {
            get { return inBmpImage; }
            set
            {
                if (inBmpImage != value)
                {
                    inBmpImage = value;
                    UpdateData();
                }
            }
        }

        private string inText = "";
        /// <summary>
        /// Displaying text
        /// </summary>
        public string Text
        {
            get { return inText; }
            set
            {
                if (inText != value)
                {
                    inText = value;
                    UpdateData();
                }
            }
        }

        private bool inIsEnabled = true;
        /// <summary>
        /// Is menu item enabled
        /// </summary>
        public bool IsEnabled
        {
            get { return inIsEnabled; }
            set
            {
                if (inIsEnabled != value)
                {
                    inIsEnabled = value;
                    UpdateData();
                }
            }
        }

        /// <summary>
        /// Raised after click on menu itme (or after open submenus)
        /// </summary>
        public event EventHandler Click;
     
        protected virtual void OnClick()
        {
            if (ItemType == AIMPMenuItemType.CheckBox)
                inIsChecked = !inIsChecked;

            EventHandler Ev = Click;
            if (Ev != null)
                Ev(this, EventArgs.Empty);
        }

        internal abstract bool UpdateData();

        
    }
}
