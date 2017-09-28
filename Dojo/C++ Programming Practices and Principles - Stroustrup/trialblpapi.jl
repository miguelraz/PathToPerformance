using Miletus, Blpapi
IP = "localhost"; Port = 8194
Session = createSession(IP, Port)
methods(bdp)
Response = bdp(Session, tickers, fields)
ibmLastPrice = Response["IBM US Equity", "PX_Last"]
ibmOpenPrice = Response["IBM US Equity", "PX_Open"]
appleLastPrice = Response["AAPL US Equity", "PX_Last"]
appleOpenPrice = Response["AAPL US Equity", "PX_Open"]
tickers =  ["IBM US Equity", "AAPL US Equity"]
fields = ["PX_Open", "PX_High", "PX_Last", "PX_Close"]



startDate = "20070707"
endDate = "20170707"

history = bdh(session, tickers, fields, startDate, endDate)
using JuliaDB
using Miletus, BusinessDays
using Miletus.TermStructure
using Miletus.DayCounts
import Miletus: Both, Receive, Contract, When, AtObs, value
import Miletus: YieldModel
import BusinessDays: USGovernmentBond
import Base.Dates: today, days, Day, Year

using Miletus
using Gadfly
using Colors
d1 = Dates.today()
d2 = d1 + Dates.Day(120)

m = GeomBMModel(d1, 100.00, 0.05, 0.0, 0.3)
mcm = montecarlo(m, d1:d2, 100_000)

theme=Theme(default_color=Colors.RGBA{Float32}(0.1, 0.1, 0.7, 0.1))
p = plot([layer(x=mcm.dates,y=mcm.paths[i,:],Geom.line,theme) for i = 1:200]...)

o = EuropeanCall(d2, SingleStock(), 100.00)
value(m, o)

value(mcm, o)

oa1 = AsianFixedStrikeCall(d2, SingleStock(), Dates.Month(1), 100.00)

using JLD2

file = "Blpapi"
pwd()
@save "blpapihistory.jld2" file history

pwd()
