#pragma once

#include "ManagedAimpCore.h"
#include "InternalLogger.h"


namespace AIMP
{
	namespace SDK
	{
		using namespace System;
		using namespace AIMPSDK;
		using namespace AIMP::SDK::UI::MenuItem;

		/// <summary>
		/// 
		/// </summary>
		public ref class ObjectHelper abstract sealed
		{
		internal:
			template<typename TObject>
			static TObject* MakeObject(REFIID objectId)
			{
				TObject *obj = NULL;
				if (!CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(objectId, (void**)&obj)))
				{
					InternalLogger::Instance->Write("Unable create AIMP object with id: ");
				}

				return obj;
			}

			/// <summary>
			/// Makes the aimp string.
			/// </summary>
			/// <param name="aimpCore">The aimp core.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static IAIMPString *MakeAimpString(IAIMPCore *aimpCore, String ^value)
			{
				IAIMPString *strObject = NULL;
				pin_ptr<const WCHAR> strDate = PtrToStringChars(value);
				if (!CheckResult(aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject)))
				{
					InternalLogger::Instance->Write("Unable create IAIMPString object");
					return NULL;
				}
				strObject->SetData((PWCHAR)strDate, value->Length);
				return strObject;
			}

			static IAIMPMenuItem *CreateMenuItem(IAIMPCore *core)
			{
				IAIMPMenuItem *item;
				if (!CheckResult(core->CreateObject(IID_IAIMPMenuItem, (void**)&item)))
				{
					InternalLogger::Instance->Write("Unable create IAIMPMenuItem object");
					return NULL;
				}
				return item;
			}

			static IAIMPAction *CreateActionItem(IAIMPCore *core)
			{
				IAIMPAction *newAction;
				if (!CheckResult(core->CreateObject(IID_IAIMPMenuItem, (void**)&newAction)))
				{
					InternalLogger::Instance->Write("Unable create IAIMPAction object");
					return NULL;
				}
				return newAction;
			}

			static IAIMPAction *CreateActionItem(IAIMPCore *core, AIMP::SDK::UI::ActionItem::AimpActionItem ^actionItem)
			{
				IAIMPAction *action = ObjectHelper::CreateActionItem(core);
				action->SetValueAsObject(AIMP_ACTION_PROPID_ID, ObjectHelper::MakeAimpString(core, actionItem->Id));
				action->SetValueAsObject(AIMP_ACTION_PROPID_NAME, ObjectHelper::MakeAimpString(core, actionItem->Text));
				if (!String::IsNullOrWhiteSpace(actionItem->GroupName))
				{
					action->SetValueAsObject(AIMP_ACTION_PROPID_GROUPNAME, ObjectHelper::MakeAimpString(core, actionItem->GroupName));
				}
				action->SetValueAsInt32(AIMP_ACTION_PROPID_ENABLED, actionItem->Enabled ? 1 : 0);

				return action;
			}

			/// <summary>
			/// Sets the string.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static bool SetString(IAIMPPropertyList *propertyList, int propertyId, String ^value)
			{
				return SetObject(propertyList, propertyId, MakeAimpString(ManagedAimpCore::GetAimpCore(), value));
			}

			/// <summary>
			/// Sets the object.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static bool SetObject(IAIMPPropertyList *propertyList, int propertyId, IUnknown *value)
			{
				if (!CheckResult(propertyList->SetValueAsObject(propertyId, value)))
				{
					InternalLogger::Instance->Write("Unable set object with id " + propertyId);
					return false;
				}

				return true;
			}

			/// <summary>
			/// Sets the int32.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static bool SetInt32(IAIMPPropertyList *propertyList, int propertyId, int value)
			{
				if (CheckResult(propertyList->SetValueAsInt32(propertyId, value)))
				{
					InternalLogger::Instance->Write("Unable set Int32 with id " + propertyId);
					return false;
				}

				return true;
			}

			/// <summary>
			/// Sets the int64.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static bool SetInt64(IAIMPPropertyList *propertyList, int propertyId, Int64 value)
			{
				if (CheckResult(propertyList->SetValueAsInt64(propertyId, value)))
				{
					InternalLogger::Instance->Write("Unable set Int64 with id " + propertyId);
					return false;
				}

				return true;
			}

