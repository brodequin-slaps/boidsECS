#pragma once

#include <iostream>
#include <tuple>
#include <memory>
#include <cstring>

//gereral stuff

template<typename Fn, typename... Args>
void foreach_tuple(Fn&& fn, std::tuple<Args...>& tup)
{
	std::apply([fn = std::forward<Fn>(fn)](auto&... elem)
	{
		(fn(elem), ...);
	}, tup);
}

template<typename Fn, typename... Args>
void foreach_tuple(Fn&& fn, std::tuple<Args...> const& tup)
{
	std::apply([fn = std::forward<Fn>(fn)](auto const&... elem)
	{
		(fn(elem), ...);
	}, tup);
}

//ECS boids specific

struct position3f
{
    float x;
    float y;
    float z;
};

struct position2i
{
	int x, y;
};

bool operator==(position2i const& lhs, position2i const& rhs);
bool operator<(position2i const& lhs, position2i const& rhs);

struct speed3f
{
    float x;
    float y;
    float z;

	void print()
	{
		std::cout << z << std::endl;
	}
};

struct speed2i
{
	int x, y;
};

struct Mass
{
	operator float() const
	{
		return m;
	}
    float m;
};

struct Counter
{
	operator size_t() const
	{
		return counter;
	}

	Counter& operator += (int increment)
	{
		this->counter += increment;
		return *this;
	}

	size_t counter;
};

struct AspectRatio
{
	uint x, y;
};

template<typename T>
struct stack_allocated_ptr
{
    char stack_mem[sizeof(T)];

    template<typename... Args>
    stack_allocated_ptr(Args&&... args)
    {
		new (stack_mem) T{std::forward<Args>(args)...};
    }

    operator T*()
    {
        return reinterpret_cast<T*>(this);
    }

	operator T&()
    {
        return reinterpret_cast<T&>(this);
    }
};


template<typename T>
struct dummy_T : T
{
	template<typename... Args>
    dummy_T(Args&&... args) : T{std::forward<Args>(args)...}
    {
    }

	~dummy_T()
	{
	}

	dummy_T(dummy_T const& other)
	{
	}

	dummy_T(dummy_T&& other)
	{
	}

	dummy_T& operator=(dummy_T const& other)
	{
	}
	dummy_T& operator=(dummy_T&& other)
	{
	}

	operator T&()
	{
		return static_cast<T&>(*this);
	}
};