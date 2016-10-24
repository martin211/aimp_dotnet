using System.Collections;
using System.Collections.Generic;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Extension;

namespace AIMP.CustomDataProvider
{
    public class DataStorage
    {
        public const string FieldId = AimpDataField.AIMPML_RESERVED_FIELD_ID;
        public const string FieldFileName = AimpDataField.AIMPML_RESERVED_FIELD_FILENAME;
        public const string FieldTitle = "Title";
        public const string FieldNode = "Node";

        public IList GetFields(SchemaType schemaType)
        {
            switch (schemaType)
            {
                case SchemaType.AIMPML_FIELDS_SCHEMA_ALL:
                    return new List<AimpDataField>
                    {
                        new AimpDataField(FieldId, AimpDataFieldType.AIMPML_FIELDTYPE_STRING, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_INTERNAL),
                        new AimpDataField(FieldFileName, AimpDataFieldType.None, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_INTERNAL),
                        new AimpDataField(FieldTitle, AimpDataFieldType.AIMPML_FIELDTYPE_STRING)
                    };
                    case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS:
                    case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT:
                    case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS:
                    return new List<string>
                    {
                        "Title"
                    };
            }

            return null;
        }
    }
}