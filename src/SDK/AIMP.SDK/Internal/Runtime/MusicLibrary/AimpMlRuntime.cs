using System;
using System.Collections;
using System.Collections.Generic;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.Internal.Runtime.MusicLibrary
{
    /// <summary>
    /// Helpers shared by the music library wrappers.
    /// </summary>
    internal static class AimpMlRuntime
    {
        public static IList<string> ReadFieldNames(IntPtr fields)
        {
            var names = new List<string>();

            if (fields == IntPtr.Zero)
            {
                return names;
            }

            using (var list = new AimpObjectList(AimpComHelper.AddRef(fields)))
            {
                for (var i = 0; i < list.Count; i++)
                {
                    names.Add(list.GetString(i));
                }
            }

            return names;
        }

        public static IntPtr ToNativeValue(object value)
        {
            if (value is string text)
            {
                return AimpString.CreateNative(text);
            }

            if (value is IAimpNativeObject native)
            {
                return native.NativePointer;
            }

            return IntPtr.Zero;
        }

        public static IntPtr CreateFieldList(IList fields)
        {
            var list = AimpObjectList.Create();

            if (fields != null)
            {
                foreach (var item in fields)
                {
                    if (item is IAimpDataField field)
                    {
                        list.AddUnknown(CreateFieldObject(field));
                    }
                    else if (item is string name)
                    {
                        list.Add(name);
                    }
                }
            }

            var pointer = AimpComHelper.AddRef(list.Pointer);
            list.Dispose();
            return pointer;
        }

        private static IAIMPMLDataFieldNative CreateFieldObject(IAimpDataField field)
        {
            var native = AimpRuntime.RequireCore().CreateObject<IAIMPMLDataFieldNative>(AimpIids.IAIMPMLDataField);
            var properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)native);

            properties.SetString(AimpMlPropId.FieldName, field.Name);
            properties.SetInt32(AimpMlPropId.FieldType, (int)field.Type);
            properties.SetInt32(AimpMlPropId.FieldFlags, (int)field.Flags);

            if (field.Image != ImageType.Folder)
            {
                properties.SetInt32(AimpMlPropId.FieldImage, (int)field.Image);
            }

            return native;
        }
    }
}