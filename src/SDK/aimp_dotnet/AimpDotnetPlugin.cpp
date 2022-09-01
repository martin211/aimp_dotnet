//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "DotNetPlugin.h"


Reflection::Assembly^ OnAssemblyResolve(Object^ sender, ResolveEventArgs^ args);

BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin** Header)
{
    AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&OnAssemblyResolve);

    *Header = new DotNetPlugin();
    return true;
}

Reflection::Assembly^ OnAssemblyResolve(Object^ sender, ResolveEventArgs^ args)
{
    String^ path = Path::GetDirectoryName(Reflection::Assembly::GetExecutingAssembly()->Location);
    String^ dllFileName = (gcnew Reflection::AssemblyName(args->Name))->Name + ".dll";
    List<String^> assembly = Directory::EnumerateFiles(path, dllFileName, SearchOption::TopDirectoryOnly);

    if (assembly.Count == 0)
    {
        return nullptr;
    }

    return System::Reflection::Assembly::LoadFrom(assembly[0]);
}
