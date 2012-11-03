#pragma once

template<typename T> class Singleton
{

public:
	static T& Instance()
	{
		static T theSingleInstance; // assumes T has a default constructor
		return theSingleInstance;
	}

protected:
	// force this class to be abstract (can't initialize)
	//virtual Singleton() { };
	//Singleton() { };
};

// USAGE:
// In the derived class you should add the following line
//  friend class Singleton<T>;
// and also make its constructor protected