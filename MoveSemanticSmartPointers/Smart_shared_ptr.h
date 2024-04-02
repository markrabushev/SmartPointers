#pragma once

template <class>
class smart_weak_ptr;

template <class T> 
class smart_shared_ptr
{
public:
	smart_shared_ptr() :m_ptr(nullptr), m_counter(nullptr) {}
	smart_shared_ptr(T* i_ptr) :m_ptr(i_ptr) 
	{
		m_counter = new int(1);
	}
	smart_shared_ptr(const smart_shared_ptr<T>& i_other) 
	{
		m_ptr = i_other.m_ptr;
		m_counter = i_other.m_counter;
		if(m_counter) (*m_counter)++;
	}
	smart_shared_ptr(const smart_weak_ptr<T>& weak_ptr)
		: m_ptr(weak_ptr.m_ptr), m_counter(weak_ptr.m_shared_count)
	{
		if (m_counter) (*m_counter)++;
	}
	smart_shared_ptr(smart_shared_ptr<T>&& i_other) noexcept
	{
		m_ptr = i_other.m_ptr;
		m_counter = i_other.m_counter;

		i_other.m_ptr = nullptr;
		i_other.m_counter = nullptr;
	}
	~smart_shared_ptr()
	{
		if (m_counter && --(*m_counter) == 0)
		{
			delete m_ptr;
			delete m_counter;
		}
		
	}
	smart_shared_ptr& operator=(const smart_shared_ptr& i_other)
	{
		if (this == &i_other) return *this;
		if (m_counter && --(*m_counter) == 0)
		{
			delete m_ptr;
			delete m_counter;
		}
		m_ptr = i_other.m_ptr;
		m_counter = i_other.m_counter;
		if (m_counter) (*m_counter)++;
		return *this;
	}
	smart_shared_ptr& operator=(smart_shared_ptr&& i_other) noexcept
	{
		if (this == &i_other) return *this;
		if (m_counter && --(*m_counter) == 0)
		{
			delete m_ptr;
			delete m_counter;
		}
		m_ptr = i_other.m_ptr;
		m_counter = i_other.m_counter;
		
		i_other.m_ptr = nullptr;
		i_other.m_counter = nullptr;

		return *this;
	}
	T& operator*() const
	{
		return *m_ptr;
	}
	T* operator->() const
	{
		return m_ptr;
	}
	T* get() const
	{
		return m_ptr;
	}
	void reset()
	{
		if (m_counter && --(*m_counter) == 0)
		{
			delete m_ptr;
			delete m_counter;
		}
		m_ptr = nullptr;
		m_counter = nullptr;
	}
	operator bool() const
	{
		return m_ptr != nullptr;
	}
	int use_count()
	{
		if(m_counter) return *m_counter;
	}
	friend class smart_weak_ptr<T>;


private:
	T* m_ptr;
	int* m_counter;
};
