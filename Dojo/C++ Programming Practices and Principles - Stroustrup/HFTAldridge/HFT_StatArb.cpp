////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void AnalyzePair(char* symbol1, char* symbol2)
{
	double close1[100] = {0};
	int n1 = 0, dates1[100] = {0};
	double close2[100] = {0};
	int n2 = 0, dates2[100] = {0};
	double avgdiff = 0;
	double stddiff = 0;
	double nStdDevs = 2;
	double minInfoRatio = 1;
	double infoRatio = 0;
	double closediff = 0;
	double ub = 0;
	double lb = 0;

        // LoadPriceHistory is a function that populates arrays
        // close1 and dates1 with closing prices and dates/times, 
        // respectively.  n1 is the returned number of elements in
        // arrays close1 and dates1.
        // LoadPriceHistory has the following specification:
        //     void LoadPriceHistory(char * symbol, double* c, int* dates, int* n)       
        //
	LoadPriceHistory(symbol1, close1, dates1, &n1);
	LoadPriceHistory(symbol2, close2, dates2, &n2);

	int i = 0, j, k;
	double n = (double)n2;
	if(n1 < n2)
		n = (double)n1;

	if((n1 == 0) | (n2 == 0))
		return;

	if(n1 != n2)
	{
		//align dates
		for(i = 0; i<n; i++)
		{
			if(dates1[i] < dates2[i])
			{
				for(j = i; j<n2; j++)
				{
					if(dates2[j] == dates1[i])
						break;
				}
				k = i;
				while(j < n2)
				{
					dates2[k] = dates2[j];
					high2[k] = high2[j];
					low2[k] = low2[j];
					close2[k] = close2[j];
					j++;
					k++;
				}
			}
			if(dates1[i] > dates2[i])
			{
				for(j = i; j<n1; j++)
				{
					if(dates2[j] == dates1[i])
						break;
				}
				k = i;
				while(j < n1)
				{
					dates1[k] = dates1[j];
					high1[k] = high1[j];
					low1[k] = low1[j];
					close1[k] = close1[j];
					j++;
					k++;
				}
			}
		}
		n = i;
	}

	if(n == 0)
		return;

	//compute avg and std out of sample for N=30
	//calculate %accuracy the following day
	double pctAccuracy = 0, sampleSize = 0;
	int buy= 0, sell = 0;

	avgdiff = 0;
	stddiff = 0;
	buy= 0;
	sell = 0;

	for(i = 1; i<31; i++)
	{
		avgdiff += close1[i] - close2[i];
	}
	avgdiff = avgdiff/n;

	for(i = 1; i<31; i++)
	{
		stddiff += pow((close1[i] - close2[i] - avgdiff), 2);
	}
	stddiff = stddiff/(n-1);
	stddiff = pow(stddiff, 0.5);

	//
	if(stddiff > 0)
	{
		infoRatio = stddiff/fabs(avgdiff);
		if(infoRatio < minInfoRatio)
		{
			if(close1[0] - close2[0] < avgdiff - nStdDevs*stddiff)
				buy = 1; //buy symbol 1 and sell symbol 2
			if(close1[0] - close2[0] > avgdiff + nStdDevs*stddiff)
				sell = 1; //buy symbol 2 and sell symbol 1
			if((buy == 1) | (sell == 1))
			{
				closediff = close1[0] - close2[0];
				ub = avgdiff + nStdDevs*stddiff;
				lb = avgdiff - nStdDevs*stddiff;
                                if(buy)
        				printf("%s is underpriced relative to %s\n", symbol1, symbol2);
                                else
        				printf("%s is underpriced relative to %s\n", symbol2, symbol1);
			}
		}
	}

	return;
}
