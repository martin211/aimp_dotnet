//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Collections.Generic;

namespace DemoPlugin
{
    public class Logger
    {
        private static Logger _instance;

        private List<string> _items;

        public EventHandler<string> OnLogChanged;

        public Logger()
        {
            _items = new List<string>();
        }

        public static Logger Instance => _instance ?? (_instance = new Logger());

        public void AddInfoMessage(string message)
        {
            var msg = $"[Info]: {message}";
            _items.Add(msg);
            OnLogChanged?.Invoke(this, msg);
        }
    }
}
