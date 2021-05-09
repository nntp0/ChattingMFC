#include <iostream>
#include <list>
#include <string>

#include <atlstr.h>
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

int main()
{
    MessageControlModule controlModule;
    
    controlModule.Test();
}

void MessageControlModule::Test() {
    ShowMessageListStr();

    UpdateMessageList(std::string("안녕하세요??"));

    ShowMessageListStr();

    std::string temp("만나서 반갑습니다!!");

    UpdateMessageList(temp);

    ShowMessageListStr();

    std::cout << "=======" << std::endl;

    ShowMessageList();

    UpdateMessageList(CString("안녕하세요??"));

    ShowMessageList();

    CString temp2("만나서 반갑습니다!!");

    UpdateMessageList(temp2);

    ShowMessageList();

}

void MessageControlModule::UpdateMessageList(CString msg) {
    this->messageList.push_back(msg.GetString());
}
void MessageControlModule::UpdateMessageList(std::string msg) {
    this->messageListStr.push_back(msg);
}
void MessageControlModule::ShowMessageList() {

    for (auto it = std::begin(this->messageList); it != std::end(this->messageList); it++) {
        wprintf(_T("%s\n"), it->GetString());
    }
}
void MessageControlModule::ShowMessageListStr() {

    for (auto it = std::begin(this->messageListStr); it != std::end(this->messageListStr); it++) {
        std::cout << *it << std::endl;
    }
}