using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    //public class SafeEventManager
    //{
    //    internal int AssocPluginID
    //    {
    //        get;
    //        set;
    //    }
    //    internal int AssocAppDomainID
    //    {
    //        get;
    //        private set;
    //    }
    //    internal SafeEventManager(int PlgID)
    //    {
    //        AssocPluginID = PlgID;
    //        AssocAppDomainID = AppDomain.CurrentDomain.Id;
    //    }

    //    private Dictionary<MAIMPPlayerEventsDelegate, MAIMPSafeCorssDomainCaller> OneToOneMap = new Dictionary<MAIMPPlayerEventsDelegate, MAIMPSafeCorssDomainCaller>();

    //    public MAIMPPlayerEventsDelegate GetInvocation(MAIMPPlayerEventsDelegate dlg)
    //    {
    //        MAIMPSafeCorssDomainCaller res = null;
    //        if (!OneToOneMap.TryGetValue(dlg, out res))
    //        {
    //            res = new MAIMPSafeCorssDomainCaller(dlg, AssocPluginID);
    //            OneToOneMap[dlg] = res;
    //        }
    //        return new MAIMPPlayerEventsDelegate(res.CallFunction);
    //    }
    //    public void RemoveInvocation(MAIMPPlayerEventsDelegate dlg)
    //    {
    //        OneToOneMap.Remove(dlg);
    //    }

    //    public MAIMPPlayerEventsDelegate GetAndRemoveInvocation(MAIMPPlayerEventsDelegate dlg)
    //    {
    //        MAIMPSafeCorssDomainCaller res = null;
    //        if (OneToOneMap.TryGetValue(dlg, out res))
    //        {
    //            OneToOneMap.Remove(dlg);
    //            return new MAIMPPlayerEventsDelegate(res.CallFunction);
    //        }
    //        return null;
    //    }

    //    public void RemoveAllInvocations()
    //    {
    //        OneToOneMap.Clear();
    //    }

    //}

    internal class MAIMPSafeCorssDomainCaller : MarshalByRefObject
    {
        public MAIMPSafeCorssDomainCaller(MAIMPPlayerEventsDelegate dlg, int PlugID)
        {
            if (dlg == null)
                throw new ArgumentNullException("dlg");
            innerDel = dlg;
            PluginUID = PlugID;
        }

        public int PluginUID
        {
            get;
            private set;
        }
        public MAIMPPlayerEventsDelegate innerDel
        {
            get;
            private set;
        }
        public void CallFunction(object sender, MAIMPPlayerEventArgs args)
        {
            innerDel(sender, args);
        }

    }



    //public class MAIMPCorssDomainCaller: MarshalByRefObject
    //{
    //    public MAIMPCorssDomainCaller(MAIMPPlayerEventsDelegate dlg)
    //    {
    //        if (dlg == null)
    //            throw new ArgumentNullException("dlg");
    //        innerDel = dlg;
    //        DomainUID = AppDomain.CurrentDomain.Id;
    //    }

    //    public void CallFunction(object sender, MAIMPPlayerEventArgs args)
    //    {
    //        innerDel(sender, args);
    //    }
    //    internal int DomainUID
    //    {
    //        get;
    //        private set;
    //    }


    //    private MAIMPPlayerEventsDelegate innerDel = null;

    //    public static MAIMPPlayerEventsDelegate GetInvocation(out MAIMPCorssDomainCaller sbObj, MAIMPPlayerEventsDelegate dlg)
    //    {
    //        sbObj = new MAIMPCorssDomainCaller(dlg);
    //        return new MAIMPPlayerEventsDelegate(sbObj.CallFunction);
    //    }
    //    public MAIMPPlayerEventsDelegate GetInvocation()
    //    {
    //        return new MAIMPPlayerEventsDelegate(CallFunction);
    //    }
    //}
}
