#pragma once

#include <mta/misc/SString.hpp>
#include <mta/misc/SharedUtil.DynamicArray.h>

#include <mta/api/IAccount.hpp>

using SharedUtil::DynamicArray;

struct IAccountManager
{
    virtual IAccount* Get(const char* szName, const char* szPassword = nullptr, bool caseSensitive = true) const noexcept = 0;

    virtual DynamicArray<IAccount*>                  GetAllAccounts() const noexcept = 0;
    virtual DynamicArray<IAccount*>                  GetAccountsBySerial(const SString& strSerial) const noexcept = 0;
    virtual DynamicArray<IAccount*>                  GetAccountsByIP(const SString& strIP) const noexcept = 0;
    virtual IAccount* GetAccountByID(const int ID) const noexcept = 0;
    virtual DynamicArray<IAccount*>                  GetAccountsByData(const SString& dataName, const SString& value) const noexcept = 0;
};
