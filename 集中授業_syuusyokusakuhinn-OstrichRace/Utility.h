
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