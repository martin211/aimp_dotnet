// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        ref class ManagedAimpCore;

        public ref class AimpImage :
            public AimpObject<IAIMPImage2>,
            public IAimpImage {
        private:
            ManagedAimpCore^ _core;
        public:
            explicit AimpImage(IAIMPImage2* obj);
            explicit AimpImage(IAIMPImage2* obj, ManagedAimpCore^ core);
            property AimpImageFormat FormatId { virtual AimpImageFormat get(); }
            property Drawing::PointF Size { virtual Drawing::PointF get(); }
            virtual AimpActionResult^ LoadFromFile(String^ fileName);
            virtual AimpActionResult^ LoadFromStream(IAimpStream^ stream);
            virtual AimpActionResult^ SaveToFile(String^ fileName, AimpImageFormat format);
            virtual AimpActionResult^ SaveToStream(IAimpStream^ stream, AimpImageFormat format);
            virtual AimpActionResult<IAimpImage^>^ Clone();
            virtual AimpActionResult^ Draw(IntPtr dc, Drawing::RectangleF rect);
            virtual AimpActionResult^ Resize(int width, int height);

            // IAIMPImage2
            virtual AimpActionResult^ LoadFromResource();
            virtual AimpActionResult^ LoadFromBitmap(IntPtr bitmap);
            virtual AimpActionResult^ LoadFromBits(RGBQuad bits, int width, int height);
            virtual AimpActionResult^ CopyToClipboard();
            virtual AimpActionResult^ CanPasteFromClipboard();
            virtual AimpActionResult^ PasteFromClipboard();
        };
    }
}
