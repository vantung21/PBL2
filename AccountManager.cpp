#include "AccountManager.h"

AccountManager::AccountManager(){
    ifstream infile("savegame/accounts.txt");
    nextUserID = 100000;
    if (infile.is_open()) {
        string username, password;
        int userID;
        while (infile >> username >> password >> userID) {
            accounts.push_back({{username, password}, userID});
            if (userID >= nextUserID) {
                nextUserID = userID + 1; 
            }
        }
    }
}

string AccountManager::hashPassword(const string& password) {}

bool AccountManager::registerAccount(const string& username, const string& password) {
    if(username.empty() || password.empty()) {
        return false; // Khong the dang ky voi tai khoan hoac mat khau rong
    }
    // Kiem tra tai khoan da ton tai?
    for (const auto& account : accounts){
        if (account.first.first == username) {
            return false; // Tai khoan da ton tai
        }
    }

    // Them tai khoan moi
    accounts.push_back({{username, password}, nextUserID++});
    ofstream outfile("savegame/accounts.txt", ios::app);
    if (outfile.is_open()){
        outfile << username << " " << password << " " << (nextUserID - 1) << endl;
        outfile.close();
    }
    return true;
}

int AccountManager::login(const string& username, const string& password) {
    for (const auto& account : accounts) {
        if (account.first.first == username && account.first.second == password) {
            return account.second; // tra ve userID
        }
    }
    return -1; // dang nhap that bai
}