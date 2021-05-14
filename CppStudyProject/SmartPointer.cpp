#include <iostream>
#include <memory>

#include <vector>

#include "SmartPointer.h"

SmartPointerPractice::SmartPointerPractice() {

}
SmartPointerPractice::~SmartPointerPractice() {

}

void SmartPointerPractice::OnAccept(UINT portNum) {
	int i = portNum + 5;

	auto temp = std::shared_ptr<int>(new int(portNum), 
		[i](int* pi) {
			std::cout << "i: " << i << "\n*pi: " << *pi << "\n"; 
			delete pi; 
		}
	);

	this->m_SocketList.push_back(temp);
}
void SmartPointerPractice::ShowList() {
	for (auto it = std::begin(this->m_SocketList); it != std::end(this->m_SocketList); it++) {
		std::cout << *it << " : " << it->use_count() << std::endl;
	}
	std::cout << std::endl;
}

void SmartPointerPractice::Test() {
	std::cout << 1 << std::endl;

	ShowList();

	std::cout << 2 << std::endl;

	OnAccept(10);

	ShowList();

	std::cout << 3 << std::endl;

	OnAccept(15);

	ShowList();
}