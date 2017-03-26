# PathToPerformance
__TO DOS__

CS Courses
1. [Stanford SQL](https://lagunita.stanford.edu/courses/DB/2014/SelfPaced/about)
2. [Numerical Analysis - Homer Reid](http://homerreid.dyndns.org/teaching/18.330/#Programming)
3. [IEEE 754 FLOP arithmetic](http://sistemas.fciencias.unam.mx/~gcontreras/joomla15/tmp/Numerical_Computing_with_IEEE_Floating_Point_Arithmetic.pdf) with exercises!
4. Geometric Numerical Integration - Ernst Hairer et al
5. Numerical Linear Algebra - Trefethen

CS Papers and books
1. [Avoid false sharing - Intel](https://software.intel.com/sites/default/files/m/d/4/1/d/8/3-4-MemMgt_-_Avoiding_and_Identifying_False_Sharing_Among_Threads.pdf)
2. [Geometric Numerical Integration - Hairer]
3. [PDF scheduling and multithreading bonanza as per #21017](http://www.cs.cmu.edu/~chensm/papers/ConstructiveCacheSharing_spaa07.pdf)
4. [Deep Learning MIT]
5. [some MIT book Jeff and gitter really like](https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-4.html#%_toc_start)

Julia!
1. [Tony Kelman's](https://www.youtube.com/watch?v=XKdKdfHB2KM) talk on CI, and his [notebook](https://nbviewer.jupyter.org/github/tkelman/JuliaCon2016workshop/blob/master/Workshop.ipynb)
2. [Chris Rackauckas](www.stochasticlifestyle.com/finalizing-julia-package-documentation-testing-coverage-publishing/) full CI tips implementation on thesis.
3. [His other awesome post](http://www.stochasticlifestyle.com/modular-algorithms-scientific-computing-julia/) and [this one](www.juliabloggers.com/7-julia-gotchas-and-how-to-handle-them/)
4. [Dear lord Chris you are a machine](http://www.stochasticlifestyle.com/finalizing-julia-package-documentation-testing-coverage-publishing/)
5. [To Lisp or not to lisp - Stefan Karpinski](https://www.youtube.com/watch?v=dK3zRXhrFZY)
6. [CUDA, Julia, and Deep Learning](https://devblogs.nvidia.com/parallelforall/mocha-jl-deep-learning-julia/)
7. [Julia - HPC book]

Parallel Julia
1. [Workshop 1](https://www.youtube.com/watch?v=euZkvgx0fG8)
    update to Arch Robinson?

Econ/Finance
1. https://lectures.quantecon.org/jl/finite_markov.html
2. http://aviks.github.io/Ito.jl/process.html

Pkgs to Know.
1.
2. https://github.com/JuliaParallel/Dagger.jl
3.https://github.com/IntelLabs/ParallelAccelerator.jl
4.https://github.com/pluskid/Mocha.jl
5. https://github.com/IntelLabs/HPAT.jl
6. https://juliaplots.github.io/
Spark
1. [Workshops 1 ](https://www.youtube.com/watch?v=OheiUl_uXwo&index=1&list=PL-x35fyliRwhDv3g1dae8v2F6-_bzBfGK)
2. [Workshop 2](https://www.youtube.com/watch?v=VWeWViFCzzg)
3. [Workshop 3]

__SHIT I'VE LEARNED__ Scientific Day Logger

34. `whos()` tells you what is in memory.
35. `join([string arrays], "delim") is my friend
36. Hackerrank: 211,207


25/03/17
28. Julia Multithreading in the works but is kept secret.
29. `_foo` makes a handy internal implementation that uses dispatch. it means don't rely on it.
30. FINALLY solved Hackerank 2. 
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
33. Run time library Julep - BIG deal if you can setup a native Float. GPUs use 
Float16 - order of magnitude difference.




24/03/17
25. [Method of Lines](https://en.wikipedia.org/wiki/Method_of_lines) discretize one dimension in a PDE, solve.
26. Julia's GC makes ultra-low-latency a non-starter.
27. Juleps are big big development projects - Julia enhancement proposals.




23/03/17
19.Haswells are new chip design methodologies to improve efficiency of computation and power savings?
21. Skylake is an even better version.
22. Clock multiplying is basically doing more instructions within the same clock cycle
23. Randall Leveque made amazing Claw software for Hyperbolic systems
24. `ack` is old school tool for refactoring code = reformatting so as to facilitate everything.


22/03/17
18. Added this to my to dos... [some MIT book Jeff and gitter really like](https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-4.html#%_toc_start)
[Julia manual](https://upload.wikimedia.org/wikipedia/commons/2/2e/Julia.pdf)
[Julia for HPC]

19. `@edit` takes you to the definition of the source code ! :D
20. 27:41 `...` after a tuple means extract those arguments and call function again on those arguments.
21. 44:21 - a generated function acts on the typed AST!


19/03/17

12. @KristofferC says
For bisecting, you can write a small script that passes / fails depending on what you are testing for, and then let git automatically bisect the whole way to the correct commit, see https://lwn.net/Articles/317154/

13.  Tuple types are covariant in their parameters: Tuple{Int} is a subtype of Tuple{Any}.
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

14. Function inputs are tuple types, so they have to be covariant
e.g. if you have f(::Int, ::Any) and call f(1, 2), dispatch happens based on whether Tuple{Int, Int} <: Tuple{Int, Any}

15. Typevars always get "filled" with concrete types when subtyping, which is another way of saying that {T,T} where T asserts that both type parameters are equal
Otherwise, f(x::T, y::T) where T would be the same as f(x::Any, y::Any)
Since you could have T = Any

16./ [Subnormals are the devil](https://discourse.julialang.org/t/50x-speed-difference-in-gemv-for-different-values-in-vector/2755)

17. [Help out CUDANative.jl](https://github.com/JuliaGPU/CUDAnative.jl/blob/master/TODO.md)
[Help out Dagger.](https://github.com/JuliaParallel/Dagger.jl)
[Help out TensorOperations](



18/03/17
7. Got Git Kraken. Told sister about it.

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

11. [git bisecting](https://git-scm.com/docs/git-bisect) finds an offending commit.
Builds may take time. Beware...





17/03/2017
0. Read Jeff's PhD thesis. Julia's heart/subtyping algorithm still freakin' hyerogliphical.
Will return.

 0.5 Ran Valgrind on all Julia, ValidatedNumerics.jl, and TaylorSeries.jl source code.
 No memleaks. Nice.

#1. @ChrisRackaukas Bikeshedding - arguing about syntax

"""
#The term was coined as a metaphor to illuminate Parkinson’s Law of Triviality. Parkinson observed that a committee whose job is to approve plans for a nuclear power plant may spend the majority of its time on relatively unimportant but easy-to-grasp issues, such as what materials to use for the staff bikeshed, while neglecting the design of the power plant itself, which is far more important but also far more difficult to criticize constructively. It was popularized in the Berkeley Software Distribution community by Poul-Henning Kamp[1] and has spread from there to the software industry at large.
"""
2. tests might be "bleeding"
i.e. one test is setting a value that changes another test.

3. The fantastic @ChrisRackaukas post on [Software Engineering practices](http://www.stochasticlifestyle.com/finalizing-julia-package-documentation-testing-coverage-publishing/) for Julia.

4. [Github hooks](http://biorxiv.org/content/biorxiv/early/2016/05/13/048744.full.pdf) (in Rule 5) are scripts that run everytime a push happens, so that Continuous Integration and Testing can happen. Travis CI for UNIX, Appveyor for UNIX.

5. Use Digital Object Identifiers to cite source code/databases. Zenodo is recommended, or Figshare.

6. Use Gists that are secret from search engines!





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








A. Help Sanders
B. Help Benet
c. Help Mendezsdf
  matrix playground - subtypes(AbstractArray)


d. read floating point standard 754 and exercicses
e read 1788 standard and exercicses
f. splatting
g. matrix playground
