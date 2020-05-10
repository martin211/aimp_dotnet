// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

using namespace AIMP::SDK;

typedef AimpActionResult^ VoidResult;
typedef AimpActionResult<System::String^>^ StringResult;
typedef AimpActionResult<float>^ FloatResult;
typedef AimpActionResult<int>^ IntResult;
typedef AimpActionResult<System::Int64>^ Int64Result;
typedef AimpActionResult<IAimpStream^>^ StreamResult;
typedef AimpActionResult<FileManager::IAimpFileInfo^>^ FileInfoResult;
typedef AimpActionResult<FileManager::IAimpVirtualFile^>^ VirtualFileResult;
typedef AimpActionResult<FileManager::Commands::IAimpFileSystemCommand^>^ FileSystemCommandResult;

#define VOID_RESULT(resultType) gcnew AimpActionResult(resultType);

//-V122_NOPTR

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif  // _DEBUG

#include <windows.h>
#include <exception>
#include "AimpSdk.h"


#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
