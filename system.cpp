#include "system.h"

int clear()
{
	return system("clear");
}

// int sleep(float time)
// {
// 	if(time < 0.0f)
// 	{
// 		return -1;
// 	}
	
// 	char floatArray[sizeof(time)];
// 	char arr[6] = 'sleep '
// 	char* sleepCMD = arr[6] + sprintf(floatArray, "%f", time);
// 	return system("sleep ");
// }
