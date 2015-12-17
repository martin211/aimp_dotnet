// This is the main DLL file.

#include "stdafx.h"
#include "DotNetPlugin.h"


System::Reflection::Assembly ^ OnAssemblyResolve(System::Object ^sender, System::ResolveEventArgs ^args);
BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin **Header)
{
    System::AppDomain::CurrentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&OnAssemblyResolve);

	*Header = new DotNetPlugin();
	return true;
}
System::Reflection::Assembly ^ OnAssemblyResolve(System::Object ^sender, System::ResolveEventArgs ^args)
{
    System::String ^path = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
    System::String ^dllFileName = (gcnew System::Reflection::AssemblyName(args->Name))->Name + ".dll";
    System::Collections::Generic::List<System::String^> assembly = System::IO::Directory::EnumerateFiles(path, dllFileName, System::IO::SearchOption::TopDirectoryOnly);
    return System::Reflection::Assembly::LoadFrom(assembly[0]);
}
