/*
	http://ikpil.com
*/
#pragma once

template <typename T>
inline constexpr void SAFE_RELEASE_DELETE(T*& p)
{
	if (p)
	{
		p->Release();
		delete p;
	}
	p = nullptr;
};

template <typename T>
inline constexpr void SAFE_RELEASE(ComPtr<T>& p)
{
	if (p) p->Release();
	p = nullptr;
};

template <typename T>
inline constexpr void SAFE_RELEASE(T*& p)
{
	if (p) p->Release();
	//p = nullptr;
};

template <typename T>
inline constexpr void SAFE_DELETE(T*& p)
{
	if (p) delete p;
	p = static_cast<T *>(0);
};


template <typename T>
inline constexpr void SAFE_DELETE_ARRAY(T*& p)
{
	delete[] p;
	p = static_cast<T *>(0);
}

template <typename T, typename F>
inline constexpr void SAFE_DELET_F(T*& p, F f)
{
	if (0 == p)
		return;

	f();

	safe_delete(p);
}

template <typename T, typename F>
inline constexpr void CONST_SAFE_DELETE_F(const T*& cp, F f)
{
	T* p = const_cast<T *>(cp);

	safe_delete_f(p, f);
	cp = static_cast<const T*>(0);
}

template <typename T, typename F>
inline constexpr void SAFE_DELETE_ARRAY_F(T*& p, F f)
{
	if (0 == p)
		return;

	f();
	safe_delete_array(p);
}

template <typename T, typename F>
inline constexpr void CONST_SAFE_DELETE_ARRAY_F(const T*& cp, F f)
{
	T* p = const_cast<T *>(cp);

	safe_delete_array_f(p, f);
	cp = static_cast<const T*>(0);
}

template <typename T>
inline constexpr void SAFE_DELETE_MFf(T*& p, void (T::* mf)())
{
	if (0 == p)
		return;

	(p->*mf)();

	safe_delete(p);
}

template <typename T>
inline constexpr void CONST_SAFE_DELETE_MF(const T*& cp, void (T::* mf)())
{
	T *p = const_cast<T *>(cp);

	safe_delete_mf(p, mf);
	cp = static_cast<const T*>(0);
}

template <typename T>
inline constexpr void SAFE_DELETE_MF2(T*& p, void (T::* mf1)(), void (T::* mf2)())
{
	if (0 == p)
		return;

	(p->*mf1)();

	(p->*mf2)();

	safe_delete(p);
}

template <typename T>
inline constexpr void CONST_SAFE_DELETE_MF2(const T*& cp, void (T::* mf1)(), void (T::* mf2)())
{
	T *p = const_cast<T *>(cp);

	safe_delete_mf2(p, mf1, mf2);
	cp = static_cast<const T*>(0);
}

template <typename T>
inline constexpr void VECTOR_RELEASE(const T& vector)
{
	for (auto& v : vector)
		v->rlease();
	vector.clear();
}

// for gcc comfile, no line at end of file.