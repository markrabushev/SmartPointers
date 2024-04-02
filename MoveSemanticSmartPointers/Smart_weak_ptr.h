#pragma once


template <class T>
class smart_weak_ptr
{
public:
    smart_weak_ptr() : m_ptr(nullptr), m_shared_count(nullptr), m_weak_count(nullptr) {}
    smart_weak_ptr(const smart_weak_ptr<T>& i_other)
        : m_ptr(i_other.m_ptr), m_shared_count(i_other.m_shared_count), m_weak_count(i_other.m_weak_count) 
    {
        if (m_ptr) {
            (*m_weak_count)++;
        }
    }
    smart_weak_ptr(const smart_shared_ptr<T>& shared_ptr): m_ptr(shared_ptr.m_ptr), m_shared_count(shared_ptr.m_counter)
    {
        if (m_ptr) {
            m_weak_count = new int(1);
        }
    }
    smart_weak_ptr(smart_weak_ptr&& i_other) noexcept 
    {
        m_ptr = i_other.m_ptr;
        m_shared_count = i_other.m_shared_count;
        m_weak_count = i_other.m_weak_count;

        i_other.m_ptr = nullptr;
        i_other.m_shared_count = nullptr;
        i_other.m_weak_count = nullptr;
    }
    smart_weak_ptr<T>& operator=(const smart_weak_ptr<T>& i_other) 
    {
        if (this == &i_other) return *this;
        reset();
        m_ptr = i_other.m_ptr;
        m_shared_count = i_other.m_shared_count;
        m_weak_count = i_other.m_weak_count;
        if (m_ptr) {
            (*m_weak_count)++;
        }
        return *this;
    }
    smart_weak_ptr<T>& operator=(smart_weak_ptr<T>&& i_other) noexcept 
    {
        if (this == &i_other) return *this;
        reset();
        m_ptr = i_other.m_ptr;
        m_shared_count = i_other.m_shared_count;
        m_weak_count = i_other.m_weak_count;

        i_other.m_ptr = nullptr;
        i_other.m_shared_count = nullptr;
        i_other.m_weak_count = nullptr;
        return *this;
    }
    smart_weak_ptr<T>& operator=(const smart_shared_ptr<T>& i_other)
    {
        m_ptr = i_other.m_ptr;
        m_shared_count = i_other.m_counter;
        *m_weak_count = 1;
        return *this;
    }
    bool expired() const {
        return !m_ptr || (*m_shared_count == 0);
    }

    smart_shared_ptr<T> lock() const {
        if (expired()) {
            return smart_shared_ptr<T>();
        }
        return smart_shared_ptr<T>(*this);
    }

    void reset() {
        if (m_ptr) {
            if (m_weak_count && --(*m_weak_count) == 0) {
                delete m_ptr;
                delete m_shared_count;
                delete m_weak_count;
            }
            m_ptr = nullptr;
            m_shared_count = nullptr;
            m_weak_count = nullptr;
        }
    }
    friend class smart_shared_ptr<T>;

private:
    T* m_ptr;
    int* m_shared_count;
    int* m_weak_count;
};
