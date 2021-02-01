#ifndef SINGLETON_H
#define SINGLETON_H
#include <Windows.h>

#define NOCOPYABLE(x) \
    private: \
          x(const x&)=delete;\
          x& operator=(const x&)=delete;

template<class T>
class Singleton
{
	NOCOPYABLE(Singleton);
public:
	static BOOL CALLBACK Init(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *lpContext)
	{
		static T instance;
		m_Instance = &instance;
		return TRUE;
	}

	static T& GetInstance()
	{
		static INIT_ONCE flag;
		PVOID lpContext;
		InitOnceExecuteOnce(&flag, Init, NULL, &lpContext);
		return *m_Instance;
	}
protected:
	Singleton() = default;
	~Singleton() = default;
private:
	static T* m_Instance;
};
template<class T>
T* Singleton<T>::m_Instance;
#endif/*SINGLETON_H*/