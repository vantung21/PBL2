#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "include.h"

class AccountManager {
    private:
        Vector<pair<pair<string, string>, int>> accounts; // ((username, password), userID)
        int nextUserID;
    public:
        AccountManager();
        bool registerAccount(const string& username, const string& password);
        int login(const string& username, const string& password);
        //string hashPassword(const string& password);
        
};

#endif