			/// <summary>
			/// Sets the float.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static bool SetFloat(IAIMPPropertyList *propertyList, int propertyId, double value)
			{
				if (CheckResult(propertyList->SetValueAsFloat(propertyId, value)))
				{
					InternalLogger::Instance->Write("Unable set Float with id " + propertyId);
					return false;
				}

				return true;
			}

			/// <summary>
			/// Sets the bool.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="value">if set to <c>true</c> [value].</param>
			/// <returns></returns>
			static bool SetBool(IAIMPPropertyList *propertyList, int propertyId, bool value)
			{
				return SetInt32(propertyList, propertyId, value ? 1 : 0);
			}

			/// <summary>
			/// Gets the string.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>		
			[System::Runtime::ExceptionServices::HandleProcessCorruptedStateExceptions]
			static String^ GetString(IAIMPPropertyList *propertyList, int propertyId)
			{
				IAIMPString* str = nullptr;

				try
				{
					if (!CheckResult(propertyList->GetValueAsObject(propertyId, IID_IAIMPString, (void**)&str)))
					{
						InternalLogger::Instance->Write("Unable get String with id " + propertyId);
						return nullptr;
					}
					if (str != NULL)
					{
						return GetString(str);
					}
				}
				catch (System::Exception ^ex)
				{
					System::Diagnostics::Debugger::Break();
					InternalLogger::Instance->Write(ex);
					return nullptr;
				}
				finally
				{
					if (str != NULL)
					{
						str->Release();
						str = NULL;
					}
				}

				return nullptr;
			}

			static String^ GetString(IAIMPString *aimpString)
			{
				return gcnew String(aimpString->GetData());
			}

			/// <summary>
			/// Gets the object.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <param name="objectId">The object identifier.</param>
			/// <param name="value">The value.</param>
			/// <returns></returns>
			static bool GetObject(IAIMPPropertyList *propertyList, int propertyId, REFIID objectId, void **value)
			{
				if (!CheckResult(propertyList->GetValueAsObject(propertyId, objectId, (void**)&value)))
				{
					InternalLogger::Instance->Write("Unable get object with id " + propertyId);
					return false;
				}

				return true;
			}

			/// <summary>
			/// Gets the int32.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <returns></returns>
			static int GetInt32(IAIMPPropertyList *propertyList, int propertyId)
			{
				int val;
				if (!CheckResult(propertyList->GetValueAsInt32(propertyId, &val)))
				{
					InternalLogger::Instance->Write("Unable get Int32 with id " + propertyId);
					return 0;
				}

				return val;
			}

			/// <summary>
			/// Gets the int64.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <returns></returns>
			static Int64 GetInt64(IAIMPPropertyList *propertyList, int propertyId)
			{
				Int64 val;
				if (!CheckResult(propertyList->GetValueAsInt64(propertyId, &val)))
				{
					InternalLogger::Instance->Write("Unable get Int64 with id " + propertyId);
					return 0;
				}

				return val;
			}

			/// <summary>
			/// Gets the float.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <returns></returns>
			static double GetFloat(IAIMPPropertyList *propertyList, int propertyId)
			{
				double val;
				if (!CheckResult(propertyList->GetValueAsFloat(propertyId, &val)))
				{
					InternalLogger::Instance->Write("Unable get Float with id " + propertyId);
					return false;
				}

				return val;
			}

			/// <summary>
			/// Gets the bool.
			/// </summary>
			/// <param name="propertyList">The property list.</param>
			/// <param name="propertyId">The property identifier.</param>
			/// <returns></returns>
			static bool GetBool(IAIMPPropertyList *propertyList, int propertyId)
			{
				return GetInt32(propertyList, propertyId) > 0;
			}

			static MenuItem ^ConvertToMenu(IAIMPPropertyList *aimpMenuItem)
			{
				MenuItem^ result = nullptr;

				int menuType;
				if (CheckResult(aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, &menuType)))
				{
					int checked;
					aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_CHECKED, &checked);

					IAIMPString* idString;
					IAIMPString* nameString;

					CheckResult(aimpMenuItem->GetValueAsObject(AIMP_MENUITEM_PROPID_NAME, IID_IAIMPString, (void**)&nameString));

