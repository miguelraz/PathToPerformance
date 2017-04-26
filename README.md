
__Stuff I've learned: Annotations on the path to Julia Nirvana__
======================
Scientific Day Logger
---------------------

A trillion points of altruism to Julia's Gitter chat and its benign and helpful netizens.

:shipit:

### 07/04/2017

88. Chris gives us an awesome lecture on mathematical history of numerial methods
> yeah, might as well be
it's like LSODA
people like it because of history, and the idea
in reality, Sundials decended from the Petzold algorithms (LSODA)
early Sundials had stiffness detection and switching, because the code was essentially LSODA
they took it out because it slowed things down
(the detection on multistep methods can be costly)

>[Since Shampine wrote this, the authors of NR have consulted a worker active in the field. Unfortunately, a great many other experts in the field consider the advice they got to be very poor indeed -- extrapolation methods are almost always substantially inferior to Runge-Kutta, Taylor's series, or multistep methods.]
There's a better way of thinking about extrapolation techniques
essentially, they are a bad arbitrary order Runge-Kutta method
If you pick an order
then at that order
it actually is an Runge-Kutta method
if you check the number of steps, there are far more steps than optimal.
And if you check the coefficient of the highest order error term, its really bad
so it's essentially just a series of bad RK methods.
however, if your necessary tolerance is really low, then a higher order RK method will always do better
but the definition of "low" seems to be really low
like, 5th order does well until like 1e-5, then something like 8th order does well until you need sub 1e-16 accuracy, 14th order still beats extrapolation even at accuracies like 1e-40

> a recent result by Gyongy is a BS technique for parabolic SPDEs
which shows that higher order methods can achieve arbitrary accuracy
(easy way to prove that)
but it still doesn't break the Kloeden computational barrier.
(accuracy vs computational cost metric in SPDEs)

> Random Differential Equations - wait for Kloeden's book.

> • Davie & Gaines (2000) showed that any numerical scheme applied to the SPDE
(6) with f = 0 which uses only values of the noise Wt cannot converge faster than
the rate of 1/6 with respect to the computational cost

> https://www.researchgate.net/publication/314242937_Random_Ordinary_Differential_Equations_and_their_Numerical_Solution
you can find the thesis if you look hard enough
it's online
it has a bunch of methods for higher order RODEs
and I'll get around to implementing it
Oh, I stored the reference in the issue discussing RODEs in diffeq
JuliaDiffEq/DifferentialEquations.jl#145
http://publikationen.ub.uni-frankfurt.de/frontdoor/index/index/docId/40146

> if you want the most modern "book" on the subject, this is it: http://www.math.uni-luebeck.de/mitarbeiter/roessler/publikationen-e.php
http://epubs.siam.org/doi/10.1137/09076636X  that being the main article I think
or this review: http://www.math.uni-hamburg.de/research/papers/prst/prst2010-02.pdf
with the latest development of course being http://chrisrackauckas.com/assets/Papers/ChrisRackauckas-AdaptiveSRK.pdf

> the field diverged a bit
essentially because it is really hard to beat Euler's method
and so mathematicians still study it a little bit
but pushed forward to new equations
like RODEs and SPDEs
where some semblance of "better than Euler" is just coming out
while the more applied communities went to solving discrete stochastic (Gillespie) methods
ftp://www.cs.toronto.edu/na/reports/NA.Bio.Kin.Survey.rev1.pdf
(pst! If anyone wants to join in with implementing these algorithms... JuliaDiffEq/DiffEqJump.jl#8 )

> where if you estimate "lots of proteins", you have ODEs
"a good amount" you have SDEs
"very small", then you don't have concentrations any more, but discrete numbers
but you can still write out stochastic simulations (Gillespie's algorithm)
but the breakthrough was the convergence results to SDEs
and then Burrage's Poisson Runge-Kutta methods (and Gillespie+ Petzold's tau-leaping)
essentially, a type of Runge-Kutta that works in the case where the numbers of things are discrete and stochastic.
There's still a shit ton to work out there
but Kloeden's RODE work is interesting, because technically those discrete stochastic equations are RODEs
so higher order methods for RODEs work even with discrete variables and other nonsense.

89. [Why not to use Numerical Recipes](https://www.stat.uchicago.edu/~lekheng/courses/302/wnnr/nr.html)

90. [Chris gives homework!](https://github.com/JuliaDiffEq/DiffEqJump.jl/issues/8)

91.




### 06/04/2017

83. Added a whole bunch of parallel/distributed/performance resources.
* [Arch's slides](http://www.blonzonics.us/julia/juliacon-2016), [huge comment](https://github.com/JuliaLang/julia/issues/1790) and [recommended reading](http://supertech.csail.mit.edu/papers/tushara-meng-thesis.pdf)
* Loop [fusion notebook](https://github.com/JuliaLang/julialang.github.com/blob/master/blog/_posts/moredots/More-Dots.ipynb) [and blog post](https://julialang.org/blog/2017/01/moredots)
* Cache management
* Multidimensional [arrays and iteration](https://julialang.org/blog/2016/02/iteration)
* Do the damn manual
* v0.5 [Highlights](https://julialang.org/blog/2016/10/julia-0.5-highlights)
* Parallel [Accelerator](https://julialang.org/blog/2016/03/parallelaccelerator)

84. OK, turns out Wonseok Shin is a Numerical Electromagnetism Beast. Casually asked him for a numerical analysis course notes. Casual. Sweet.

85. John Myles White is [THE MAN](https://github.com/johnmyleswhite/SimpleAintEasy) for statistics and hopefully know a bit more about cache management in Julia.
* Simple [ain't easy - Real-World statistics pitfalls.](https://github.com/johnmyleswhite/SimpleAintEasy/raw/master/book.pdf)
and his [Github looks like the bomb](https://github.com/johnmyleswhite?tab=repositories)

86. Read through [the monster issue on multithreading](https://github.com/JuliaLang/julia/issues/1790). Looks like Cilk is the way to go :D
> I am not fond of the barrier-style of programming made popular by OpenMP for writing resuable components, because barriers introduce composability issues. The problem is that the barrier style fundamentally assumes that you know how many parallel threads of execution you have at the point of starting parallel work. Finding out the answer to that question at any moment in a large system (where other components vie for threads) is exactly the sort of global question that programmers learn not to ask in a scalable parallel program.
Put another way, the "control freak" style of parallel programming ("I totally control the machine") delivers great benchmark results. But you can't marry two control freaks.
-- Arch D Robison, 2014

87. Arch Robison is a legend and aswers emails like a boss.

### 05/04/2017

76. Organized some PathToPerformance stuff wrt courses and links and bibliography. Happily, Arch D. Robison's course on parallelism is based on Cilk+ - which Julia is based on. The cosmos smiles at me... Quote of the day: "Your computer school was weak - I learned from the streets!"

77. Helped Chris out with some PyCall stuff that they broke. Submitted a PR for a CONTRIBUTING.md to eschnetter/FunHPC.jl

78. TODO: 100 Julia array comprehensions, 100 metaprogramming, 100 problems, blog comparing MATLAB and julia before and after codes.

79. Almost done configuring Frankie. Investigate [Pachyderm.io](http://www.pachyderm.io/) and [Kubernets.io](https://kubernetes.io/)

80. Get my ass on DiffEqs before Chris' Seminar!

81. [Must read physics papers](https://www.reddit.com/r/Physics/comments/1xeobv/what_are_classic_papers_every_physicist_should/) includes Alfven, Nobel Prize 1941, made it in a page.

82. @ScottPJones says that strings have not been priority for devs in Julia, but is uniquely suited to handle them in future - delaying this is a problem for data handling.

> You can make parameterized string types, that (using traits) deal with all the sorts of encoding issues (big vs. little endian, linear indexed or not, possibly mutable vs. immutable, code unit size, code point range, validated or not, whether it is possible to go backwards (single byte character sets, UTF-8, UTF-16, UTF-32 can, but most legacy multibyte character sets you can't), and have optimized code generated for different string encodings, writing only pretty generic code.
(take a look at @nalimilan's https://github.com/nalimilan/StringEncodings.jl for how that might look)

### 04/04/2017

74. Miletus is based on [this paper 1](https://www.microsoft.com/en-us/research/wp-content/uploads/2016/07/contracts-icfp.pdf) and [and this paper](http://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=2427D016B409720B4C0520B2D325E4B3?doi=10.1.1.14.7885&rep=rep1&type=pdf) by SL Peyton James and J-M Eber et al.

75. Today in chat we talked about the case of Sage - I remember Felix Lawrence talking about it. Sad days. Academia does not take into account CI or software maintenance, just shitty scripts into pushing papers.

Fight or flight?
:/
New bucketlist goal: make tears [of academic pride](http://www.walkingrandomly.com/?p=6275) flow off a fellow HPCer from proper development practices.

### 03/04/2017

67. Submitted GSoC proposal. Chat was invaluable. Remember Chris' advice about not building a compiler yourself - focus on your thing, let experts do theirs. Balance will be interesting.

68. Read a gazillion Kahan papers. [That man is a beast](http://people.eecs.berkeley.edu/~wkahan/) Julia needs a FLOP debugger. Can Gallium pull it off? Also, Gustafson is misguided as heck, UNUMS are not coming anytime soon. Ever. For anything.

69. Classical papers in numerical analysis by Trefethen [are here](http://web.stanford.edu/class/cme324/classics/)

70. Miletus bug resolved. Properly reported. now use support+juliafin@juliacomputing.com

71. "Mathematics is the art of giving the same name to different things.10
by noted mathematician Henri Poincar´e." - from the [Julia paper ](https://julialang.org/publications/julia-fresh-approach-BEKS.pdf)

72. [Basic assembler commands](https://docs.oracle.com/cd/E36784_01/pdf/E36859.pdf)

73. Julia parallelism method on page 95 of [paper](https://julialang.org/publications/julia-fresh-approach-BEKS.pdf)

### 31/03/2017

66. Never use a darn push array to plot - use array comprehension! Props to Simon Byrne and the Miletus.jl manual.
>
function payoff_curve(c, d::Date, prices)
payoff = [value(GeomBMModel(d, x, 0.0, 0.0, 0.0), c) for x in prices]
p = [x.val for x in payoff]
r = [x.val for x in prices]
return r, p
end

67. [PArallel accelerator talk](https://www.youtube.com/watch?v=Ti9qqAe_NF4). Awesome talk. Possibility of Julia compiler, and of running awesome parallelization stuff. Announced multithreading. Jeeeeeeeeeeeeeeeeeeeeeeeeefffffffffff...

### 30/03/17

59. Enumerate generate a lot of types, says Chris. Use this if you want tons of types for dispatch --> parallelization. Also, Chris says to handle distributed computing via multiple dispatch. Much pro, very wow.

60. Jeff gives [a good overview](https://www.youtube.com/watch?v=osdeT-tWjzk) on how and why internals of Julia work the way they do.

61. [Jameson Nash](https://www.youtube.com/watch?v=ErGi9sNgUjw) explains future avenues of research for Statically compiling Julia and getting a mini hackable version going.

62. Amit Murthy explains [a little of how to sping up your own cluster](https://www.youtube.com/watch?v=XJAQ24NS458)

63. [Miletus.jl DEMO IS FINALLY ONLINE!](https://www.youtube.com/watch?time_continue=4&v=e8h1ZVaeIus)

64. Downloaded free copy of JuliaFIN. Let-s hope beta access means future access for a while, as well as BLPAPI integration.

65. Ctrl-R in REPL helps you find code says KristofferC.

### 29/03/2017

54. Turns out @frederikekre and @KristofferC are behind JuaFEM.jl. Chris says I should consider applying for the DiffEqs.jl project on GSoC. Whelp, let's do it gang!

55. fixed spacing in Chris PR. perhaps a prettyfying script is in order.

56. Read about efficient laziness in the story [The tale of the man who has too lazy to fail](http://emilkirkegaard.dk/en/wp-content/uploads/Robert-A.-Heinlein-Time-enough-for-love_-the-lives-of-Lazarus-Long.pdf)

57. @ararslan made a kick as commit explaining how to [manage the zip function via a recursive algo. Awesome dude](https://github.com/JuliaLang/julia/pull/21208)

58. chris says MXNet > Mocha.jl

### 28/03/17

41. Grammar/style fixes go in a separate PR.
42. sample() from StatsBase is awesome.
43. [Custom allocators](https://en.wikipedia.org/wiki/Allocator_(C%2B%2B)) sound like a damn good idea. You basically allow memory pools, and optimize GC or shared memory.
44. Rackaukas says about Sundials.jl:
>Sundials is good because it's the modern Petzold algorithm
i.e. it's the multistep algorithm
I say "the"
because they are literally all the same algorithm
Gear made it in the 70's, then that became vode, then Petzold did a bunch of stuff to make it lsode, modified it for DAEs to get DASSL and DASPK, then it was translated to C as cvode/ida
all these years, the same code though
there are definitely many things that can be done better, and Sundials is actually quite slow in many cases
which is why I plan to at some point make a full adaptive order+timestep multistep method myself... but it's a huge undertaking
but... multistep methods minimize function evaluations, so if your PDE is really large, Sundials is the best there is.
and since it handles stiff equations, they generally handle most equations (they don't handle large complex eigenvalues well, but still, ehhh)
so they are a workhorse of scientific computing for that reason: it may be slow, but it'll always work, no matter how big the problem is, and scales better than other algorithms
>

45. @dextorius says about custom allocators:
>Any heap allocation you do from Julia (whenever you create, for instance, a new Vector) is handled by whichever version of malloc Julia uses internally. When I say "a custom allocator" I refer to the ability to instead use a different allocator from the default. In my case, that would mostly be for the purposes of introducing specific memory alignment in some data structures for performance reasons.
This is a very common practice in languages like C/C++/D, especially when it comes to numerical code and GPGPU computing.

46. Chris and the gang say that Shampine is the boss and that I should read about the [Matlab ODE suite](http://people.eecs.berkeley.edu/~wkahan/Math128/ODEsuite.pdf), [Solving DDes in Matlab](http://www.radford.edu/~thompson/RP/dde23.pdf), [IRKC and IMEX solver for stiff blah balh](http://faculty.smu.edu/shampine/IRKC.pdf).
Duly noted.

47. First attempt at a PR. [#21208](https://github.com/JuliaLang/julia/pull/21208)
Github hurts. Remember to add tests. skip CI until last PR.

48. [Wong-Zakai theorem](http://www.hairer.org/papers/WongZakai.pdf) for PDEs - 57 page paper.

49.
```
This is cool code from base/test/linalg/generic.jl
> # test ops on Numbers
for elty in [Float32,Float64,Complex64,Complex128]
    a = rand(elty)
    @test trace(a)         == a
    @test rank(zero(elty)) == 0
    @test rank(one(elty))  == 1
    @test !isfinite(cond(zero(elty)))
    @test cond(a)          == one(elty)
    @test cond(a,1)        == one(elty)
    @test issymmetric(a)
    @test ishermitian(one(elty))
    @test det(a) == a
end
```

50. @KristofferC did an [awesome talk](https://www.youtube.com/watch?v=30TUEhbGmuc) on the FEM landscape. Take note of storing plots at 20mins in.
PETSc holy grail of what?

51. [Jeff B](https://www.youtube.com/watch?v=JoRn4ryMclc) basic talk 2013 on Julia parallelism

52. [ERMAGERD cluster manager and parallel julia!](https://www.youtube.com/watch?v=XJAQ24NS458)

### 27/03/17

37. doing A & 1 will give you booleans

38. Oracle machine is used for complexity proofs in CS

39. Intel new Optane memory announced - SSD killer?

40. * No mode(A) in base Julia?


34. `whos()` tells you what is in memory.

35. `join([string arrays], "delim")` is my friend

36. Hackerrank: 211,207

### 25/03/17

28. Julia Multithreading in the works but is kept secret.

29. `_foo` makes a handy internal implementation that uses dispatch. it means don't rely on it.

30. FINALLY solved Hackerank 2. FINALLY!

```
readline(STDIN)
array = [parse(Int,s) for s in split(string(readline(STDIN)))]
print(mapreduce(x -> x, +, array))
```

31. Chat says Julia is slow at strings and dynamic operations.

32. Aliasing - @mbauman says
""" Yes, two objects alias each other when they point to the same memory region. In general, compilers must pessimistically assume that a write to object A may affect object B.
So after writing to object B, it must re-load anything from object A before going on
since it might have changed
What @mbauman said, with the corollary that this forced assumption inhibits a great many optimizations with regards to reordering code, vectorizing, etc.

33. Run time library Julep - BIG deal if you can setup a native Float. GPUs use Float16 - order of magnitude difference or greater.

### 24/03/17

25. [Method of Lines](https://en.wikipedia.org/wiki/Method_of_lines) discretize one dimension in a PDE, solve.

26. Julia's GC makes ultra-low-latency a non-starter.

27. Juleps are big big development projects - Julia enhancement proposals.

### 23/03/17

19. Haswells are new chip design methodologies to improve efficiency of computation and power savings?

21. Skylake is an even better version.

22. Clock multiplying is basically doing more instructions within the same clock cycle

23. Randall Leveque made amazing Claw software for Hyperbolic systems

24. `ack` is old school tool for refactoring code = reformatting so as to facilitate everything.

25. AVX are super compiler magics to super speed up compiler instructions. Basically SIMD.

### 22/03/17

18. Added this to my to dos... [some MIT book Jeff and gitter really like](https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-4.html#%_toc_start), [Julia manual](https://upload.wikimedia.org/wikipedia/commons/2/2e/Julia.pdf)
[Julia for HPC]

19. `@edit` takes you to the definition of the source code ! :D

20. 27:41 `...` after a tuple means extract those arguments and call function again on those arguments.

21. 44:21 - a generated function acts on the typed AST!

### 19/03/17

12. @KristofferC says
For bisecting, you can write a small script that passes / fails depending on what you are testing for, and then let git automatically bisect the whole way to the correct commit, see https://lwn.net/Articles/317154/

13.  Tuple types are covariant in their parameters: Tuple{Int} is a subtype of Tuple{Any}.
```
julia> typeof((1, 0.1)) <: NTuple{2}
false

julia> typeof((1, 0.1)) <: NTuple{2,Any}
true

julia> typeof([1,2]) <: Vector
true

julia> typeof([1,2]) <: Vector{Any}
false

julia> Tuple{Int,Int} <: NTuple{2}
true

julia> Tuple{Int,Float64} <: NTuple{2}
false

julia> Tuple{Int,Float64} <: NTuple{2,Any}
true
```

14. Function inputs are tuple types, so they have to be covariant
e.g. if you have f(::Int, ::Any) and call f(1, 2), dispatch happens based on whether Tuple{Int, Int} <: Tuple{Int, Any}

15. Typevars always get "filled" with concrete types when subtyping, which is another way of saying that {T,T} where T asserts that both type parameters are equal
Otherwise, f(x::T, y::T) where T would be the same as f(x::Any, y::Any)
Since you could have T = Any

16. [Subnormals are the devil](https://discourse.julialang.org/t/50x-speed-difference-in-gemv-for-different-values-in-vector/2755)

17. [Help out CUDANative.jl](https://github.com/JuliaGPU/CUDAnative.jl/blob/master/TODO.md)
[Help out Dagger.](https://github.com/JuliaParallel/Dagger.jl)
[Help out TensorOperations](

### 18/03/17

7. Got Git Kraken. Told sister about it. Edit: 30/03 / [ohshitgit.com](ohshitgit.com)

8. Gitter says
`function f(x)
    function g()
        if is(x, Int)
            1
        elseif
            0
        end        
    end
    g()
end`

is the same as `type G{T} x::T end; g = G(x)` and defining call on `::G` ... @MikeInnes

9. @testnowarn @example

10. @mbauman says NTuple{N} is now the same as NTuple{N,T} where T (this means where T <: Any)

11. [git bisecting](https://git-scm.com/docs/git-bisect) finds an offending commit. Builds may take time. Beware...

### 17/03/2017

0. Read Jeff's PhD thesis. Julia's heart/subtyping algorithm still freakin' hyerogliphical. Will return. Edit: 30/03/17 - subtyping algo explained a bit more in his Julia Internals Juliacon 2015 talk.

 0.5.  Ran Valgrind on all Julia, ValidatedNumerics.jl, and TaylorSeries.jl source code. No memleaks. Nice.

1. @ChrisRackaukas Bikeshedding - arguing about syntax

"""
#The term was coined as a metaphor to illuminate Parkinson’s Law of Triviality. Parkinson observed that a committee whose job is to approve plans for a nuclear power plant may spend the majority of its time on relatively unimportant but easy-to-grasp issues, such as what materials to use for the staff bikeshed, while neglecting the design of the power plant itself, which is far more important but also far more difficult to criticize constructively. It was popularized in the Berkeley Software Distribution community by Poul-Henning Kamp[1] and has spread from there to the software industry at large.
"""

2. tests might be "bleeding"
i.e. one test is setting a value that changes another test.

3. The fantastic @ChrisRackaukas post on [Software Engineering practices](http://www.stochasticlifestyle.com/finalizing-julia-package-documentation-testing-coverage-publishing/) for Julia.

4. [Github hooks](http://biorxiv.org/content/biorxiv/early/2016/05/13/048744.full.pdf) (in Rule 5) are scripts that run everytime a push happens, so that Continuous Integration and Testing can happen. Travis CI for UNIX, Appveyor for UNIX.

5. Use Digital Object Identifiers to cite source code/databases. Zenodo is recommended, or Figshare.

6. Use Gists that are secret from search engines!


# PathToPerformance
__TO DOS__

## CS Courses
1. [Stanford SQL](https://lagunita.stanford.edu/courses/DB/2014/SelfPaced/about)
2. [Numerical Analysis - Homer Reid](http://homerreid.dyndns.org/teaching/18.330/#Programming)
3. [IEEE 754 FLOP arithmetic](http://sistemas.fciencias.unam.mx/~gcontreras/joomla15/tmp/Numerical_Computing_with_IEEE_Floating_Point_Arithmetic.pdf) with exercises!
4. Geometric Numerical Integration - Ernst Hairer et al
5. Numerical Linear Algebra - Trefethen

## CS Papers and books
1. [Avoid false sharing - Intel](https://software.intel.com/sites/default/files/m/d/4/1/d/8/3-4-MemMgt_-_Avoiding_and_Identifying_False_Sharing_Among_Threads.pdf)
2. [Geometric Numerical Integration - Hairer]
3. [PDF scheduling and multithreading bonanza as per #21017](http://www.cs.cmu.edu/~chensm/papers/ConstructiveCacheSharing_spaa07.pdf)
4. [Deep Learning MIT]
5. [some MIT book Jeff and gitter really like](https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-4.html#%_toc_start)

## Julia!
1. [Tony Kelman's](https://www.youtube.com/watch?v=XKdKdfHB2KM) talk on CI, and his [notebook](https://nbviewer.jupyter.org/github/tkelman/JuliaCon2016workshop/blob/master/Workshop.ipynb)
2. [Chris Rackauckas](www.stochasticlifestyle.com/finalizing-julia-package-documentation-testing-coverage-publishing/) full CI tips implementation on thesis.
3. [His other awesome post](http://www.stochasticlifestyle.com/modular-algorithms-scientific-computing-julia/) and [this one](www.juliabloggers.com/7-julia-gotchas-and-how-to-handle-them/)
4. [Dear lord Chris you are a machine](http://www.stochasticlifestyle.com/finalizing-julia-package-documentation-testing-coverage-publishing/)
5. [To Lisp or not to lisp - Stefan Karpinski](https://www.youtube.com/watch?v=dK3zRXhrFZY)
6. [CUDA, Julia, and Deep Learning](https://devblogs.nvidia.com/parallelforall/mocha-jl-deep-learning-julia/)
7. [Julia - HPC book]
8. Arch D robison parallel computing book
9. Study Julia source code from Plots.jl and DifferentialEquations.jl

## Parallel Julia
1. [Workshop 1](https://www.youtube.com/watch?v=euZkvgx0fG8)
    update to Arch Robinson?

Econ/Finance
1. https://lectures.quantecon.org/jl/finite_markov.html
2. http://aviks.github.io/Ito.jl/process.html

## Pkgs to Know.
1. Plots.jl
2. https://github.com/JuliaParallel/Dagger.jl
3.https://github.com/IntelLabs/ParallelAccelerator.jl
4.https://github.com/pluskid/Mocha.jl
5. https://github.com/IntelLabs/HPAT.jl
6. https://juliaplots.github.io/
Spark
1. [Workshops 1 ](https://www.youtube.com/watch?v=OheiUl_uXwo&index=1&list=PL-x35fyliRwhDv3g1dae8v2F6-_bzBfGK)
2. [Workshop 2](https://www.youtube.com/watch?v=VWeWViFCzzg)
3. [Workshop 3]



Julia to do's
1. Jeff Bezanson - theory update on Julia's type inference algorithm since conception
2. Latex in Documenter?
3. WTF is a tuple
  bitstype
    bufferio
    AbstractArray
    generalizedcartesianindex
4. Julia Typesupertree
5. WTF are _xxx_ calls?
6. Lifting
7. Bottom is the least common Type
8. promotion rules
9. splatting = pass a structure of n values as n separate args to a function
10. linear algebra matrix type definitions andreas noack
11. Introducing Julia/types
12. 100 julia exercises
13. numerical recipes in Julia
14. distributed recipes in Julia
15. metaprogramming exercises - https://discourse.julialang.org/t/simple-metaprogramming-exercises-challenges/731

## Altruism
1. Help Sanders
2. Help Benet
3. Help Mendezs
  matrix playground - subtypes(AbstractArray)
4. read floating point standard 754 and exercicses
5. read 1788 standard and exercicses
6. splatting
7. matrix playground
