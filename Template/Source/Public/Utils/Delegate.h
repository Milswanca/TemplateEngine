#pragma once
#include <vector>
#include <typeinfo>

template <typename Ret, typename... Params>
class Callback
{
public:
	virtual Ret Invoke(Params... InParams) = 0;
};

template <typename Ret, typename... Params>
class StaticCallback : public Callback<Ret, Params...>
{
public:
	StaticCallback(Ret(*InFunc)(Params...))
		: StaticMethod(InFunc)
	{}

	virtual Ret Invoke(Params... InParams)
	{
		return (*StaticMethod)(InParams...);
	}

	Ret(*StaticMethod)(Params...);
};

template <typename T, typename Method, typename Ret, typename... Params>
class MethodCallback : public Callback<Ret, Params...>
{
public:
	void* m_Object;
	Method m_Method;
public:

	MethodCallback(void *InObject, Method InMethod) : m_Object(InObject), m_Method(InMethod)
	{}

	virtual Ret Invoke(Params... params)
	{
		T* Obj = static_cast<T*>(m_Object);
		return (Obj->*m_Method)(params...);
	}
};

template <typename Ret, typename... Params>
class Delegate
{
public:

	Delegate()
	{

	}

	~Delegate()
	{
		RemoveAll();
	}

	template<typename T, typename Method>
	void Add(T* InObject, Method InMethod)
	{
		MethodCallback<T, Method, Ret, Params...>* NewMethod = new MethodCallback<T, Method, Ret, Params...>(InObject, InMethod);
		m_Callbacks.push_back(NewMethod);
	}

	void Add(Ret(*func)(Params...))
	{
		StaticCallback<Ret, Params...>* NewMethod = new StaticCallback<Ret, Params...>(func);
		m_Callbacks.push_back(NewMethod);
	}

	template<typename T, typename Method>
	void Remove(T* InObject, Method InMethod)
	{
		int FoundIndex = 0;
		MethodCallback<T, Method, Ret, Params...>* Callback = FindBoundMethod(InObject, InMethod, FoundIndex);
		if (Callback)
		{
			m_Callbacks.erase(m_Callbacks.begin() + FoundIndex);
			delete Callback;
		}
	}

	void Remove(void(*InFunc)(Params...))
	{
		int FoundIndex = 0;
		StaticCallback<Ret, Params...>* Callback = FindBoundStaticMethod(InFunc, FoundIndex);
		if (Callback)
		{
			m_Callbacks.erase(m_Callbacks.begin() + FoundIndex);
			delete Callback;
		}
	}

	void RemoveAll()
	{
		for (unsigned int i = 0; i < m_Callbacks.size();)
		{
			Callback<Ret, Params...>* Callback = (*m_Callbacks.begin());
			m_Callbacks.erase(m_Callbacks.begin());
			delete Callback;
		}
	}

	//We need a void type specialization function to handle the invoke if a function is void return
	//This is because the compiler will throw an error because void is not returnable
	template<typename = typename enable_if <!is_void<Ret>::value>::type>
	Ret Invoke(Params... param)
	{
		Ret RetVal = NULL;

		for (Callback<Ret, Params...>* i : m_Callbacks)
		{
			RetVal = i->Invoke(param...);
		}

		return RetVal;
	}

	void Invoke(Params... InParam)
	{
		for (Callback<Ret, Params...>* i : m_Callbacks)
		{
			i->Invoke(InParam...);
		}
	}

	template<typename T, typename Method>
	bool IsAlreadyBound(T* InObject, Method InMethod)
	{
		int FoundIndex = 0;
		return FindBoundMethod(InObject, InMethod, FoundIndex) != nullptr;
	}

	bool IsAlreadyBound(Ret(*InFunc)(Params...))
	{
		int FoundIndex = 0;
		return FindBoundStaticMethod(InFunc, FoundIndex) != nullptr;
	}

	template<typename T, typename Method>
	MethodCallback<T, Method, Ret, Params...>* FindBoundMethod(T* InObject, Method InMethod, int& OutFoundIndex)
	{
		OutFoundIndex = -1;
		for (unsigned int i = 0; i < m_Callbacks.size(); i++)
		{
			MethodCallback<T, Method, Ret, Params...>* Callback = static_cast<MethodCallback<T, Method, Ret, Params...>*>(m_Callbacks[i]);
			if (Callback->m_Object == InObject && Callback->m_Method == InMethod)
			{
				OutFoundIndex = i;
				return Callback;
			}
		}
		return false;
	}

	StaticCallback<Ret, Params...>* FindBoundStaticMethod(Ret(*InFunc)(Params...), int& OutFoundIndex)
	{
		OutFoundIndex = -1;
		for (unsigned int i = 0; i < m_Callbacks.size(); i++)
		{
			StaticCallback<Ret, Params...>* Callback = static_cast<StaticCallback<Ret, Params...>*>(m_Callbacks[i]);
			if (Callback->StaticMethod == InFunc)
			{
				OutFoundIndex = i;
				return Callback;
			}
		}
		return false;
	}

protected:
	std::vector<Callback<Ret, Params...>*> m_Callbacks;
};