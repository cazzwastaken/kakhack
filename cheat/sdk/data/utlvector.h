#pragma once

inline int CalcNewAllocationCount(int allocationCount, int growSize, int newSize, int bytesItem)
{
	if (growSize)
		allocationCount = ((1 + ((newSize - 1) / growSize)) * growSize);
	else
	{
		if (!allocationCount)
			allocationCount = (31 + bytesItem) / bytesItem;

		while (allocationCount < newSize)
			allocationCount *= 2;
	}

	return allocationCount;
}

template <class T, class N = int>
class UtlMemory
{
public:
	T& operator[](N i)
	{
		return memory[i];
	}

	const T& operator[](N i) const
	{
		return memory[i];
	}

	T* Base()
	{
		return memory;
	}

	int NumAllocated() const
	{
		return allocationCount;
	}

	void Grow(int num = 1)
	{
		if (IsExternallyAllocated())
			return;

		int oldAllocationCount = allocationCount;
		int allocationRequested = allocationCount + num;
		int newAllocationCount = CalcNewAllocationCount(allocationCount, growSize, allocationRequested, sizeof(T));

		if (static_cast<int>(static_cast<N>(newAllocationCount)) < allocationRequested)
		{
			if (static_cast<int>(static_cast<N>(newAllocationCount)) == 0 && static_cast<int>(static_cast<N>(newAllocationCount - 1)) >= allocationRequested)
				--newAllocationCount;
			else
			{
				if (static_cast<int>(static_cast<N>(allocationRequested)) != allocationRequested)
				{
					return;
				}

				while (static_cast<int>(static_cast<N>(newAllocationCount)) < allocationRequested)
					newAllocationCount = (newAllocationCount + allocationRequested) / 2;
			}
		}

		allocationCount = newAllocationCount;

		if (memory != nullptr)
		{
			//pMemory = reinterpret_cast<T*>(I::MemAlloc->Realloc(pMemory, iAllocationCount * sizeof(T)));

			std::byte* data = new std::byte[allocationCount * sizeof(T)];
			memcpy(data, memory, oldAllocationCount * sizeof(T));
			memory = reinterpret_cast<T*>(data);
		}
		else
			//pMemory = reinterpret_cast<T*>(I::MemAlloc->Alloc(iAllocationCount * sizeof(T)));
			memory = reinterpret_cast<T*>(new std::byte[allocationCount * sizeof(T)]);
	}

	bool IsExternallyAllocated() const
	{
		return growSize < 0;
	}

protected:
	T* memory;
	int allocationCount;
	int growSize;
};

template <class T>
void Destruct(T* memory)
{
	memory->~T();
}

template <class T>
T* Construct(T* memory)
{
	return new(memory) T;
}

template< class T >
T* Copy(T* memory, T const& src)
{
	return new(memory) T(src);
}

template <class T, class A = UtlMemory<T>>
class UtlVector
{
	using Allocator = A;
public:
	auto begin() const noexcept
	{
		return memory.Base();
	}

	auto end() const noexcept
	{
		return memory.Base() + size;
	}

	T& operator[](int i)
	{
		return memory[i];
	}

	const T& operator[](int i) const
	{
		return memory[i];
	}

	T& Element(int i)
	{
		return memory[i];
	}

	const T& Element(int i) const
	{
		return memory[i];
	}

	T* Base()
	{
		return memory.Base();
	}

	int Count() const
	{
		return size;
	}

	int& Size()
	{
		return size;
	}

	void GrowVector(int count = 1)
	{
		if (size + count > memory.NumAllocated())
			memory.Grow(size + count - memory.NumAllocated());

		size += count;
	}

	void ShiftElementsRight(const int element, const int shift = 1)
	{
		const int toMove = size - element - shift;

		if (toMove > 0 && shift > 0)
			memmove(&Element(element + shift), &Element(element), toMove * sizeof(T));
	}

	void ShiftElementsLeft(const int element, const int shift = 1)
	{
		const int toMove = size - element - shift;

		if (toMove > 0 && shift > 0)
			memmove(&Element(element), &Element(element + shift), toMove * sizeof(T));
	}

	int InsertBefore(const int element)
	{
		// can insert at the end
		GrowVector();
		ShiftElementsRight(element);
		Construct(&Element(element));
		return element;
	}

	int InsertBefore(int element, const T& src)
	{
		// reallocate if can't insert something that's in the list
		// can insert at the end
		GrowVector();
		ShiftElementsRight(element);
		Copy(&Element(element), src);
		return element;
	}

	int AddToTail()
	{
		return InsertBefore(size);
	}

	int AddToTail(const T& src)
	{
		return InsertBefore(size, src);
	}

	int Find(const T& src) const
	{
		for (int i = 0; i < Count(); ++i)
		{
			if (Element(i) == src)
				return i;
		}

		return -1;
	}

	void Remove(const int element)
	{
		Destruct(&Element(element));
		ShiftElementsLeft(element);
		--size;
	}

	void RemoveAll()
	{
		for (int i = size; --i >= 0;)
			Destruct(&Element(i));

		size = 0;
	}

	bool FindAndRemove(const T& src)
	{
		if (const int element = Find(src); element != -1)
		{
			Remove(element);
			return true;
		}

		return false;
	}

protected:
	Allocator memory;
	int size;
	T* elements;
};
