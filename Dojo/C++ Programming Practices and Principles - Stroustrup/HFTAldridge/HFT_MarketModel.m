%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PLEASE READ THIS IMPORTANT DISCLAIMER
% This code is distributed AS IS, and is 
% not subject to any warranty, performance
% guarantees, etc.  
%
% It is intended strictly for educational
% purposes to illustrate the concepts 
% presented in Irene Aldridge's book: 
% "High-Frequency Trading: A Practical Guide
% to Algorithmic Strategies and Trading Systems".
% 
% Any commercial distribution of the code is 
% strictly prohibited.  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function HFT_MarketModel()

n = 32;

x1 = ForecastOneName('EWC', n)
x2 = ForecastOneName('IBM', n)

dbeta = x1(1,2) - x2(1,2);
sdbeta = (1/n)*((x1(1, 4)^2 + x2(1, 4)^4)^0.5);
tbeta = dbeta/sdbeta


dalpha = x1(1,1) - x2(1,1);
sdalpha = (1/n)*((x1(1, 3)^2 + x2(1, 4)^3)^0.5);
talpha = dalpha/sdalpha

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [x] = ForecastOneName(name, n)

x = zeros(n, 4);

for day = 1:n
   x(day, :) = ForecastOneNamePerDay(name, day);
end

end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [x] = ForecastOneNamePerDay(name, day)

clear data0;
% get SPY
fname = sprintf('C:/SPY_hist_data_day%d.txt', day);
data0 = dlmread(fname, '\t');
sSPY = size(data0);
nSPY = sSPY(1);

clear data1;
% get data
clear fname;
fname = sprintf('C:/%s_hist_data_day%d.txt', name, day);
data1 = dlmread(fname, '\t');
s = size(data1);
n = s(1);

if(n > nSPY)
    n = nSPY; %equalize the number of rows
end

clear dataSPY;
dataSPY = zeros(n, 3);
for i = 1:n
    dataSPY(i, 1) = data0(n-i+1,5);
    dataSPY(i, 2:3) = data0(n-i+1,3:4);
end

clear data;
data = zeros(n, 3);
for i = 1:n
    data(i, 1) = data1(n-i+1,5);
    data(i, 2:3) = data1(n-i+1,3:4);
end

lag = 32;

delay = 1;

if(lag + 1 < n)
    
    clear x;
    
    clear retsSPY;
    clear rets;
    % compute returns based on closing prices for each sampling period
    retsSPY = zeros(lag, 1);
    retsSPY = dataSPY(n-lag+1:n, 1)./dataSPY(n-lag:n-1, 1)-1;
    rets = zeros(lag, 1);
    rets = data(n-lag+1:n, 1)./data(n-lag:n-1, 1)-1;
    
    clear Y;
    Y = retsSPY;
    clear X;
    X = ones(lag, 2);
    X(:, 2) = rets;

    %disp([Y(1:10, 1) X(1:10,:)]);
    
    IXX = inv(X'*X);
    beta_ = IXX*(X'*Y);
    alpha = beta_(1,1);
    beta = beta_(2,1);
    
    sb = size(X);
    e = Y - X*beta_;
    s2 = (e'*e)/(sb(1)-2);  % s(Y|X) = (e'*e)/(sb(2)-2)
    s_b = (IXX(2,2)*s2).^0.5;
    t_b = beta./s_b;
    
    s_a = (s2*(1/sb(1)+(mean(X(:,2))^2)*IXX(1,1))).^0.5;
    t_a = alpha./s_a;

    
    x = [alpha beta s_a s_b];

end

end
