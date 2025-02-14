//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#pragma warning(disable : 4996)

using namespace AIMP::SDK;
using namespace AIMP::SDK::Objects;

typedef AimpActionResult^ ActionResult;
typedef AimpActionResult<System::String^>^ StringResult;
typedef AimpActionResult<float>^ FloatResult;
typedef AimpActionResult<int>^ IntResult;
typedef AimpActionResult<long long>^ LongResult;
typedef AimpActionResult<System::Int64>^ Int64Result;
typedef AimpActionResult<IAimpStream^>^ StreamResult;
typedef AimpActionResult<double>^ DoubleResult;
typedef AimpActionResult<FileManager::Objects::IAimpFileInfo^>^ FileInfoResult;
typedef AimpActionResult<FileManager::Objects::IAimpVirtualFile^>^ VirtualFileResult;
typedef AimpActionResult<FileManager::Commands::IAimpFileSystemCommand^>^ FileSystemCommandResult;
typedef AimpActionResult<Playlist::Objects::IAimpPlaylist^>^ PlaylistResult;
typedef AimpActionResult<MenuManager::Objects::IAimpMenuItem^>^ MenuItemResult;

#define ACTION_RESULT(resultType) gcnew AimpActionResult(resultType);
#define INT_RESULT(result, resultInt) gcnew AimpActionResult<int>(result, resultInt);
#define STRING_RESULT(result, object) gcnew AimpActionResult<String^>(result, object);
#define DOUBLE_RESULT(result, value) gcnew AimpActionResult<double>(result, value);
#define ARGUMENT_NULL(name, message) throw gcnew System::ArgumentNullException(name, message);
#define ACTION_ERROR2(result, message) throw gcnew AimpActionException(result, message);
#define ACTION_ERROR(result) throw gcnew AimpActionException(result);
#define NULL_REFERENCE() throw gcnew System::NullReferenceException();
#define TYPED_RESULT(type) AimpActionResult<type^>^
#define TYPED_RESULT_2(type1, type2) AimpActionResult<type1^, type2^>^
#define RETURN_TYPED_RESULT(type, value1, value2) gcnew AimpActionResult<type^>(value1, value2)

#define GET_IUNKNOWN(type1, object) static_cast<type1^>(object)->InternalAimpObject

#define RELEASE(obj) if (obj != nullptr) { obj->Release(); obj = nullptr; }

#include <windows.h>
#include "AimpSdk.h"
#include "vcclr.h"
#include "AimpLogger.h"