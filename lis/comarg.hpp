#ifndef LIS_COMMAND_ARGUMENT_HPP_3728
#define LIS_COMMAND_ARGUMENT_HPP_3728

#include <cstdlib>







namespace lis
{





inline int _arg(char *s, int def = 0)
{
	char *e;
	int res = strtol(s, &e, 10);
	return e == s ? def : res;
}

inline long _arg(char *s, long def = 0)
{
	char *e;
	long res = strtol(s, &e, 10);
	return e == s ? def : res;
}
	
inline long long _arg(char *s, long long def = 0)
{
	char *e;
	long long res = strtol(s, &e, 10);
	return e == s ? def : res;
}



template<typename T>
inline T arg(char *s, T def = T())
{
	return _arg(s, def);
}

template<typename T>
inline T arg(int argc, char **argv, int i, T def = T())
{
	return i < argc ? arg<T>(argv[i], def) : def;
}





}





#endif
