# PathToPerformance

__SHIT I'VE LEARNED__ Scientific Day Logger
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