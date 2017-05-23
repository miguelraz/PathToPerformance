
__Stuff I've learned: Annotations on the path to Julia Nirvana__
======================
Scientific Day Logger
---------------------

A trillion points of altruism to Julia's Gitter chat and its benign and helpful netizens.

:shipit:

### 22/05/17

115. Dear god just stumbled onto @eschnett 's twitter. Super cool guy. Need to get a hold of his manual on proper Distributed computing. Also, this link on [modern architectures has to be noted down somewhere](https://us9.proxysite.com/process.php?d=joV9v0%2BWEk1HycjQWBjdi9MLNGsVx213r9Gi0i%2BY8w%3D%3D&b=3)


### 19/05/17

112. A Struct is a Class whose every member is public. A `begin` block introduces a local scope/vars for you to play with :D.

113. Views/subarrays when passed by value make copies and render data as contiguous in memory >>> speeds up calculation if you have a lot of transformations to do!

114. @pure functions only modified their arguments and nothing else, not even globals -- no side effects! Purity leads to ease in parallelization.

### 17/05/17

111. [The problem with threads](https://www2.eecs.berkeley.edu/Pubs/TechRpts/2006/EECS-2006-1.pdf)

### 10/05/17

110. Scribing! @Pualms comes into chat with non-linear conservation laws based on Kurganov and Tadmor and FVol method. @aytekinar discussion is also a great DiffEq user case walkthrough with simple Euler.

### 06/05/2017

107. Rust has some really cool approach to building an common API for pkg dev [socially](https://blog.rust-lang.org/2017/05/05/libz-blitz.html) remember to bring this up after v0.6 release.
@oxinabox and @musm

108. Read [Chris's post about modular Pkg devving](http://www.stochasticlifestyle.com/modular-algorithms-scientific-computing-julia/). Basically, your core package is a metapackage that pulls all the other dependencies together to have a robust and modular API.

109. Vocab: Closures are defining a [function inside a function](http://stackoverflow.com/documentation/julia-lang/5724/closures#t=201705061353044428602). A special case of this is currying, where you call a function and it outputs
more args into itself.
`curry(f,x) = (xs...) -> f(x,xs...)`

110. Notes on DiffEqDevDocs:
# Overview
- Common interface is `solve(prob,alg;kwargs)`.
- JuliaDiffEq is setup in a distributed manner.
- JuliaDiffEq is a metapackage, DiffEqBase pulls the different modules in to work on cool stuff. People can then license/contribute their own algorithms in their own way and make it work in the ecosystem.
- Component solvers are the \*DiffEq (Aaaaach so.)
- Add-on packages are DiffEq\*, which add functionality to the Problem+solve setup.
- To have package join the ecocystem, Pkg has to get into JuliaDiffEq, then algos can move into DiffEqBase.

# Adding Algos
- new problems (new PDE, new type of diffeq, new subclass of problems, etc) problem and solution types should be added to DiffEqBase first.
- After problem and solutions are defined, the `solve` method is implemented. Should accept maximum kwargs, compatibility with Juliatypes must be documented, also in document in DiffEqBenchmarks, DiffEqTutorials

# eg adding new algos to ODEq. with SSPRK22
1. To create a new solver, 2/3 types have to be created. The algo SSPRK22 is used for dispatch, the other ones `SPRK22Cache` for inplace updates and `SSPRK22ConstantCache`.
2. algo gets defined in `algorithms.jl` as `immutable SSPRK22 <: Ordinarry DiffEqAlgorithm end`. It has no First Same As Last property, but derivatives are used for the Hermite interpolations -> only one more function evaluatied. This happens in `alg_utils.jl` like `isfsal(alg::SSPRK22) = true`. Also, order is set as `alg_order(alg::SPRK22) = 2`.
3. export the algo `SSPRK22` to `ODEq.jl`
4. In `caches.jl`, the two cache types are defined. Note*: wtf? Ask Chris.
5. new file `integrators/ssprk_integrators.jl` for both types of caches, the functions `initialize!` and `perform_step!` are defined there.
6. Tests are added. New file `test/ode/ode_ssprk_tests.jl` is created and includes tests/runtests.jl via `@time @testset "SSPRK Tests" begin include("ode/ode_ssprk_tests.jl") end`
7. Addendum, regression tests for the dense output are added in `test/ode/ode_dense_tests.jl`
8. Deets [are here](https://github.com/JuliaDiffEq/OrdinaryDiffEq.jl/pull/40)
Summary:
Create types for your algo and 2 caches. Define the immutable in `algorithms.jl`, maybe `alg_utils.jl` applies. Export in ODEq.jl. Define the 2 caches in `caches.jl` because magics. in `integrators/ssprk_integrators.jl`, you define `initialize!` and `perform_step!` for both types of caches. Add super cool tests. Add dense tests.
i.e.,
```
dts = 1.//2.^(8:-1:4)
testTol = 0.2

prob = prob_ode_linear

sim = test_convergence(dts,prob,SSPRK22())
@test abs(sim.𝒪est[:final]-2) < testTol

prob = prob_ode_2Dlinear

sim = test_convergence(dts,prob,SSPRK22())
@test abs(sim.𝒪est[:final]-2) < testTol
```
change `dts ` around, and plot to make sure things are legit == should be smooth to the eye!

Also, probs copy a test from [the dense output](https://github.com/JuliaDiffEq/OrdinaryDiffEq.jl/blob/master/test/ode/ode_dense_tests.jl#L65).

> for making sure that the dense output is good. Just follow what's there for RK4 or the Midpoint method. You'll need to adjust the numbers on the test to match how close the fit should be (this is a regression test). Before setting the numbers, make sure you plot it with the interpolation (should be the default plot(sol). Check it by eye: if it's not smooth then there's an issue in the interpolation.

# Developing a new problem

Define new problem types to specialize dispatch. New diffeqs, pdes, special subclasses of diffeqs.
1. Make a new `DEProblem` and new `DESolution`. These belong in DiffEqBase and should be  exported. The `DEProblem` must hold all mathematical info, including meshing in both space and time, and `DESolution` should hold all info for the solution. That's all you need to get a `solve(::DEProblem,alg;kwargs)` which takes problem, spits solution.
2. Does it make sense in a hierarchy? Make a promotion structure. Cool! ODEProbs are DAEProbs, this way, methods for DAES can solve ODEs by promotion (like DASSL provides BDF method).
3. Add plotting via a recipe to the the solution type.
4. Add tests with `DETestProblem` and `DETestSolution` which holds the analytical solution, and extend `appxtrue!` in DiffEqDevTools. To check algo works, add a dispatch for `test_convergence` which makes a `ConvergenceSimulation` type. This already has a recipe, plotting is therefore embedded. Your problem can take in a true solution, and has a field `errors` which is a dictionary of symbols for the different error estimates (L2, L inf, etc.).
5. Update docs to include new problem types.
Summary:
make new types for problem and solution. solution needs all math info like meshing space and time. create promotion structure for types if logical. add plotting, tests, and error metrics. update docs.

# DiffEq Internals

Easy way to start is to develop a new solver algo.


### 05/05/2017

99. Chris on DiffEq roadmap and advantages of DiffEq global sensitivity methods
> I wouldn't count number of packages as much as I would cound the number of packages with binary dependencies
these are all pure Julia, all the way down
so they should work anywhere
Do any of the DAE solvers support the callback interface?
Only if you count + projection
it wouldn't be hard to implement the mass matrix stuff in the Rosenbrock methods though
so that would be a DAE solver + callback interface
but no
IDA, dassl, and daskr do not implement the callback interface
Sundials and DASKR have a hard problem with garbage control: they need a custom allocator so that way Julia's GC can know their size. To me, it's easier just to implement native Julia DAE solvers than to handle that...
Dassl.jl just needs love.
but I'm thinking of starting over, extending OrdinaryDiffEq.jl in that direction, instead of working on DASSL.jl
so...
that's where I am at with that
I would need a good reason to push there though, since I don't generally use DAEs in my research, which makes it hard to justify the work
Drayton Munster @dwmunster May 01 12:58
extending OrdinaryDiffEq.jl in that direction
In the direction of implementing native Julia solvers?
Christopher Rackauckas @ChrisRackauckas May 01 12:58
multistep methods
OrdinaryDiffEq.jl is all one-step methods right now, but it already is setup to do multistep methods, but I haven't done those yet
I think it's probably just better to recreate the multistep methods anyways: the old Gear methods (LSODE/Sundials/DASKR etc., they are all actually the same code) are super convoluted and really need to just be restarted from scratch
it's all time management though: since Sundials exists I put that off for other things
it wouldn't be hard to setup the passing of the mass matrix to radau though, and that's a very good DAE method, but that doesn't have callbacks
yeah, Rosenbrock is your best bet right now
I'm releasing my next roadmap in about a week, after Google Summer of Code is announced and DiffEq 2.0 is out
but essentially, my next focus is on tools for PDEs, symplectic methods, higher order SDE methods, and stiff ODEs
DAEs written in mass matrix format come for free out of the stiff ODE stuff, at least in many cases.
Christopher Rackauckas @ChrisRackauckas May 01 13:03
Then I believe 4.0 would be the big push for a new multistep NDF/BDF/Adams implementation
but honestly, those are slightly overrated: they're only useful if the function evaluation is very expensive and you don't have many events (they have to restart from Euler, so tons of events will slow them down even in the case where they do best. Unless it's a huge PDE discretization, it's kind of a toss-up between these and implicit RK methods like Radau)
I'll have a blog post explain this all, but really it was
1.0 = core (good common interface to ODE/SDE/DAEs with basic event handling)
2.0 = infrustructure (all of the bells and whistles: find out how to resize, completely bonkers event handling, abstract types, split problems, interpolations, APIs, solution handling, etc.)
3.0 = PDEs (toolboxes for making PDEs easy, and some standard discretizations)
4.0 = algorithms (now implementing algorithms is easy, and so just do it the standard way and everything else like event handling is free)
robindenhardteriksson @robindenhardteriksson May 02 09:29
@ChrisRackauckas I saw that you were interested in integrating some global sensitivity analysis into Diffeqs. I was going to move over some matlab stuff I had previously done for this into Julia. What's the best place to discuss this?
Christopher Rackauckas @ChrisRackauckas May 02 09:30
right here
robindenhardteriksson @robindenhardteriksson May 02 09:32
Perfect. What is the advantage you see in having this in DiffEqs rather than another package?
Christopher Rackauckas @ChrisRackauckas May 02 09:33
not much. But if it's in JuliaDiffEq, then the members of JuliaDiffEq could help with the maitanance.
But this could be built outside of DiffEq without a problem
robindenhardteriksson @robindenhardteriksson May 02 09:35
I was just thinking about the numerical advantages. With local sens, you've already got access to jacobians if you're implementing this in DiffEqs. But from the global sens methods I know, none of that kind of info is required
Christopher Rackauckas @ChrisRackauckas May 02 09:36
if you implement it on the DiffEq interface, than any underlying numerical method can be used
I think the ability to swap between BDF methods and high order RK methods to match the problem is where the gains would be had
robindenhardteriksson @robindenhardteriksson May 02 09:38
Ah, you mean depending on the resolution you're looking for with your global sens? ie. if a parameter only has a small effect you could switch methods to better resolve this effect
Christopher Rackauckas @ChrisRackauckas May 02 09:39
yes and things like that
and also you could estimate models with events
robindenhardteriksson @robindenhardteriksson May 02 09:39
models with events?
Christopher Rackauckas @ChrisRackauckas May 02 09:40
yes
like special behavior on zero-crossings
like a bouncing ball
discontinuities
robindenhardteriksson @robindenhardteriksson May 02 09:40
right
Christopher Rackauckas @ChrisRackauckas May 02 09:40
the DiffEq interface also makes the extension to stochasticity easy
I'm not sure what the other option would really be anyways. What else would you build it on top of?
robindenhardteriksson @robindenhardteriksson May 02 10:10
The quick-and-dirty GSA i had done was pretty much by itself. You would have to write a sensitivity function, which would compute outputs from inputs from the GSA, this is where you would solve models. You would define an input space, then it would do some sampling and return different sensitivity indices
Christopher Rackauckas @ChrisRackauckas May 02 10:13
but what you were sampling was solutions of a diffeq solver with different parameters?
robindenhardteriksson @robindenhardteriksson May 02 10:13
mostly yes
Christopher Rackauckas @ChrisRackauckas May 02 10:14
yeah
I was just thinking of making it so that way it can take some diffeq problem and some diffeq algorithm, and use that internally for the sampling
if you have an idea for making this encompass more general models, that works too
robindenhardteriksson @robindenhardteriksson May 02 10:16
It would be a nice addition to have it integrated, right alongside the local SA
Were you thinking of implementing it in a similar way to the current local SA?
Christopher Rackauckas @ChrisRackauckas May 02 10:17
no
local SA is a much different algorithm in implementation
that builds an extended diffeq and solves that
I don't think you need to do any modifications like that for global SA. As you said, you can just sample solutions at different parameters.
robindenhardteriksson @robindenhardteriksson May 02 10:19
right, I didn't really ask what I meant to. I know the algorithms work differently, I was thinking of more abstractedly, in terms of receiving an ODEProblem or ParametrizedFunction and then working on that to return sensitivity indices.
Christopher Rackauckas @ChrisRackauckas May 02 10:19
yes
that's the plan
robindenhardteriksson @robindenhardteriksson May 02 10:20
I thought I'd read up on the current local SA to get an idea how the global would be done
Christopher Rackauckas @ChrisRackauckas May 02 10:20
I'm not sure that would actually be too helpful
global SA is actually closer to parameter estimation I think
in how it's all based on sampling solutions
most of what's done for local SA would likely be unnecessary for global SA
robindenhardteriksson @robindenhardteriksson May 02 10:21
Okay. Translating and writing the algorithms I'm fine with, as a user it's just the internals of DiffEq which I'm not familiar with
Christopher Rackauckas @ChrisRackauckas May 02 10:21
I don't think you need to use the internals at all.
At a high level, if I remember the Morris algorithm correctly its:
1) Take a set of parameters and solve the diffeq
2) Change the set of parameters around according to some algorithm, solve again
3) Repeat 1 and 2, saving data along the way.
robindenhardteriksson @robindenhardteriksson May 02 10:23
You think it's as simple as receiving an ODEProblem, solving it with a bunch of sampled parameters and returning sensitivity indices?
beat me to it
Christopher Rackauckas @ChrisRackauckas May 02 10:24
I will say I haven't implemented it yet so I am not intimitely familiar with all of the details
but that's what it seemed like it was from a first read.
robindenhardteriksson @robindenhardteriksson May 02 10:25
Yeah, that's basically it, sampling parameters and re-calculating a model output based on new samples
Christopher Rackauckas @ChrisRackauckas May 02 10:27
so yeah, I'm not sure any of the diffeq internals are really needed. It should be standard diffeq usage (solve diffeq and change parameters), then turned into a library function to make it easy for others to use it.
robindenhardteriksson @robindenhardteriksson May 02 10:29
Is there an example I can base myself on, or a set of principles for making it a library function?
Christopher Rackauckas @ChrisRackauckas May 02 10:31
The main principle is that it should try to be as efficient as possible, yet agnostic to the type of problem it's solving (ODE/SDE/DDE/DAE/etc.) and the algorithms it's using to solve it (it should be able to swap out OrdinaryDiffEq methods for Sundials methods etc. as much as possible)
but I think it's usually best to just start small
make a method which only works for ODEs, and then generalize later
I prefer multiple consecutive PRs, each adding one detail, to one giant PR that is supposed to solve the whole problem.
(of course, you don't have to go all the way. You could write it to ODEs and PR that and be off on your merry way. Then that gives me or someone else a starting point to work from later)
robindenhardteriksson @robindenhardteriksson May 02 10:37
Okay. In any case, I'm going to be implementing several GSA methods into Julia for my own use (ODEs for now, possibly stochastic later). I'd be more than happy to help out and possibly contribute.
From which repo should I branch and then submit PRs?
Christopher Rackauckas @ChrisRackauckas May 02 10:38
DiffEqSensitivity.jl
you'll see it's a very tiny library, just with the local SA stuff
it's in dire need of love :smile:
robindenhardteriksson @robindenhardteriksson May 02 10:39
yeah, I saw the code isn't very long. Does that actually contain everything to do local SA?
Christopher Rackauckas @ChrisRackauckas May 02 10:40
yeah
robindenhardteriksson @robindenhardteriksson May 02 10:41
that's some nice and concise code there
Christopher Rackauckas @ChrisRackauckas May 02 10:42
I mean, local SA is just appending to the diffeq some extra states for solving the SA equations simultaniously
it's not an adjoint method or anything fancy (though I do wish to get there)
robindenhardteriksson @robindenhardteriksson May 02 10:48
true, not overly complex, but still nice
Well thanks for the time to chat. I'll make some basic GSA stuff first, and will probably be back at some point with some more questions.

100.
julia> @doc clamp                                                                                   clamp(x, lo, hi)                                                                                                                                                                                    Return x if lo <= x <= hi. If x < lo, return lo. If x > hi, return hi. Arguments are promoted     to a common type. Operates elementwise over x if x is an array.                                                                                                                                     
julia> clamp([pi, 1.0, big(10.)], 2., 9.)                                                         3-element Array{BigFloat,1}:                                                                       3.141592653589793238462643383279502884197169399375105820974944592307816406286198                  2.000000000000000000000000000000000000000000000000000000000000000000000000000000          9.000000000000000000000000000000000000000000000000000000000000000000000000000000

101. On Plots.jl design
> Michael Krabbe Borregaard @mkborregaard 00:58
No @sbromberger the ecosystem is quite solid. PlotRecipes, on the other hand, is fragile. That is because the very purpose of PlotRecipes is to hold those plotting recipes that require dependencies on other packages, exactly to separate those dependencies from the rest of the ecosystem. This means that PlotRecipes fails every time one of the dependencies fail - in this case both bugs in PlotRecipes come through NetworkLayouts.
But that doesn't affect the rest of the functionality of the Plots ecosystem.
The most solid approach is for downstream packages to not rely on PlotRecipes but to depend on RecipesBase and put the plotting functionality inside the package that defines the types. That will clearly keep all bugs to the package itself. Maybe it's worth considering something like that for LightGraphs? The graph functionality in PlotRecipes itself is general and not restricted to LigthGraphs, so maybe even a small GraphRecipes package residing in the Graphs organization?

102. Compatibility [is hard. Very hard](https://github.com/JuliaLang/Juleps/issues/3)
Read springoff issues 2 and 3.

103. @sbromberger uses @inferred and `using testsets` all over to help find regressions and such.
@Evizero had some [good recommendations](https://discourse.julialang.org/t/why-wouldnt-one-want-to-use-inferred-in-package-tests/2776) about its usage in his [JuliaML UnitTests](https://github.com/JuliaML/LossFunctions.jl/blob/master/test/tst_api.jl#L30-L33)

104. @ChrisRackauckas on shadowing. Refactoring code ain't as easy as it looks...
when you create a new function which matches the name of another
so if you're in a package, and you define a function cycle, it will shadow Base.cycle
your local scope will now act like Base.cycle didn't exist, and all of its dispatches didn't exist: just the ones you define.
the way that import works is very weird though
import DiffEqBase: DiffEqDiffTools.get_du
will import DiffEqDiffTools.get_du instead of DiffEqBase.get_du
which are two different functions: DiffEqBase.get_du is user-facing and part of the integrator interface
DiffEqDiffTools.get_du is backend only, part of the differentiation tools (probably should be re-named so that way this clash isn't even possible)

105. Nugget: to copy over your past Julia version, copy the REQUIRE file hidden in ~.julia
If moving around dependencies, don't forget to import or delete from REQUIRE as appropriate.

106. Vocab: Refactoring - moving code around. Aesthetic and Quality of Life but not functional changes.
Linter - Cool program that tells you if script will compile before compiling, usually with little color flags.

107. @oxinabox shows [why the for loop iterator](https://github.com/JuliaLang/julia/issues/6484) is the way it is.
`for (x, y) in zip(xs, ys)`


### 04/05/2017

96. [Fuck.](https://summerofcode.withgoogle.com/organizations/5642180010967040/?sp-page=2#!)

97. Chris goes all out on DiffEq philosophy and what separates it from the others
> I think the main things are:
1) Refinement of standard tools (performance and new algorithms)
2) Integrated analysis (parameter estimation, uncertainty quanitifcation)
3) Expanded problem domain (stochasticity, discrete stochastic jump equations, random ordinary differential equations, etc.)
Most of the ecosystems before focused on just solving ODEs with adaptive timestepping
In fact, the vast majority of codes were the same wrapped Fortran codes (dopri, Sundials, and LSODA which is actually just an old version of Sundials)
however, those were all written in the 80's and 90's
and there has been a lot of research, not to mention a small change in computer architecture, since that happened
so along the lines of one: use newer algorithms, make them internally SIMD and multithreadbrom, etc.
along the lines of two: there have been some "addons" or external software in MATLAB for doing this, but it required "choosing" a specific type of ODE solver. Now, you can give it generically any DE solver for any kind of DE, and you can do extended analysis on it with the built-in tools
and 3, there really isn't a comprehensive suite which handles the wide variety of differential equations
MATLAB does ODEs, DAEs and DDEs (delay differential equations). BVPs too
some codes here and there do versions of tha tas well
Sundials and thus SciPy does ODEs and DAEs, then they have a separate wrapper for BVPs
R wraps essentially the same codes as SciPy
none of these really handle SDEs
Christopher Rackauckas @ChrisRackauckas 12:55
and the specialized extra packages that do handle SDEs are not well maintained and don't implement many algorithms
so definitely including random equations (RODEs, SDEs) is unique.
Then tying this all to PDEs
Of course, we wrap all of the same algorithms the other suites do, but we don't use them as the core. We use them as bait in benchmarks
And I think that's essentially the summary
Christopher Rackauckas @ChrisRackauckas 12:56
If you look at some extended diffeq feature in another language
say
parameter estimation
you can pull up how to do it in Python
http://stackoverflow.com/questions/11278836/fitting-data-to-system-of-odes-using-python-via-scipy-numpy
http://adventuresinpython.blogspot.com/2012/08/fitting-differential-equation-system-to.html
but if you want to do it in Julia, we have a built in function that does exactly what the top searches are doing
http://docs.juliadiffeq.org/latest/analysis/parameter_estimation.html#lm_fit-1
but recommend you don't use it because it's a really bad method, and instead point you to more advanced methods
Seeing things like that (everyone re-implementing Levenburg-Marquedt parameter estimation for each new project, instead of developing a suite of well-tested more advanced methods) pisses me off so much that I had to do it.

98. MCMC and DiffEq
>
@jamesonquinn they're actually very different
DiffEq usually isn't about data
it's about models
is simulating trajectories of a class of nonlinear models which just happen to describe scientific phenomena really well.
So to a statistician, you can think of DiffEq as just an entire library of scientifically interesting nonlinear models
Parameter estimation of differential equation is the question: what about the model needs to be true in order to fit data?
One example of this in statistics (under different words) is nonlinear mixed effects models.
But generally, it's defining some optimization problem to solve, and finding out the parameters for the model (friction coefficients, chemical reaction rates, etc.) such that the timewise trajectories you get out of the simulations match the realistic data.
These converge when you start to talk about these methods
since some of the most common methods for finding parameters are Bayesian methods and MCMC
but at that point, you're almost away from diffeqs, essentially making the assumption "okay we can simulate diffeq models, and using the results of simulations vs data ..."
but actually, the vast majority of DiffEq is methods for simulating the diffeqs
Christopher Rackauckas @ChrisRackauckas 18:22
And that's why I am interested in your work: I want MCMC tools to apply at the end of the stack here

### 03/05/2017

94. Found a super handy guide for [finite difference methods as a review](http://www.colorado.edu/amath/sites/default/files/attached-files/introduction_to_finite_differences_3.pdf)

95. Read the Fornberg - Calculating weights in finite differences formulas paper. Cool insights by hand.

### 02/05/2017

91. Chris recommends lyx.org for Latex stuff, and we learned about why kwargs are slow and heap allocated arrays.[Some of the design philosophy](http://stackoverflow.com/questions/43731862/why-both-tableau-and-explicit-solver-in-differentialequations-jl) for DiffEqs.jl is here.

92. [Rosenbrocks methods are](https://en.wikipedia.org/wiki/Rosenbrock_methods)
> Rosenbrock methods for stiff differential equations are a family of multistep methods for solving ordinary differential equations that contain a wide range of characteristic timescales.[1][2] They are related to the implicit Runge-Kutta methods[3] and are also known as Kaps-Rentrop methods

93. Read the 3 Shampine Papers, as well as Stroustrup's paper on CS education/curriculum.

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
