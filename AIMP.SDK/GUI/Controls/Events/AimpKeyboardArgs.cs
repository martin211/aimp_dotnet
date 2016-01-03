namespace AIMP.SDK.GUI.Controls.Events
{
    using System;
    public class AimpKeyboardArgs : EventArgs
    {
        public int Key { get; set; }

        public AimpUIModifiers Modifiers { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpKeyboardArgs(int key, AimpUIModifiers modifiers)
        {
            Key = key;
            Modifiers = modifiers;
        }
    }

    public class AimpKeyArgs : EventArgs
    {
        public int Key { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpKeyArgs(int key)
        {
            Key = key;
        }
    }
}