					if (menuType == AIMP_MENUITEM_STYLE_CHECKBOX)
					{
						result = gcnew CheckBoxMenuItem(gcnew String(nameString->GetData()));
						((CheckBoxMenuItem^)result)->Checked = checked > 0;
					}
					else if (menuType == AIMP_MENUITEM_STYLE_RADIOBOX)
					{
						result = gcnew RadioButtonMenuItem(gcnew String(nameString->GetData()));
						((RadioButtonMenuItem^)result)->Checked = checked > 0;
					}
					else if (menuType == AIMP_MENUITEM_STYLE_NORMAL)
					{
						result = gcnew StandartMenuItem(gcnew String(nameString->GetData()));
					}

					if (CheckResult(aimpMenuItem->GetValueAsObject(AIMP_MENUITEM_PROPID_ID, IID_IAIMPString, (void**)&idString)))
					{
						if (idString != NULL)
						{
							result->Id = gcnew String(idString->GetData());
						}
					}

					int visible;
					aimpMenuItem->GetValueAsInt32(AIMP_MENUITEM_PROPID_VISIBLE, &visible);
					result->Visible = visible > 0;
				}

				return result;
			}

			static System::Drawing::Bitmap^ GetBitmap(IAIMPImageContainer* imageContainer)
			{
				IAIMPImage* image;
				if (!CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImage, (void**)&image)))
				{
					InternalLogger::Instance->Write("Unable get Bitmap");
					return nullptr;
				}

				imageContainer->CreateImage(&image);
				return GetBitmap(image);
			}

			static System::Drawing::Bitmap^ GetBitmap(IAIMPImage* image)
			{
				SIZE size;
				if (CheckResult(image->GetSize(&size)))
				{
					image->SaveToFile(AIMP::ObjectHelper::MakeAimpString(AIMP::SDK::ManagedAimpCore::GetAimpCore(), "d:\\temp.png"), AIMP_IMAGE_FORMAT_PNG);

					if (size.cx == 0 || size.cy == 0)
					{
						return nullptr;
					}

					System::Drawing::Bitmap^ bmp = gcnew System::Drawing::Bitmap(size.cx, size.cy);

					IAIMPStream *stream;
					AIMP::SDK::ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPMemoryStream, (void**)&stream);
					image->SaveToStream(stream, AIMP_IMAGE_FORMAT_PNG);
					if (stream->GetSize() > 0)
					{
						Int64 size = stream->GetSize();
						unsigned char *buf = new unsigned char[size];
						HRESULT r = stream->Seek(0, AIMP_STREAM_SEEKMODE_FROM_BEGINNING);
						r = stream->Read(buf, size);

						System::IO::MemoryStream^ strm = gcnew System::IO::MemoryStream();
						try
						{
							for (int i = 0; i < size; i++)
							{
								strm->WriteByte(buf[i]);
							}
							bmp = gcnew System::Drawing::Bitmap(strm);
						}
						finally
						{
							strm->Close();
							strm = nullptr;

							delete[] buf;
							stream->Release();
							image->Release();
						}
					}

					return bmp;
				}

				return nullptr;
			}

			static IAIMPImage *CreateImage(System::Drawing::Bitmap ^image)
			{
				System::IO::MemoryStream ^stream;
				try
				{
					stream = gcnew System::IO::MemoryStream();
					image->Save(stream, System::Drawing::Imaging::ImageFormat::Png);
					array<Byte> ^buffer = gcnew array<byte>(stream->Length);
					buffer = stream->ToArray();

					IAIMPStream *aimpStream = NULL;
					IAIMPImage *img;
					if (CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPMemoryStream, (void**)&aimpStream))
						&& CheckResult(ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPImage, (void**)&img)))
					{
						aimpStream->SetSize(stream->Length);
						pin_ptr<System::Byte> p = &buffer[0];
						unsigned char* pby = p;
						if (CheckResult(aimpStream->Write(pby, stream->Length, nullptr)))
						{
							img->LoadFromStream(aimpStream);
						}

						return img;
					}
				}
				finally
				{
					if (stream != nullptr)
					{
						stream->Close();
					}
				}

				return NULL;
			}

			/// <summary>
			/// Checks the result.
			/// </summary>
			/// <param name="result">The result.</param>
			/// <returns></returns>		
			static bool CheckResult(HRESULT result)
			{
				if (result != S_OK)
				{
					//System::Diagnostics::Debugger::Break();
					InternalLogger::Instance->Write(String::Format(L"Invalid operation: result {0}", result));
				}

				return result == S_OK;
			}
		};
	}
}