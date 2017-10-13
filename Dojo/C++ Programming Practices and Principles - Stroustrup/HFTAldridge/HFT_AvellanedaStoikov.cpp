/*
PLEASE READ THIS IMPORTANT DISCLAIMER
This code is distributed AS IS, and is 
not subject to any warranty, performance
guarantees, etc.  

It is intended strictly for educational
purposes to illustrate the concepts 
presented in Irene Aldridge's book: 
"High-Frequency Trading: A Practical Guide
to Algorithmic Strategies and Trading Systems".

Any commercial distribution of the code is 
strictly prohibited.  
*/


void HFT_AvellanedaStoikov()
{
	FILE* fin, *fout;
	double lambda_a, lambda_b, d_lambda_a, d_lambda_b;
	int hh = 0, mm = 0, ss, nb = 0, na = 0, prevnb = 0, prevna = 0, prevm = 0;
	double bid, ask, prevbid = 0, prevask = 0;
	char * p1, *p2, buffer[1024], fname[512];
	double gamma = 0.01;
	double optbid = 0;
	double optask = 0;
	char action;
	double portfolio = 0;
	int position = 0;
	double bids[100] = {0}, asks[100] = {0};

	sprintf(fname, "C:/AvellanedaStoikov2008_WFC_InputData.txt"); //download this file from hftradingbook.com
	fin = fopen(fname, "r");
	if(fin)
	{
		sprintf(fname, "C:/AvellanedaStoikov2008_output.txt");
		fout = fopen(fname, "w");
		if(fout)
		{
			//for each event, find the before and after window
			while(fgets(buffer, 1024, fin))
			{
				bid = 0;
				ask = 0;
				sscanf(buffer, "%d\t%d\t%lf\t%lf\n", &hh, &mm, &bid, &ask);
				
				if(prevm != mm)
				{
					if((nb-prevnb != 0) & (nb != 0) & (prevnb != 0))
						optbid = bid- (1/gamma)*log(1-gamma*(((double)nb)/(double)(nb-prevnb)/prevnb));
					if((na-prevna != 0) & (na != 0) & (prevna != 0))
						optask = ask- (1/gamma)*log(1-gamma*(((double)na)/(double)(na-prevna)/prevna));

					if((optbid > 0) & (optask > 0) & (bid > 0) & (ask > 0))
					{
						if(hh > 15) 
						{
							if(position != 0)
							{
								action = 'L';
								//liquidate
								if(position > 0)
								{
									portfolio += position*bid;
									position = 0;
								}
								else if(position < 0)
								{
									portfolio -= position*ask;
									position = 0;
								}
							}
						}
						else
						{
							if(optbid > ask)
							{
								//if(position <= 3)
								{
									action = 'B';
									portfolio -= ask;
									position++;
								}
								//else action = 'N';
							}
							else if(optask < bid)
							{
								//if(position >= -3)
								{
									action = 'A';
									portfolio += bid;
									position--;
								}
								//else action = 'N';
							}
							else
							{
								//between bid and ask
								//if closer to bid, buy
								//else sell
								if(fabs(bid-optbid) < fabs(ask-optask))
								{
									action = 'B';
									portfolio -= ask;
									position++;
								}
								else if(fabs(bid-optbid) > fabs(ask-optask))
								{
									action = 'A';
									portfolio += bid;
									position--;
								}
							}
						}
						//output

						if((na != 0) & (nb != 0) & (prevna != 0) & (prevnb != 0))
							fprintf(fout, "%02d\t%02d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%c\t%lf\t%d\n",
								hh, mm, bid, ask, (bid+ask)/2, (1/(double)nb), (1/(double)na), 
								(double)(nb-prevnb)/prevnb, (double)(na-prevna)/prevna, round(optbid, 2), round(optask, 2),
								action, portfolio, position);
					}
					prevm = mm;
					prevna = na;
					prevnb = nb;
					na = 0;
					nb = 0;
				}

				if((prevbid > 0) & (prevask > 0))
				{
					if(bid != prevbid)
					{
						nb++;
					}
					if(ask != prevask)
					{
						na++;
					}
				}
				prevbid = bid;
				prevask = ask;
			}
			fclose(fout);
		}
		fclose(fin);
	}
}
