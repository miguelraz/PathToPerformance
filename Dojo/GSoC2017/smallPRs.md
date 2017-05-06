### GSoC TODOS

read dev docs
read source code

add unit tests

--------------------
1. Read forward diff docs
examples
2.

---------------
Alright
when this PR is finished (with the unit tests)
the next step will be moving over the current ForwardDiff usage for Jacobian calculations
https://github.com/JuliaDiff/ForwardDiff.jl/issues/218#issuecomment-296227769
essentially explains how it's done
JuliaDiffEq/DiffEqDiffTools.jl#3
together with this issue
You should play around with it, understand what's going on there, and then put in a PR to OrdinaryDiffEq.jl to first simplify the ForwardDiff.derivative calls, then start working on the API for Jacobian stuff (which will be the core of the project, and is essentially what JuliaDiffEq/DiffEqDiffTools.jl#1 describes)
While I say it's the core, I think you can get that part done quite quickly, and then we can move onto the cool stuff
https://github.com/JuliaDiffEq/OrdinaryDiffEq.jl/blob/master/src/integrators/rosenbrock_integrators.jl
https://github.com/JuliaDiffEq/OrdinaryDiffEq.jl/blob/master/src/derivative_wrappers.jl
Those are the only two files contain all of the derivative calculation stuff

Christopher Rackauckas @ChrisRackauckas 02:06
so try and understand what's going on there (the algorithm is the Rosenbrock algorithm from the MATLAB ODE Suite paper from Shampine)

Christopher Rackauckas @ChrisRackauckas 02:17
I opened up a few issues for these next steps
You should start trying to work through them
it will be a little bit difficult at first, since you'll essentially be learning the internals of OrdinaryDiffEq at the same time you learn NLsolve, DiffBase, and ForwardDiff, but please just ask any questions
Together, these changes are not that large so this is more about learning the internals
All of these first steps are to get you to know what the current setup for differention tools are, move them over to DiffTools, and improve them a little bit
After that's all done, then we start on making the Jacobian API
Essentially, JuliaDiffEq/DiffEqDiffTools.jl#7 is the same thing as the Jacobians, except there's no "extra" API, so it's a really self-contained small example starter project for the bigger project.
-------------
Small PRs and upgrades

new series recipes
more default plots
benchmarks between different algos
add example IJulia notebooks to DiffEqTutorials
make solvers more efficient
improve docs

STRETCH goals: use MC! ... search for Chris article.
