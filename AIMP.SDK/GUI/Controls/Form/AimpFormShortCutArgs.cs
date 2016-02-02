namespace AIMP.SDK.GUI.Controls.Form
{
    using System;

    using Events;

    public class AimpFormShortCutArgs : EventArgs
    {
        public int Key { get; set; }

        public AimpUIModifiers Modifiers { get; set; }

        public bool Handled { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpFormShortCutArgs(int key, AimpUIModifiers modifiers, bool handled)
        {
            Key = key;
            Modifiers = modifiers;
            Handled = handled;
        }
    }
}