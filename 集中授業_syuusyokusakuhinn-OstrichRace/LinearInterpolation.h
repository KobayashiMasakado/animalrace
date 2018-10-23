#pragma once
#include <stdio.h>

//���`��Ԃ̌���
#define INTERP(xi,xi1,yi,yi1,x)(yi + (((yi1 - yi)*(x - xi))/(xi1 - xi)))

//class LinearInterpolation
//{
	//����
	const int ar[] = {
		/*x*/ 10,50,100,
		/*z*/ 50,100,200
	};
	//����̉��̒���
	const int ar_w = (sizeof(ar) / sizeof(ar[0])) / 2;

	//���`���
	int interpldim(const int x, const int* ar, const int w)
	{
		if (x <= ar[0])
		{
			return ar[w];
		}
		else if (x >= ar[w - 1])
		{
			return ar[w * 2 - 1];
		}

		for (int i = 1; i < w; i++)
		{
			if (ar[i] >= x)
			{
				break;
			}
			//y=yi + (yi+1-yi)(x-xi)/(xi+1-xi)���s���l��Ԃ�
			return INTERP(ar[i - 1], ar[i], ar[i + w - 1], ar[i + w], x);
		}
	}
//};