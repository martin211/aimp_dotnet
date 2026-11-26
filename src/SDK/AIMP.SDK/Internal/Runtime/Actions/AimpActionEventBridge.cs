using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Actions;
using AIMP.SDK.Actions.Objects;

namespace AIMP.Internal.Runtime.Actions
{
    /// <summary>
    /// Bridges a managed callback to <c>IAIMPActionEvent</c>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class AimpActionEventBridge : IAIMPActionEventNative
    {
        private readonly EventHandler _handler;
        private readonly IAimpActionEvent _actionEvent;

        public AimpActionEventBridge(Action callback)
        {
            Callback = callback;
        }

        public AimpActionEventBridge(EventHandler handler)
        {
            _handler = handler;
        }

        public AimpActionEventBridge(IAimpActionEvent actionEvent)
        {
            _actionEvent = actionEvent;
        }

        public Action Callback { get; }

        [PreserveSig]
        public void OnExecute(IntPtr data)
        {
            try
            {
                Callback?.Invoke();
                _handler?.Invoke(this, EventArgs.Empty);
                RaiseOnExecute(_actionEvent);
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
            }
        }

        private static readonly Dictionary<Type, FieldInfo> OnExecuteFields =
            new Dictionary<Type, FieldInfo>();

        /// <summary>
        /// Raises the <see cref="IAimpActionEvent.OnExecute"/> event. The event cannot
        /// be raised from outside the implementing type, so the compiler generated
        /// backing field is read through reflection.
        /// </summary>
        private static void RaiseOnExecute(IAimpActionEvent actionEvent)
        {
            if (actionEvent == null)
            {
                return;
            }

            var type = actionEvent.GetType();
            FieldInfo field;

            lock (OnExecuteFields)
            {
                if (!OnExecuteFields.TryGetValue(type, out field))
                {
                    field = type.GetField(
                        "OnExecute",
                        BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
                    OnExecuteFields[type] = field;
                }
            }

            var handler = field?.GetValue(actionEvent) as EventHandler;
            handler?.Invoke(actionEvent, EventArgs.Empty);
        }

        /// <summary>
        /// Creates a native <c>IAIMPActionEvent*</c> that invokes the callback.
        /// </summary>
        public static IntPtr CreatePointer(Action callback)
        {
            return callback == null
                ? IntPtr.Zero
                : AimpComHelper.GetPointer(
                    new AimpActionEventBridge(callback),
                    typeof(IAIMPActionEventNative));
        }

        /// <summary>
        /// Creates a native <c>IAIMPActionEvent*</c> that raises the event.
        /// </summary>
        public static IntPtr CreatePointer(EventHandler handler)
        {
            return handler == null
                ? IntPtr.Zero
                : AimpComHelper.GetPointer(
                    new AimpActionEventBridge(handler),
                    typeof(IAIMPActionEventNative));
        }

        /// <summary>
        /// Creates a native <c>IAIMPActionEvent*</c> for a managed handler object.
        /// </summary>
        public static IntPtr CreatePointer(IAimpActionEvent actionEvent)
        {
            return actionEvent == null
                ? IntPtr.Zero
                : AimpComHelper.GetPointer(
                    new AimpActionEventBridge(actionEvent),
                    typeof(IAIMPActionEventNative));
        }
    }
}