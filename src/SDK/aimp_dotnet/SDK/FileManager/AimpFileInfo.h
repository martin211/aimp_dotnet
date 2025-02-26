//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK\AimpObject.h"
#include "SDK\ManagedAimpCore.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace FileManager;

        public ref class AimpFileInfo : public AimpObject<IAIMPFileInfo>, public IAimpFileInfo {
        public:
            AimpFileInfo();

            AimpFileInfo(IAimpFileInfo^ item);

            AimpFileInfo(IAIMPFileInfo* aimpItem);

            virtual property String^ CustomData
            {
                String^ get();
                void set(String^ value);
            }

            virtual property System::Drawing::Bitmap^ AlbumArt
            {
                System::Drawing::Bitmap^ get();
                void set(System::Drawing::Bitmap^ value);
            }

            virtual property String^ Album
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ AlbumArtist
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Artist
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Codec
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Comment
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Composer
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ CopyRight
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ CUESheet
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Date
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ DiskNumber
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ DiskTotal
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ FileName
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Genre
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Lyrics
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Publisher
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Title
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ TrackTotal
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ URL
            {
                String^ get();
                void set(String^ value);
            }

            virtual property double AddedDate
            {
                double get();
            }

            virtual property double LastPlayedDate
            {
                double get();
            }

            virtual property double TrackGain
            {
                double get();
                void set(double value);
            }

            virtual property String^ TrackNumber
            {
                String^ get();
                void set(String^ value);
            }

            virtual property double TrackPeak
            {
                double get();
                void set(double value);
            }

            virtual property double AlbumGain
            {
                double get();
                void set(double value);
            }

            virtual property double AlbumPeak
            {
                double get();
                void set(double value);
            }

            virtual property double Duration
            {
                double get();
                void set(double value);
            }

            virtual property int BitRate
            {
                int get();
                void set(int value);
            }

            virtual property int BitDepth
            {
                int get();
                void set(int value);
            }

            virtual property int BPM
            {
                int get();
                void set(int value);
            }

            virtual property int Channels
            {
                int get();
                void set(int value);
            }

            virtual property int SampleRate
            {
                int get();
                void set(int value);
            }

            virtual property int PlayCount
            {
                int get();
            }

            virtual property String^ Conductor {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Mood {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Catalog {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Isrc {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Lyricist {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ EncodedBy {
                String^ get();
                void set(String^ value);
            }

            virtual property Int64 FileSize
            {
                Int64 get();
                void set(Int64 value);
            }

            virtual property double StatDisplayingMark {
                double get();
                void set(double value);
            }

            virtual void Assign(IAimpFileInfo^ source);

            virtual IAimpFileInfo^ Clone();

            virtual property double StatMark {
                double get();
                void set(double value);
            }

            virtual property int StatPlayCount {
                int get();
            }

            virtual property DateTime StatAddingDate {
                DateTime get();
            }

            virtual property DateTime StatLastPlayDate {
                DateTime get();
            }

            virtual property int Rating {
                int get();
                void set(int value);
            }

            virtual property double StatRating
            {
                double get();
            }

            virtual property String^ Key {
                String^ get();
                void set(String^ value);
            }

        protected:
            void RegisterAtMemoryManager() override {
                
            }
            void ReleaseFromMemoryManager() override {
                
            }
        };
    }
}
