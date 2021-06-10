#include "pch.h"
#include "NNTPlib.h"

namespace nntp {
	thread::thread()
		: onWork(false), status(OwnerStatus::Stopped)
	{}
	thread::~thread() {}

	bool thread::Start() {
		if (status != OwnerStatus::Stopped) {
			return false;
		}

		onWork = true;
		std::thread(WorkFlow, this).detach();

		while (status != OwnerStatus::Started);

		return true;
	}
	bool thread::Stop() {
		if (status == OwnerStatus::Stopped) {
			return false;
		}

		onWork = false;
		notice.notify_all();

		while (status != OwnerStatus::Stopped) {
			Sleep(10);
		};

		return true;
	}

	bool thread::WorkFlow(void* owner) {
		std::mutex isThereAnyWork;
		std::unique_lock<std::mutex> waitLock(isThereAnyWork);

		thread* myOwner = (thread*)owner;
		myOwner->status = OwnerStatus::Started;

		while (myOwner->onWork) {
			if (myOwner->jobCnt) {
				if (myOwner->Job()) {
					myOwner->jobCntMutex.lock();
					myOwner->jobCnt--;
					myOwner->jobCntMutex.unlock();
				}
				else {

				}
			}
			else {
				myOwner->notice.wait(waitLock);
			}
		}

		if (myOwner->jobCnt) {
			while (myOwner->jobCnt) {
				if (myOwner->Job()) {
					myOwner->jobCntMutex.lock();
					myOwner->jobCnt--;
					myOwner->jobCntMutex.unlock();
				}
				else {

				}
			}
		}
		myOwner->status = OwnerStatus::Stopped;

		return true;
	}
	bool thread::Job() {
		return true;
	}
	bool thread::YouHaveWork() {
		jobCntMutex.lock();
		jobCnt++;
		jobCntMutex.unlock();

		notice.notify_one();
		return true;
	}
}