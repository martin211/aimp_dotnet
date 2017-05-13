using System;
using System.Collections.Generic;

namespace DemoPlugin
{
    public class Logger
    {
        private static Logger _instance;

        public static Logger Instance => _instance ?? (_instance = new Logger());

        private List<string> _items;

        public Logger()
        {
            _items = new List<string>();
        }

        public void AddInfoMessage(string message)
        {
            var msg = $"[Info]: {message}";
            _items.Add(msg);
            OnLogChanged?.Invoke(this, msg);
        }

        public EventHandler<string> OnLogChanged;
    }
}