#pragma once
#include <iostream>

template<class T> class SingletonBase
{
protected:
	SingletonBase() {}
	virtual ~SingletonBase() {}
public:
	static T* GetInstance()
	{
		static T singleton;
		return &singleton;
	}

};

template<class T> 
T LinearInterpolate(const T& startV, const T& endV, 
	int nowCnt, int maxFlame)
{
	float t = nowCnt / (float)maxFlame;
	return startV*(1 - t) + endV*t;
}

//template<class T, template <class A, class Allocator = std::allocator<A> > class Container = std::vector>
//class Clerp
//{
//private:
//	bool valid;
//	Container<T> x, y;
//	const int n;
//
//public:
//	Clerp(container<T> x, Container<T> y) : valid(false), x(x), y(y), n(x.size() - 1)
//	{
//		//要素数が2個以上か調べる
//		if (x.size() < 2 || y.size() < 2)
//		{
//			std::cout << "Error! The size of X or Y must be greater than 2" << std::endl;
//			return;
//		}
//		//要素数が同じか調べる
//		if (x.size() != y.size())
//		{
//			std::cout << "Error! The size of X and Y are different" << std::end;
//			return;
//		}
//		//単調増加か調べる
//		for (int i = 0; i < n - 1; i++)
//		{
//			if (x[i] > x[i + 1])
//			{
//				std::cout << "Error! X must be monotonically increasing" << std::endl;
//				return
//			}
//		}
//		valid = true;
//
//		Get(T x)
//		{
//			//コンストラクタが正常でない場合終了
//			if (!valid)
//			{
//				return 0;
//			}
//
//			//最初の要素より小さかった場合、最初の２つの要素を線形補間
//			if (x < x[0])
//			{
//				return y[0] + (y[1] - y[0]) / (x[1] - x[0]) * (x - x[0]);
//
//			}
//			//最後の要素より大きかった場合、最後の２つの
//		}
//	}
//}