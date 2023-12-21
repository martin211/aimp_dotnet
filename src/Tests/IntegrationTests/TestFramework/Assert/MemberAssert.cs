//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace Aimp.TestRunner.TestFramework.Assert;

public abstract class MemberAssert : MemberAssert<object>
{
    protected MemberAssert(string name, object value, string message)
        : base(name, value, message)
    {
        FieldName = name;
        Value = value;
        Message = message;
    }
}

public abstract class MemberAssert<TValue> : IMemberAssert
{
    protected MemberAssert(string name, TValue value, string message)
    {
        FieldName = name ?? "Field";
        Value = value;
        Message = message;
    }

    public string FieldName { get; set; }

    public TValue Value { get; set; }

    public string Message { get; set; }
    public bool IsValid { get; internal set; } = true;

    public abstract void Validate();
    public Action Finally { get; set; }

    protected virtual void Validate(Action validator)
    {
        try
        {
            if (validator != null)
            {
                validator();
                IsValid = true;
            }
        }
        finally
        {
            Finally?.Invoke();
        }
    }
}

public interface IMemberAssert
{
    bool IsValid { get; }

    Action Finally { get; set; }

    void Validate();
}
