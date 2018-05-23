#pragma once
#include <pthread.h>

class mutex;

class condition
{
public:
	condition();
	~condition();

	bool signal();
	bool broadcast();	//�൱��notifyall
	bool wait(mutex& lock);

private:
	pthread_cond_t _cond;
};
