#pragma once

#pragma once
#include <thread>
#include <condition_variable>

namespace nntp {
	enum class OwnerStatus {
		Started,
		Stopped,
	};
	enum class WorkerStatus {
		Working,
		Waiting,
	};

	class thread {
	protected:
		thread();
		virtual ~thread();

	protected:
		static bool WorkFlow(void*);
		virtual bool Job();
		bool YouHaveWork();

	public:
		bool Start();
		bool Stop();

	protected:
		std::condition_variable notice;
		bool onWork;
		OwnerStatus status;

		std::mutex jobCntMutex;
		int jobCnt = 0;

	public:
	};
}