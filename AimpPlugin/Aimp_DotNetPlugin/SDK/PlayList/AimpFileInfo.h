#pragma once
#include "..\ObjectHelper.h"
#include "..\AimpObject.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System;

		public ref class AimpFileInfo : public AimpObject<IAIMPFileInfo>, public IAimpFileInfo
		{
		public:
			AimpFileInfo()
			{
				IAIMPFileInfo *fileInfo;
				(IAIMPFileInfo*)ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPFileInfo, (void**)&fileInfo);
				_aimpObject = fileInfo;
			}

			AimpFileInfo(IAIMPFileInfo *aimpItem) : AimpObject(aimpItem)
			{}

			virtual property String^ CustomData
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_CUSTOM);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_CUSTOM, value);
				}
			}

			virtual property System::Drawing::Bitmap^ AlbumArt
			{
				System::Drawing::Bitmap^ get()
				{
					System::Drawing::Bitmap^ bmp = nullptr;

					IAIMPImageContainer *container;
					ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImageContainer, (void**) &container);
					_aimpObject->GetValueAsObject(AIMP_FILEINFO_PROPID_ALBUMART, IID_IAIMPImageContainer, (void**) &container);

					if (container != NULL)
					{
						bmp = ObjectHelper::GetBitmap(container);
						container->Release();
					}
					else
					{
						IAIMPImage *image;
						ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImage, (void**) &image);
						_aimpObject->GetValueAsObject(AIMP_FILEINFO_PROPID_ALBUMART, IID_IAIMPImage, (void**) &image);
						if (image != NULL)
						{
							bmp = ObjectHelper::GetBitmap(image);
							image->Release();
						}
					}
					
					return bmp;
				}
			}

			virtual property String^ Album
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUM);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUM, value);
				}
			}

			virtual property String^ AlbumArtist
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMARTIST);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMARTIST, value);
				}
			}

			virtual property String^ Artist
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_ARTIST);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_ARTIST, value);
				}
			}

			virtual property String^ Codec
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_CODEC);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_CODEC, value);
				}
			}

			virtual property String^ Comment
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_COMMENT);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_COMMENT, value);
				}
			}

			virtual property String^ Composer
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_COMPOSER);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_COMPOSER, value);
				}
			}

			virtual property String^ CopyRight
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_COPYRIGHT);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_COPYRIGHT, value);
				}
			}

			virtual property String^ CUESheet
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_CUESHEET);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_CUESHEET, value);
				}
			}

			virtual property String^ Date
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_DATE);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_DATE, value);
				}
			}

			virtual property String^ DiskNumber
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKNUMBER);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKNUMBER, value);
				}
			}

			virtual property String^ DiskTotal
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKTOTAL);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_DISKTOTAL, value);
				}
			}

			virtual property String^ FileName
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_FILENAME);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_FILENAME, value);
				}
			}

			virtual property String^ Genre
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_GENRE);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_GENRE, value);
				}
			}

			virtual property String^ Lyrics
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_LYRICS);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_LYRICS, value);
				}
			}

			virtual property String^ Publisher
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_PUBLISHER);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_PUBLISHER, value);
				}
			}

			virtual property String^ Title
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_TITLE);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_TITLE, value);
				}
			}

			virtual property String^ TrackTotal
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKTOTAL);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKTOTAL, value);
				}
			}

			virtual property String^ URL
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_URL);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_URL, value);
				}					
			}

			virtual property double Mark
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_MARK);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_MARK, value);
				}
			}

			virtual property double AddedDate
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_ADDINGDATE);
				}
			}

			virtual property double LastPlayedDate
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_LASTPLAYDATE);
				}
			}

			virtual property double StateRating
			{
				double get()
				{					
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_RATING);					
				}
			}

			virtual property double StatMark
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_MARK);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_STAT_MARK, value);
				}
			}

			virtual property double TrackGain
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKGAIN);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKGAIN, value);
				}
			}

			virtual property String^ TrackNumber
			{
				String^ get()
				{
					return ObjectHelper::GetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKNUMBER);
				}
				void set(String^ value)
				{
					ObjectHelper::SetString(_aimpObject, AIMP_FILEINFO_PROPID_TRACKNUMBER, value);
				}
			}

			virtual property double TrackPeak
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKPEAK);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_TRACKPEAK, value);
				}
			}

			virtual property double Gain
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMGAIN);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMGAIN, value);
				}
			}

			virtual property double Peak
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMPEAK);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_ALBUMPEAK, value);
				}
			}

			virtual property double Duration
			{
				double get()
				{
					return ObjectHelper::GetFloat(_aimpObject, AIMP_FILEINFO_PROPID_DURATION);
				}
				void set(double value)
				{
					ObjectHelper::SetFloat(_aimpObject, AIMP_FILEINFO_PROPID_DURATION, value);
				}
			}

			virtual property int BitRate
			{
				int get()
				{
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_BITRATE);
				}
				void set(int value)
				{
					ObjectHelper::SetInt32(_aimpObject, AIMP_FILEINFO_PROPID_BITRATE, value);
				}
			}

			virtual property int BitDepth
			{
				int get()
				{   
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_BITDEPTH);
				}
				void set(int value)
				{
					ObjectHelper::SetInt32(_aimpObject, AIMP_FILEINFO_PROPID_BITDEPTH, value);
				}
			}

			virtual property int BPM
			{
				int get()
				{
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_BPM);
				}
				void set(int value)
				{
					ObjectHelper::SetInt32(_aimpObject, AIMP_FILEINFO_PROPID_BPM, value);
				}
			}

			virtual property int Channels
			{
				int get()
				{
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_CHANNELS);
				}
				void set(int value)
				{
					ObjectHelper::SetInt32(_aimpObject, AIMP_FILEINFO_PROPID_CHANNELS, value);
				}
			}

			virtual property int SampleRate
			{
				int get()
				{
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_SAMPLERATE);
				}
				void set(int value)
				{
					ObjectHelper::SetInt32(_aimpObject, AIMP_FILEINFO_PROPID_SAMPLERATE, value);
				}
			}

			virtual property int PlayCount
			{
				int get()
				{
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_STAT_PLAYCOUNT);
				}
			}

			virtual property Int64 FileSize
			{
				Int64 get()
				{
					
					return ObjectHelper::GetInt32(_aimpObject, AIMP_FILEINFO_PROPID_FILESIZE);
				}
				void set(Int64 value)
				{
					ObjectHelper::SetInt64(_aimpObject, AIMP_FILEINFO_PROPID_FILESIZE, value);
				}
			}

			virtual void Assign(IAimpFileInfo^ source)
			{
				_aimpObject->Assign(((AimpFileInfo^) source)->InternalAimpObject);
			}

			virtual IAimpFileInfo^ Clone()
			{
				IAIMPFileInfo* clone;
				ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPFileInfo, (void**)&clone);
				_aimpObject->Clone(&clone);
				return gcnew AimpFileInfo(clone);
			}
		};
	}
}