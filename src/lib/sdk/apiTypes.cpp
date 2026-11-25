////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3000
//
//  Purpose:   General Types
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#include <apiTypes.h>

#ifdef API_VAR_NEXTGEN

	void* VarValuePtr(VarValue target)
	{
		return (char*)target + sizeof(VarValueStruct);
	}

	void VarValueInitCore(VarValue* target, int type, void* data, int dataSize) 
	{
		VarValue value = (VarValue)malloc(sizeof(VarValueStruct) + dataSize);
		if (value) 
		{
			value->freeproc = &free;
			value->type = type;
			if (dataSize > 0)
				memcpy(VarValuePtr(value), data, dataSize);
		}
		(*target) = value;
	}

#endif

void VarValueFree(VarValue* value)
{
	#ifdef API_VAR_NEXTGEN
		(*value)->freeproc(*value);
		(*value) = nullptr;
	#else
		VariantClear(value);
	#endif
}

void VarValueCopy(VarValue* target, const VarValue& source)
{
	if (VarValueIsInt32(source))
		VarValueInit(target, VarValueToInt32(source));
	else if (VarValueIsInt64(source))
		VarValueInit(target, VarValueToInt64(source));
	else if (VarValueIsString(source))
		VarValueInit(target, VarValueToString(source));
	else
		VarValueInit(target, VarValueToFloat(source));
}

void VarValueInit(VarValue* target, const PChar value)
{
	#ifdef API_VAR_NEXTGEN
		VarValueInitCore(target, vvString, (void*)value, (_clen(value) + 1) * sizeof(TChar));
	#else
		VariantInit(target);
		target->vt = VT_BSTR;
		target->bstrVal = SysAllocString(value);
	#endif // API_VAR_NEXTGEN
}

void VarValueInit(VarValue* target, INT32 value)
{
	#ifdef API_VAR_NEXTGEN
		VarValueInitCore(target, vvInt32, &value, sizeof(INT32));
	#else
		VariantInit(target);
		target->vt = VT_I4;
		target->lVal = value;
	#endif // API_VAR_NEXTGEN
}

void VarValueInit(VarValue* target, INT64 value)
{
	#ifdef API_VAR_NEXTGEN
		VarValueInitCore(target, vvInt64, &value, sizeof(INT64));
	#else
		VariantInit(target);
		target->vt = VT_I8;
		target->llVal = value;
	#endif // API_VAR_NEXTGEN
}

void VarValueInit(VarValue* target, double value)
{
	#ifdef API_VAR_NEXTGEN
		VarValueInitCore(target, vvFloat, &value, sizeof(double));
	#else
		VariantInit(target);
		target->vt = VT_R8;
		target->dblVal = value;
	#endif // API_VAR_NEXTGEN
}

bool VarValueIsFloat(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		return source->type == vvFloat;
	#else
		return source.vt == VT_R8 || source.vt == VT_R4;
	#endif
}

bool VarValueIsInt32(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		return source->type == vvInt32;
	#else
		return
			source.vt == VT_I1 ||
			source.vt == VT_I2 ||
			source.vt == VT_I4 ||
			source.vt == VT_UI1 ||
			source.vt == VT_UI2 ||
			source.vt == VT_UI4;
	#endif
}

bool VarValueIsInt64(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		return source->type == vvInt64;
	#else
		return source.vt == VT_I8 || source.vt == VT_UI8;
	#endif
}

bool VarValueIsString(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		return source->type == vvString;
	#else
		return source.vt == VT_BSTR;
	#endif
}

VarValue VarValueNull()
{
	#ifdef API_VAR_NEXTGEN
		return nullptr;
	#else
		VarValue target;
		VariantInit(&target);
		return target;
	#endif
}

double VarValueToFloat(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		if (VarValueIsFloat(source))
			return *(double*)(VarValuePtr(source));
	#else
		switch (source.vt)
		{
			case VT_R4:
				return source.fltVal;
			case VT_R8:
				return source.dblVal;
		}
	#endif
		if (VarValueIsInt32(source))
			return (double)VarValueToInt32(source);
		if (VarValueIsInt64(source))
			return (double)VarValueToInt64(source);
		if (VarValueIsString(source))
			return _ctof(VarValueToString(source));
		return 0.0;
}

INT32 VarValueToInt32(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		if (VarValueIsInt32(source))
			return *(INT32*)(VarValuePtr(source));
	#else
		switch (source.vt)
		{
			case VT_I1:
			case VT_UI1:
				return source.bVal;
			case VT_I2:
			case VT_UI2:
				return source.iVal;
			case VT_I4:
			case VT_UI4:
				return source.lVal;
		}
	#endif
		if (VarValueIsFloat(source))
			return (INT32)VarValueToFloat(source);
		if (VarValueIsInt64(source))
			return (INT32)VarValueToInt64(source);
		if (VarValueIsString(source))
			return _ctoi(VarValueToString(source));
		return 0;
}

INT64  VarValueToInt64(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		if (VarValueIsInt64(source))
			return *(INT64*)(VarValuePtr(source));
	#else
		switch (source.vt)
		{
			case VT_I8:
			case VT_UI8:
				return source.llVal;
		}
	#endif
		if (VarValueIsFloat(source))
			return (INT64)VarValueToFloat(source);
		if (VarValueIsInt32(source))
			return (INT64)VarValueToInt64(source);
		if (VarValueIsString(source))
			return _ctoll(VarValueToString(source));
		return 0;
}

PChar VarValueToString(const VarValue& source)
{
	#ifdef API_VAR_NEXTGEN
		if (VarValueIsString(source))
			return (PChar)(VarValuePtr(source));
	#else
		if (source.vt == VT_BSTR)
			return source.bstrVal;
	#endif
		return nullptr;
}

bool Failed(HRESULT code)
{
  return (code & 0x80000000) != 0;
}

bool Succeeded(HRESULT code)
{
  return (code & 0x80000000) == 0;
}

bool EqualGUID(REFIID a, REFIID b)
{
  return 
    a.Data1 == b.Data1 &&
    a.Data2 == b.Data2 &&
    a.Data3 == b.Data3 &&
    a.Data4[0] == b.Data4[0] &&
    a.Data4[1] == b.Data4[1] &&
    a.Data4[2] == b.Data4[2] &&
    a.Data4[3] == b.Data4[3] &&
    a.Data4[4] == b.Data4[4] &&
    a.Data4[5] == b.Data4[5] &&
    a.Data4[6] == b.Data4[6] &&
    a.Data4[7] == b.Data4[7];
}
