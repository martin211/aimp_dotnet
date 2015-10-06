#pragma once

#include "..\..\ManagedAimpCore.h"
#include "..\BaseManager.h"

namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace AIMP::SDK::Services::AlbumArtManager;
		using namespace System::IO;

		public ref class AimpAlbumArtManager : public AimpBaseManager, public IAimpAlbumArtManager
		{
		public:
			explicit AimpAlbumArtManager(ManagedAimpCore^ core) : AimpBaseManager(core)
			{
				IAIMPServiceAlbumArt* service;
				core->GetService(IID_IAIMPServiceAlbumArt, (void**) &service);
				_service = service;
				IAIMPPropertyList *prop;
				service->QueryInterface(IID_IAIMPPropertyList, (void**) &prop);
				_properties = prop;
			}

			~AimpAlbumArtManager()
			{
				_service->Release();
				_properties->Release();
				delete this->_findCallback;
			}

			event EventHandler<AimpGetAlbumArtEventArgs^>^ Completed
			{
				virtual void add(EventHandler<AimpGetAlbumArtEventArgs^>^ onCompleted)
				{
					if (this->_onComplete == nullptr)
					{
						this->_onComplete = (EventHandler<AimpGetAlbumArtEventArgs^>^)Delegate::Combine(this->_onComplete, onCompleted);
					}
				}
				virtual void remove(EventHandler<AimpGetAlbumArtEventArgs^>^ onCompleted)
				{
					delete _onComplete;
					_onComplete = nullptr;
				}
				void raise(Object^ sender, AimpGetAlbumArtEventArgs^ args)
				{
					if (_onComplete != nullptr)
					{
						_onComplete(sender, args);
					}
				}
			}

			virtual property bool FindInFiles
			{
				bool get()
				{
					int val;
					_properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, &val);
					return val != 0;
				}
				void set(bool value)
				{
					_properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, value);
				}
			}

			virtual property bool FindInInternet
			{
				bool get()
				{
					int val;
					_properties->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, &val);
					return false;
				}
				void set(bool value)
				{
					_properties->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value);
				}
			}

			virtual property array<System::String^>^ FileMasks
			{
				array<System::String^>^ get()
				{
					IAIMPString *str;
					_properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString, (void**) &str);
					String^ result = gcnew String(str->GetData());
					return result->Split(gcnew array < WCHAR > {';'});
				}
				void set(array<System::String^>^ val)
				{
					String^ str;
					for (int i = 0; i < val->Length; i++)
					{
						str += val[i];
					}
					_properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, ObjectHelper::MakeAimpString(_core->GetAimpCore(), str));
				}
			}

			virtual property array<System::String^>^ FileExtensions
			{
				array<System::String^>^ get()
				{
					IAIMPString *str;
					_properties->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString, (void**) &str);
					String^ result = gcnew String(str->GetData());
					return result->Split(gcnew array < WCHAR > {';'});
				}
				void set(array<System::String^>^ val)
				{
					String^ str;
					for (int i = 0; i < val->Length; i++)
					{
						str += val[i];
					}
					_properties->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, ObjectHelper::MakeAimpString(_core->GetAimpCore(), str));
				}
			}

			virtual property int MaxFileSize
			{
				int get()
				{
					return 0;
				}
				void set(int val)
				{
				}
			}

			void OnAlbumArtReceive(IAIMPImage* image, IAIMPImageContainer* image_container, void* user_data)
			{
				AimpGetAlbumArtEventArgs^ args = gcnew AimpGetAlbumArtEventArgs();

				if (image == NULL && image_container == NULL)
				{
					Completed(this, args);
					return;
				}

				if (image_container != NULL && image == NULL)
				{
					args->CoverImage = ObjectHelper::GetBitmap(image_container);
				}
				else if (image != NULL)
				{
					args->CoverImage = ObjectHelper::GetBitmap(image);
				}

				Completed(this, args);
			}

			virtual IntPtr GetImage(String^ fileUrl, String^ artist, String^ album, AimpFingCovertArtType flags, Object^ userData)
			{
				void* taskId;
				_findCallback = gcnew OnFindCoverCallback(this, &AIMP::AimpAlbumArtManager::OnAlbumArtReceive);
				//TAIMPServiceAlbumArtReceiveProc *f = &test;
				IntPtr thunk = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_findCallback);
				_service->Get(ObjectHelper::MakeAimpString(_core->GetAimpCore(), fileUrl), ObjectHelper::MakeAimpString(_core->GetAimpCore(), artist), ObjectHelper::MakeAimpString(_core->GetAimpCore(), album), (DWORD) flags, (TAIMPServiceAlbumArtReceiveProc(_stdcall *))thunk.ToPointer(), reinterpret_cast<void*>(&userData), &taskId);
				return (IntPtr) taskId;
			}

			virtual IntPtr GetImage(AIMP::SDK::Services::PlayList::IAimpFileInfo^ fileInfo, AimpFingCovertArtType flags, Object^ userData)
			{
				void* taskId = nullptr;
				_findCallback = gcnew OnFindCoverCallback(this, &AIMP::AimpAlbumArtManager::OnAlbumArtReceive);
				IntPtr thunk = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_findCallback);

				//_service->Get2(((AIMP::PlayList::AimpFileInfo^) fileInfo)->SourceFileInfo, (DWORD) flags, (AIMP36SDK::TAIMPServiceAlbumArtReceiveProc(_stdcall *))thunk.ToPointer(), reinterpret_cast<void*>(&userData), &taskId);
				return (IntPtr) taskId;
			}

			virtual void Cancel(IntPtr taskId, AimpFingCovertArtType flags)
			{
				if (taskId != IntPtr::Zero)
				{
					_service->Cancel((void*) taskId, (DWORD) flags);
				}
			}
		private:
			delegate void OnFindCoverCallback(IAIMPImage *image, IAIMPImageContainer *imageContainer, void *UserData);
			OnFindCoverCallback^ _findCallback;

			IAIMPServiceAlbumArt* _service;
			IAIMPPropertyList *_properties;
			EventHandler<AimpGetAlbumArtEventArgs^>^ _onComplete;
		};
	}
}