#include "pVoidTester.h"

void pVoidTester::Test() {
	EventList eventType = EventList::A;
	Info_EventA eventDataA{ 10 };
	this->EventControl(eventType, &eventDataA);

	eventType = EventList::B;
	Info_EventB eventDataB{ "Hello?" };
	this->EventControl(eventType, &eventDataB);

	eventType = EventList::C;
	Info_EventC eventDataC{ 20, "Bye!" };
	this->EventControl(eventType, &eventDataC);

	eventType = EventList::D;
	Info_EventD eventDataD{ 20, 3.0 };
	this->EventControl(eventType, &eventDataD);

	//	Error �� �߻����� �ʴ� �� ������ ���� ����
	// 	   void* ���� �����͸� ó���ؾ��ϴ� ���, ���� ������ ���ؾ��մϴ�.
	// 
	// Intended Error
	//eventType = EventList::D;
	//this->EventControl(eventType, &eventDataB);
}

void pVoidTester::EventControl(EventList eType, void* eData) {
	switch (eType) {
	case EventList::A:
	{
		Info_EventA info = *static_cast<Info_EventA*>(eData);
		printf("Type A\n");
		printf("%d\n", info.id);

		break;
	}
	case EventList::B:
	{
		Info_EventB info = *static_cast<Info_EventB*>(eData);
		printf("Type B\n");
		std::cout << info.msg << std::endl;

		break;
	}
	case EventList::C:
	{
		Info_EventC info = *static_cast<Info_EventC*>(eData);
		printf("Type C\n");
		printf("%d ", info.id);
		std::cout << info.msg << std::endl;

		break;
	}
	case EventList::D:
	{		
		auto info = *static_cast<Info_EventD*>(eData);
		
		printf("Type D\n");
		printf("%d %lf\n", info.id, info.num);

		break;
	}
	default:
	{
		printf("Default");
	}

	}

}