#pragma once

class MessageControlModule {

private:
    std::list<CString> messageList;
    std::list<std::string> messageListStr;
public:
    void UpdateMessageList(CString msg);
    void UpdateMessageList(std::string msg);
    void ShowMessageList();
    void ShowMessageListStr();

    void Test();
};