for n = 1:5, m = 1:5
    println("$n * $m = $(n * m)")
end

arr = rand(1:10, 10)
println(arr)
searched = 4
for (ix, curr) in enumerate(arr)
    if curr == searched
        println("The searched elemente $searched occurs on indexs $ix ")
        break
    end
end

for n in 1:10
    if 3 <= n <= 6
        continue #skip current iteration
    end
    println(n)
end

#Syntax error usually result in LoadError
if code in codes
    println( "This is an accdeptable code")
else
    throw(DomainError())
end

rethrow() is useful to hadn the current exception toa higher calling code level
warn("Something is not right here")

info("Did you know htis?")

type CustomException <: Exception end

#Dangerous code comes in the try bl9ock
#try-catch-finally
#You do htis so that your programs can contintue to run even if the do something bokners

a = []
try
    pop!(a)
catch ex
    println(typeof(ex))
    showerror(STDOUT,ex)
end

ret = try
    a = 4 * 2
catch ex
end

f = open("fi1.txt") #returns an IOStream(<file file1.txt)
try
    #operate on file f
catch ex
finally close(f)
end
x =
9
function funscope(n)
    x = 0 # x ins in the local scope of the function
    for i = 1:n
        x # x is local to the for loop
        x = i + 1
        if (x == 7)
            println("This is the local x in  for : $x ") # = > 7
        end
    end
x
println("this is the local x in fucnscope: $x ") # = > 0
 x = 15
end

funscope(10)
println("This is th eglboal x: $x") #

#if you need local bindings for a variable, use the let block
anon = cell(2)
for i = 1:2
    anon[i] () -> println(i)
    i += i
end
begin
    local x = 1
    let local x = 2
        println(x) # 2
    end
    x
    println(x) # 1
end
begin
    local	x	=	1
    let
        local	x	=	2
        println(x)
    end
    x
    println(x)	#>	1 end
end

# for loops update a variable
i = 0
for i = 1:10
end
println(i)

#comprehensions creat a temporary one
i = 0
[i for i = 1:10]
println(i)

function fib_producer(n)
    a, b = (0,1)
    for i = 1:n
        produce(b)
        a, b = (b, a + b)
    end
end
fib_producer(5)
tsk1 = Task( () -> fib_producer(10))
consume(tsk1)

tsk1 = @task fib_producer(10)

# Chapter 5
Collection types!

c = [1,2,3]
d = [1 2 3]

Array{Int64, 1} == Vector{Int64}
Array{Int64, 2} == Matrix{Int64}

matrix = [1 2; 3 4]

[1 2 ] * [3 ; 4]
Array{Float64, 2}

ma1 = rand(3,5)
ndims(ma1)

size(ma1)

size(ma1,1)

size(ma1,2)

length(ma1)

idm = eye(3)

idm[1:end, 2]

idm[:, 2]

idm[2, :]

idmc = idm[2:end, 2:end]

idm[2, :]

idmc = idm[2:end, 2:end]

idm[2,:] = 0

idm[2:end, 2:end] = [ 5 7 ; 9 11 ]

?sub

ma1 = rand(3,3)

ma2 = rand(3,3)

X = inv(ma1) * ma2

X

X = ma1 \ ma2

X = ma2 / ma1

Tuples are a fixed sized gorup of values separated by commans and optionally surrounded by parentheses
tuples are heterogenous containers
arrays are homogenous containers
('z', 3.13) :: (Char,Float64)

t3 = (5, 6, 7, 8)

for i in t3
    println(i)
end

a, b = t3

a

b

# Dictionariessssssssssss
Keys are unique
Basically a collection of tw-element tuples of the form (key,value)
d1 = [1 => 4.2, 2=> 5.3]
d2 = ["a" => 1, (2,3) => true]

d3 = [:A => 100, :B => 200]

d3[2]
dmus = [:first_name => "Luis", :surname => "Armstrong", :occupation => "musician", :date_of_birth => "4/8/1901"]

in((:Z, 999), d3)

(:Z, 999) in d3

in((:A, 100), d3)

(:A, 100) in d3

d3[:A]
d4 = Dict()

d5 = Dict{Float64, Int64}()

d5["c"]

delete!(d3, :B)

ki = keys(d3)
for k in keys(d3)
    println(k)
end

:A in keys(d3)

haskey(d3,:A)

collect(keys(d3))

d5 = ["JS Bach " => 1685, "Woody Allen" => 1935, "Barack Obama" => 1961]

for (k,v) in d5
    println("$k was born in $v")
end

dpairs = ["a", 1, "b", 2, "c", 3]

d6 = [dpairs[i] => dpairs[i+1] for i in 1:2:length(dpais)]

d6 = Dict{String => Int64}[dpairs[i] => dpairs[i+1] for i in 1:2:length(dpairs)]

function showfactor(n)
    d = factors(n)
    println("factors for $n")
    for (k,v) in d
        print("$k^$v\t")
    end
end

@time showfactor(3752)

@apropos factor

arrkey = [key for (key, value) in dict]
#this is the same as collect(keys(dict))
arrval = [value for (key,value) in dict]
#htis is the same as collect(values(dict))
arrn = [dict[i] for i = 1:10]

arrn = map((i) -> dict[i], [1:n])

d1 = Dict( 1 => 4.2, 2=> 5.3)

d2 = Dict{Any,Any}("a" => 1, (2,3) => true)

capitals = Dict{String, String}("France" => "Paris", "China" => "Beijing")

d5 = Dict(zip(keys1, values1))

# Dictionaries have keys that are unique, but values are not, and the keys are not ordered
# Sets are collections where the order does not matter
# Checking set ∈ in a set is independent of size
x = Set([1:100])
@time 2 in x
x2 = Set([1:1000000])
@time 2 in x2

using JLD
words1 = "To be or not to be, that is the question!"
@save "words1.txt" words1
str = readall("words1.txt")
nonalpha = r"(\W\s?)"
test = replace(words1, nonalpha, ' ')

digits = r"(\d+)"
test2 = replace(words1, digits, ' ')
word_list = split(words1, ' ')
word_freq = Dict{String, Int64}()
for word in word_list
    word = strip(word)
    if isempty(word) continue end
    haskey(word_freq, word) ?
        word_freq[word] += 1 :
        word_freq[word] = 1
    end
println("Word : freq \n")
words = sort!(collect(keys(word_freq)))
for word in words
    println("$word : $(word_freq[word])")
end
###############################
#Chapter 6. More on Types, Methods, and
#Modules
###############################

#Type annotations and conversions
(31+42) :: Float64

# Type conversions and promotions
convert(Int64, 7.0)

# In general, convert(Type, x) tries to shove x into an instane of Type.
# generally, type(x) also works.
Int64(7.0)
# But it doesn't work with 1. lost precision, 2. incompatible source value
# We can also define our own conversions and promotions

# Because of fallback promotion, Julia is super clever and instead of
# defining the + operator for shittons of combos, you can just
(x:: Number, y :: Number) = +(promote(x,y)...)
promote(1.5, im)
promote(true, 'c', 1.0)
#  promote_rule(::Type{Int8}, ::Type{Uint16}) = Int64.
# check out shit at base/promotion.jl

# TYYYYYYYYYPE Hierarchy
1.07^10
1.10^7

TYPE    Instantiate     Subtypes
Concrete    Y               N
Abstract    N               Y

Abstract such as Number or Real. Groups multiple subtypes together.
Abstract types cannot have any fields.
Any is the supertype of all types, and all the objects are also instances of Any
All types are supertypes of None and no object is an instance of None.
Now, None is Union() and Nothing becomes Void

# USER DEFINED AND COMPOSITE types
type Point
    x :: Float64
    y :: Float64
    z :: Float64
end

# Point is a concrete type.

p1 = Point(1,2,3)
p1
typeof(p1)

Composite type is most similar to a struct in C or a class without methods in Java

Instead of Python or Java's object.func(args), Julia uses function(object,args)

Julia has no classes.

Data and functions are separate.

Methods are not typed to a single type, because multiple dispatch connects them with different types.

When adding a new method for a type, you don't have to change the code of the type itself, as with other oolangs.

names(p1)

fields(p1)
methods(point)
methods(Point)
p1.y

p1.z = 3.13
p1.z = "A"
Objects as arguments to functions are passed by REFERENCE.
if you don't want your objects to be changeable, use immutable.

immutable Vector3D
    x::Float64
    y::Float64
    z::Float64
end
p = Vector3D(1,2,3)
Immutables are thread safe!
Hugely optimized for Performance.
p
p.x = 3.4

is(p, Vector3D)
p == Vector3D
abstract type Employee end
type Developer <: Employee
    name :: String
    iq
    favorite_lang :: String
end

Employee() # not going to work because yo ucan't instantiate an abstract type
The type Developer has two implicit constructors, but we can define another *outer constructor*
Developer(name, iq) = Developer(name,iq, "Java")
Outer constructors help default object creation.
devel1 = Developer("Bob", 110)

devel2 = Developer("William", 145, "Julia")
type Manager
    name :: String
    iq
    department :: String
end

man1 = Manager("Julia", 120, "ICT")
function cleverer(d:: Developer, e:: Employee)
    println("The developer $(d.name) is cleverer I think!")
end

cleverer(devel1, devel2)
cleverer(devel1, man)

function cleverer(e:: Employee, d:: Developer)
    if e.iq <= d.iq
        println("The dev $(d.name) is cleverer!")
    else
        println("The employee $(e.name) is cleverer!")
    end
end

function cleverer(d1:: Developer, d2:: Developer)
    if d1.iq <= d2.iq
        println("The developer $(d2.name) is cleverer!")
    else
        println("The deeveloper $(d1.name) is clverer!")
    end
end

cleverer(devel1, devel2)

cleverer(devel2, devel1)

TYPES and Collections - inner constructors
type Person
    firstname :: String
    lastname :: String
    sex :: Char
    age :: Float64
    children :: Array{String, 1}
end
p1 = Person("Alan", "Bates", 'M', 45.5, ["Jeff", "Stephan"])
people = Person[]
push!(people, p1)

push!(people, Person("Julia", "Smith", 'F', 27, ["Viral"]))
import Base.fullname
fullname(p::Person) = "$(p.firstname) $(p.lastname)"

show(people)

fullname(p::Person) = "$(p.firstname) $(p.lastname)"

Or the much better performant

fullname(p::Person) = string(p.firstname, " ", p.lastname)
print(fullname(p1))
type Family
    name :: String
    members :: Array{String, 1}
    big :: Bool
    Family(name :: String) = new(name, String[], false)
    Family(name :: String, members) = new(name, members, length(members)> 4)
end

fam = Family("Bates-Smith", ["Alan", "Julia", "Jeff", "Stephan", "Viral"])
new is exclusive to inner constructors

When you use inne constructors, there are no default constructors anymore. Outer Constructors calling a limited set of inner constructors is often
the best practice.

TYPE UNIONS
================
type VPoint
    x:: Float64
    y:: Float64
end
type Vector2D
    x ::Float64
    y ::Float64
end

p = VPoint(2.0,5.0)
v = Vector2D(1.0,3.0)

+(p, v)
import Base.+
+(p :: VPoint, q :: VPoint) = VPoint( p.x + q.x, p.y + q.y )
+(u :: Vector2D, v :: Vector2D) = VPoint(u.x + v.x, u.y + v.y)
+(u :: Vector2D,  p :: VPoint) = VPoint(u.x + p.x, u.y + p.y)
+(p:: VPoint, v:: Vector2D) = VPoint(p.x + v.x, p.y + v.y)

+(p,v)

VecOrPoint = Union{Vector2D, VPoint}

isa(p, VecOrPoint)

isa(v, VecOrPoint)

+(u :: VecOrPoint, v :: VecOrPoint) = VecOrPoint( u.x + v.x, u.y + v.y)
This is amazing because we just skipped defining 4 methods and did just 1.


PARAMETRIC TYPES AND METHODS
============================
You can have...
Array{Int64,1},
Array{Int16,1},
Array{Int32,1},
Array{ASCIISTRING,1},
Array{Float64,1}...

Array is thus a Parametric type
Array{T, 1}

In general, types can take type parameters, so that declarations can take a whole bunch of values

type TPoint{T}
    y :: T
    x :: T
end

Now, all of these are subtypes of TPoint.
issubtype(TPoint{String}, TPoint)

HOWEVERRRRRRRRRRRR
issubtype(TPoint{Float64}, TPoint{Real})
This is called type contravariance.

You can indicate the T in the constructor...

test = TPoint{Int64}(2,5)
or shorten to...
test = TPoint(2,5)

now for example,

teststring = TPoint("London", "Great-Britan!")

Now, we want to restrict the parameter type to T and only subtypes of Real...

type RPoint{T <: Real}
    x :: T
    y :: T
end

now if we try this next line it should error.

test2 = RPoint("London", "Great-Britain!")

Just as well, methods can have type parameters (in essence, restrictions on the mathematial domain)
add{T}(x:: T, y :: T) = y + x

add(2,3)

add(2,3.0)

add{T <: Number}(x :: T, y :: T) = y+x

function vecfloat{T <: AbstractFloat}(x :: Vector{T}) end

PAckages/Libraries are usually contained in a module, whose name starts with uppercase letter.

module Package1
println("FMLMLIA")
end

import Winston, Gadfly
Winston.plot(rand(4))
Gadfly.plot(x=[1:10],y=rand(10))

The global scope is in the Main module
The Core Module contains all built-in identifiers and is always available.
The standard library is also available (all the contents of /base is cointained in
    Base, Pkg, Collections, Graphics, Test, Profile)
A Module has a type: Module
typeof(Base)


#This tells you all the vars you have defined!
names(Main)

methods(names)

@doc names
#whos() tells you all the vars used and the corresponding types and allocation in memory
whos()

whos(Colors)

You can make internal definitions such as constants, variables, types, functions and so on visible to other modules (make them public)
by declaring them with export.

e.g.
export Type1, perc

If module LibA is defined in modules_ext.jl, then require("modules_ext.jl") will load this in the current code.
using LibA ---- Makes its exported names available in the current namespace.

Only the exported functions remain visible. The others remain private.

eg
# The below module save in file temperature_converter.jl in same directory
# module TemperatureConverter
#     export as_celsius
#
#     function as_celsius(temperature, unit)
#         if unit == :Celsius
#             return temperature
#         elseif unit == :Kelvin
#             return kelvin_to_celsius(temperature)
#         end
#     end
#
# function kelvin_to_celsius(temperature)
#     # private function
#     return temperature + 273
# end
#
# end
println("$(as_celsius(100,:Celsius))")
println("$(as_celsius(100, :Kelvin))")
println("#(kelvin_to_celsius(0))")

IN GENERAL, there are different ways of importin definitions from another module LibA.

1. using LibA --- LibA gets searched for exported definitions if needed. You can use funcitons in LibA without qualifying it.
2. using LibA.varB or, using LibC: varC, funcC
3. import LibD.funcD only imports one name na dcan also be useed if funcD was not exported.
    now must use funcD as LibD.funcD.
4. importall LibE --- import all the exported names in LibE

Imported vars are read-only, current module cannot create vars with the same names as the imported ones.
A source file can cointain many modules, or one module can be defined in several source files.
if a module contains a function __init__(), this will be executed when the module is first loaded.

include("file.jl") is, to the compiler, no different to copying file1.jl and pasting it directly in the current file or the REPL.

The variable LOAD_PATH contains a list of dirs where Julia looks for module files when running using, import, or include.
    you can exted it with push!(LOAD_PATH, "new/path/to/search")
 modules are compiled on load, which slows shit down if not for precompilation.

CHAPTER 7 - METAPROGRAMMING IN JULIAAAAAAAAAAAAA
================================================

Everything is an expression that returns a value when executed.
Everypice of the code is internally represented as an ordinary Julia data structure, also called an expression.
By working on expressions, a Julia Program can transform and generate new code.

It inherits homoiconicity from lisp: "code is data and data is code"
1. Expressions and symbols
2. eval and interpolation
3. defining macros
4. built-in macros
5. reflection capabilities

Abstract syntax trees and grammars...
an expression is simly an object that represents Julia code.
eg
2 + 3 is

    +
  2    3

To make Julia see this as an expression and block its evaluation, we have to quote it.
Or rather, to preced it by a colon(:) like
:(2 + 3). When you eval :(2 + 3), it just returns :( 2 + 3)
typeof( :(2 + 3))

quote
    a = 42
    b = a^2
    a - b
end

We can give expressions a name
d1 = :(2+3)

d1.head

d1.args

d1.typ

e2 = :(2 + a * b - c)

e2.head

e2.args

e2.typ

expressions work recursively.
We can simplify every subexpression in the same way until we end up with elementary symbols and literals.
In the content of an expression, symbols are used to singnify access to variables.
They represent the variable in the structure of the tree code.
The prevent evaluation chatacter is :.
:x returns :x

dump(d1)

dump() helps to show the args, type, and head of an expression. (works way better in REPL.
Eval and interpolation.

Because we know th etype of expressions, we can build new ones like this:

e3 = Expr(:call, :*, 3, 4 )

and this should be allowed.
We can evaluate this expression with the function eval()
eval(e4)


but we should be careful that these expressions are dfined when evaluated in the global scopeeg
f1 = :(3 - zzz)
eval(f1)

which should error because zzz was not defined. Similarly, we can have evals that change the current state of the global scope.
f2 = eval(:(b = 1))

To make writing expressions easier, we can interpolate with the $ sign.
It evaluates immediately what the expression means.
a = 4
b = 1

e4 = :(a+b)

e5 = :($a+b)

There are two kinds of evaluations here:
1. expression interpolation with the $ --- evaluates when the expression is consturcted (at parse time)
2. Quotation ( with : or quote) evaluates only when the expression is passed to eval at runtime.

This is huge for reducing boilerplates in external libraries, or to generate lots of similar routines in other situations.
    In robotics, being able to generate a program and then run it is very useful.

Functions on expressions

function math_expr(op, op1, op2)
    expr = Expr(:call,op, op1,op2)
    return expr
end

ex = math_expr(:+, 1, Expr(:call, :*, 4,5))

eval(ex)

And now an example that doubles any numeric argument but leaves the expressions alone.

function make_expr2(op, opr1, opr2)
    oprf1, oprf2 = map(x -> isa(x, Number) ? 2*x : x, (opr1, opr2))
    retexpr = Expr(:call, op, oprf1, oprf2)
    return retexpr
end

make_expr2(:+, 1, 2)

ex = make_expr2(:+, 1, Expr(:call, :*, 5,8))
eval(ex)

We move on to macros!

MACROOOOOOOOOOOOS
=================
like functions, but take expressions instead of values.
The expansion occurs at parse time when the syntax tree is being built, not when the code is actually executed.
A macro maps a tuple of arguments to a return expression, and the resulting expression is compiled directly rather than
requiring a runtime eval().

macro sayhello()
    return :( println("Hello world!") )
end

@sayhello

FUNCTION: it takes the input values and returns the computed values at runtime.
MACRO: It takes the input expressions and returns the modified expressions at parse time.

ie, a macro is a custom program transformation.
macros are defined as such
macro mname()
    #code
    println("YO!")
end
: is used for
1. creating a symbol via :x, :(:), :foo == Symbol("Foo"), or Symbol(:var, '_', "sym")
2. creating expression with :(2+3), x = Expr(:call, :+, 2,3)
ex = quote
    foo
    bar
    baz
end

@mname

@mname sum

macro macint(ex)
    quote
        println("start")
        $ex
        println("after")
    end
end

@macint println("Where am I?")
macro assert1(ex)
    :($ex ? nothing : error("Assertion failed: ", $(string(ex))))
end
@assert1 1 == 1

@assert 1 == 42

REMEMBER macroexpand!
macroexpand(:(@assert 1 == 42))
macro unless(test, branch)
    quote
        if !$test
            $branch
        end
    end
end

arr = [3.14, 42, 'b']

@unless 42 in arr println("arr does not contain 42")

macroexpand(:(@unless 41 in arr println("arr does not contain 41")))

quote
    if !(41 in arr)
        println("arr does not cointain 41")
    end
end
arr = ["a", "b", "c"]


macro convarr(arr, T)
    :(reshape($T[$arr...], size($arr)...))
end

@convarr arr Symbol

Because you are injecting code into the module they are called, gotta watch nameclashes.
Hygienic macro respect this.
    1. Declare vars in the macro as local, so as to not conflict with outer variables.
    2. Use the escape function to make sure that an interpolated expression is not expanded, but instead is used literally.
    3. Don't call eval inside a macro (likiely the vars you are evaluating don't even exist at that point)

macro timeit(ex)
    quote
        local t0 = time()
        local val = $(esc(ex))
        local t1 = time()
        print("elapsed time in seconds: ")
        @printf "%.9f" t1 - t0
        val
    end
end

@timeit factorial(10)
@timeit a^3

Gotta differentiate between calling context and macro context.

Allow you to create DSLs.

Built-in macros
===============

TESTING!
@assert
using Base.Test
@test 1==3

@test 1 ≈ 1.1

DEBUGGING!
@which sort(arr)

@show

BENCHMARKING!
REMEMBER @timed
@timed [x^2 for x in 1:1000]
@elapsed [x^2 for x in 1:1000]

@allocated [x^2 for x in 1:1000]

TASKS!
a = @async 1+2
consume(a)

REFLECTION CAPABILITIES!
Code is represented by expressions that are datastructures of type Expr.
The structure of a program and its types can be explored programmatically, just like any other data.
    This means a running program can dynamically discover its own properties, which is called REFLECTION.

Some functions that do this are...
typeof(), subtypes(),
methods(),
names and types.

eg

type person
    name :: String
    height :: Float64
end

fields(person)
code_lowered(+, (Int, Int))
code_typed(+, (Int, Int))

CHAPTER 8 - I/O, Networking, ParallelComputing
==============================================
1. Basico IO
2. working with CSVs
3. using DataFrames
4. working with TCP sockets and servers
5. Interacting with databases
6. Parallel operations nad ocmputing

Basico IO
read(STDIN, Char)

write(STDOUT, "Julia")
STDIN and STDOUT are simply streams
readbytes(STDIN,3)

REMEMBER eachline
If you need to read all the lines in a n input stream, remember to use the readline.

stream = STDIN
for line in eachline(stream)
    print("Found $line")
    print("processed")
end

we use eof(stream) with a while loop...

while !eof(stream
    x = readline(line, Char)
    println("Found $x")
    #process
end

WORKING WITH FILES
To work with files, we use the IOStream type.
it has the supertype IO and the following characteristics...
    1. fields given by

fields(IOStream)
Array{Symbol,1}: :handle :ios :name :mark

2. the types are given by IOStream.types

IOStream.types

The file handler is a pointer of the type Ptr, which is a reference to the file object.

touch("empty.txt")

fname = "empty.txt"
f1 = open(fname)
typeof(f1)

data = readlines(f1)

for line in data
    print(line)
end

close(f1)

REMEMBER do format
open(fname) do file
    process(file)
end

Writing a file requires the "w" flag, then writing to it with print, println or write, then closing.

type Wine
    fixed_acidity :: Array{Float64}
    volatile_acidity :: Array{Float64}
    citric_acid :: Array{Float64}
    quality :: Array{Float64}
end

#wine1 = Wine(data[1,:]...)
The elements of the row are splatted with the ... operator into the Wine constructor.

using DataFrames

dv = @data([7, 3, NA, 5, 42])
df = DataFrame()
df[:Col1] = 1:4
df[:Col2] = [ e, pi, sqrt(2), 42]
df[:Col3] = [ true, false, true, false]
show(df)

Julia can work with other human-readable file formats through specialized packages:
For JSON, use the JSON package. The parse method converts the JSON strings into
Dictionaries, and the json method turns any Julia object into a JSON string.
For XML, use the LightXML package
For YAML, use the YAML package
For HDF5 (a common format for scientific data), use the HDF5 package
For working with Windows INI files, use the IniFile package

We want to be able to handle multiple clients!

server = listen(8081)
while true
    conn = accept(server)
    @async begin
        try
            while true
                line = readline(conn)
                println(line)
                write(conn, line)
            end
        catch ex
            print("connection ended with error $ex")
        end
    end
end

The listen function has some variants, for example, listen(IPv6(0),2001) creates a TCP
server that listens on port 2001 on all IPv6 interfaces. Similarly, instead of readline, there are
also simpler read methods:
read(conn, Uint8): This method blocks until there is a byte to read from conn, and then
returns it. Use convert(Char, n) to convert a Uint8 value into Char. This will let you see
the ASCII letter for Uint8 you read in.
read(conn, Char): This method blocks until there is a byte to read from conn, and then
returns it.

DATABASESSSSSSSSSS
==================
Open Database Connectivity



PARALLEL OPERATIONS AND COMPUTINGGGGGGGGG
=========================================
Julia implements the actor model like Erlang, Elixir, or Dart.

Creating Processes
julia -p n to start a REPL with n workers
These are diferent processes, not threads, so they do not share memory.

workers()

for pid in workers()
    print("sup $pid here!")
end
addprocs(1)

workers()
myid()

nprocs()

All these workers communicate via TCP ports and run on the same machine, which is why it is
called a local cluster. To activate workers on a cluster of computers, start Julia as follows:
julia --machinefile machines driver.jl
Here, machines is a file that contains the names of the computers you want to engage, like this:
node01
node01
node02
node02
node03
Here node01, node02, and node03 are the three names of computers in the cluster, and we want
to start two workers each on node01 and node02, and one worker on node03.
The driver.jl file is the script that runs the calculations and has the process identifier 1. This
command uses a password-less SSH login to start the worker processes on the specified
machines. The following screenshot shows all the eight processors on an eight core machine
when engaged in a parallel operation:

REVIEW THE CLUSTERMANAGER

USING LOW-LEVEL COMMS

f(x) = x^2

r1 = remotecall(x -> x^2, 2, 1000)

fetch(r1)

r2 = @spawnat 2 sqrt(2) #lets worker 2 calculate sqrt(2)
fetch(r2)
r3 = @spawn sqrt(5)

typeof(r3)

fetch(r3)

#TO EXECUTE ON ALlLL THE WORKERS
r = [@spawnat w sqrt(5) for w in workers()]

fetch(r[1])

To execute the same statement on all hte workers, we can use the @everywhere
@everywhere println(myid())

x = 5

@everywhere println(x)
@everywhere w = 8

@everywhere using Colors

@everywhere function fib(n)
    if (n<2) then
        return n
    else return fib(n-1) + fib(n-2)
    end
end

TIP!
Separate code into files: functions.jl as the functions and parameters tha need to be run in parallel,
and the driver.jl that manages the processing and collecting the results.

Other alternative is to separate the load files on the command line

julia -p n -L file2.jl -L file2.jl driver.jl

reduce data movement to improve performance.

if every worker needs a var, use a global.

for pid in workers()
    remotecall(pid, x -> (global d; d = x; nothing), d)
end

PARALLEL LOOPS AND MAPS
=======================
function buffon(n)
hit = 0
for i = 1:n
    mp = rand()
    ϕ = (rand() * π) - π/2
    xright = mp + cos(ϕ)/2
    xleft = mp - cos(ϕ)/2
    p = (xright >= 1 || xleft <= 0) ? 1 : 0
    hit += p
end
miss = n - hit
πapprox = n /hit * 2
end


@time buffon(10_000_000)

function buffon_par(n)
    hit = @parallel (+) for i = 1:n
    mp = rand()
    ϕ = (rand() * π) - π/2
    xright = mp + cos(ϕ)/2
    xleft = mp - cos(ϕ)/2
        (xright >= 1 || xleft <= 0) ? 1 : 0
    end
    miss = n - hit
    πapprox = n/ hit * 2
end

@time buffon_par(10_000_000)
addprocs(1)

FORMAT:
@parallel ("reducing operator") "the for loop"
Calculations must be independent.

So that means this will fail...

arr = zeros(10_000_000)
@parallel for i = 1: 10_000_000
    arr[i] = i
end

because each processor has a copy of it.

If the computational task is to apply a function to all elements in some collection, you can use a
parallel map operation through the pmap function. The pmap function takes the following form:

pmap(f, coll),

applies a function f on each element of the collection coll in parallel, but
preserves the order of the collection in the result. Suppose we have to calculate the rank of a
number of large matrices. We can do this sequentially as follows:

function rank_marray()

    marr = [rand(1000,1000) for i=1:10]

    for arr in marr
        println(rank(arr))
    end
end

function prank_marray()
    marr = [rand(1000,1000) for i = 1:10]
    println(pmap(rank,marr))
end

@time prank_marray()

These are typical map-reduce problems.


DISTRIBUTED ARRAYS

@everywhere using DistributedArrays

arr = drand((100,100), workers()[1:1], [1,1])

whos(arr)

arr.pmap

arr.indexes


arr.cuts

arr.chunks

da = @parallel [2i for i = 1:10]

DArray((10,100)) do I
    println(I)
    return zeros(length(I[1]), length(I[2]))
end

Julia's model for building a large parallel application works by means of a global distributed
address space. This means that you can hold a reference to an object that lives on another machine
participating in a computation. These references are easily manipulated and passed around
between machines, making it simple to keep track of what's being computed where. Also,
machines can be added in mid computation when needed.

Chapter 9 - Running External Programs
=====================================

Running shell stuff
C and Fortran
Calling Python
Performance tips

RUNNING SHELL COMMANDS
----------------------

pwd()
cd("d:\\test\\week1")
; ls
; mkdir folder
; cd folder

Wanna run a shell command? Use the run() function!

cmd = `echo "Julia is smart"`
typeof(cmd)
@doc Cmd
run(cmd)
run("date")
@doc run

1.02^300

Julia forks commands as child processes from the Julia process. Instead of immediately running
the command in the shell, backticks create a Cmd object to represent the command, which can then
be run, connected to other commands via pipes, and read or write to it.


INTERPOLATION
file = "file1.txt"
cmd = `cat $file`
run(cmd) # prints the ocntents of file1.txt

PIPELINING
Use the |> symbol!

run(`cat $file` |> "test.txt")

and you can chain it thus

run(`echo $("\n hi \n Julia")` |> `cat` |> `grep -n J`)

Another example is to search for the word "is" in all the text files in the current folder; use the
following command:
run(`grep is $(readdir())`)


To capture the result of a command in Julia, use readall or readline:
a = readall(`cat "tosort.txt"` |> `sort`)

Now a has the value "A\r\nB\r\nC\n".

Multiple commands can be run in parallel with the & operator:
run(`cat "file1.txt"` & `cat "tosort.txt"`)
This will print the lines of the two files intermingled, because the printing happens concurrently

CALLING C AND FORTRAN
---------------------

For calling C, we need to work with pointer types.
A native Ptr{T} is the memory address for a variable of type T.
The term bitstype is also used. This is for concrete type - data consists of bits:
    Int8, Uint8, Int32, Float64, Bool, Char
To pass a string to C, it is converted to a contiguous type byte array represenatiton with the function
    bytestring(); given Ptr to a C string, it returns a Julia string.

typeof(Ptr)
@doc Ptr

lang = ccall( (:getenv, "libc"), Ptr{UInt8}, (Ptr{UInt8}, (Ptr{UInt8},), "LANGUAGE"))

@doc ccall

Base.Libdl.find_library(["libc"])

When calling FORTRAN, all inputs must be passed by reference.
Arguments to C are in general automatically converted.
The returned values in C types are also converted to Julia types.
Arrays of Booleans are handled differently in C and J, so gotta handle manually.
Some system dependent types applies too.

ccal() auto ensures args are preserved from GC until call returns.

C types are mapped to JUlia types.
short => Int16
double => Float64

Embedding is possible

you can use C with Callbacks

If you have existing C code, you must compile it as a shared lib to call it from Julia.
With GCC, use =shared -fPIC
Support for Cpp is through Cpp and Clang

Calling Python
==============

using PyCall
pyeval("10*10")

@pyimport math

math.sin(math.pi / 2)

PERFORMANCE TIPS!
=================

1. Don't use globals, or make them constant.
2. Structure code around functions that work on local vars via the funciton args - this returns the results rather than mutating global objects
3. Type stability. Don't change types over time.
4. If you need large arrays, use a sizehint from the start.
5. if arr is very large and you don't need it, kill it.
6. sometimes disabling gc via gc_disable() can be useful.
7. Anonymous funcitons yayyyy
8. use small functions.
9. code different versions of a funciton according to the types, so that multiple dispatch applies.
10. use types for keyword arguments, avoid the splat ... for dynamic lists of keyword args.
11. using mutating APIS like push!() is useful to avoid copying.
12. prefer array operations to comprehensions.
13. don't use a try/catch in a tight loop.
14. Use immutables
15. avoid Any
16. Avoid abstract types in a collection
17. don't copy unless necessary, avoid using a large number of variables or temp arrays or collections
18. devectorize your code
19. use @parallel if appropriate
20. reduce data movement between workers in parallel execution
21. fix deprecation warnings
22. use the @inbounds macro
23. don't use eval at runtime

Tools to use
============

check speed and allocations with @time

linter tool is sweet for performance profiling

consider using TypeCheck

using ProfileView

CHAPTER 10 - THE STDLIB and Packages
====================================

Stdlib, package manager, publish a package, graphics in Julia, GAdfly on data.asdf


THE STDLIB
----------
filter(f, coll) applies f to all the elements of coll

fold, min, max, sum, any, all, map, filter

filter(x -> iseven(x), 1:10)

mapreduce(f, op, coll) applies f to all elements in col, then reduces with op()
so
mapreduce(x -> sqrt(x), +, 1:10) == sum(map(x -> sqrt(x), 1:10))

The pipeline operator lets you write very functionally styled code
x |> f applies f to the function argument x.

1:10 |> (x -> sqrt(x)) |> sum

REMEMBER clipboard()
a = 42

clipboard(a)

GRAPHICS!
=========
using Gadfly

draw(SVG("gadfly.svg", 6inch, 3inch), plot([x -> x^2], 0, 25))
p1 = plot([x -> cos(x)/x], 5, 25)
draw(PNG("gadfly.png",300,100), pl)


APPENDIX AAAAAAAAAAAAAAAAAAAAAA
===============================
Useful.



===============================================================
PART II. Module 2
===============================================================

How fast can Julia be?

function pisum()
    sum = 0.0
    for j = 1:500
        sum = 0.0
        for k = 1:10_000
            sum += 1.0/(k*k)
        end
    end
    sum
end

Analyzing Julia Performance

@timev sqrt.(rand(1000))

The Julia Profiler
inspects call stack every 1ms or 10ms, counts how often each line of ocde is encountered,
    helps prioritize optimization efforts.

using Base.Profile

function testfunc()
    x = rand(10000,10000)
    y = std(x,1)
    return y
end

testfunc()

@profile testfunc()

Profile.print()

Profile.init()

There are a few profiler options that are sometimes useful, although the defaults are a good
choice for most use cases. Primary among them is the sampling interval. This can be provided as
keyword arguments to the Profile.init() method. The default delay is 1 millisecond on Linux,
and should be increased for very long-running programs through the following line of code:
julia> Profile.init(delay=.01)
The delay may be reduced as well, but the overhead of profiling can increase significantly if it is
lowered too much.
Finally, you may have realized that the profiler stores its samples in memory to be viewed later.
In order to profile a different program during an existing Julia session, it may be necessary to
clear the stored profile from memory. The Profile.clear() function does this, and must
therefore be run between any two invocations of @profile within the same Julia process

using ProfileView

ProfileView.view()

test()
@profile test()
ProvileView.view()

Naaaais

Using the Memory Allocation tracker
track -alloation=user

Profile.clear_malloc_data()

To get Julia to track memory allocation, start the julia process with the –trackallocation=user
option as follows:
julia> track -allocation=user
This will start a normal Julia session in which you can run your code as usual. However, in the
background, Julia will track all the memory used, which will be written to .mem files when Julia
exits. There will be a new .mem file for each .jl file that is loaded and executed. These files
will contain the Julia code from their corresponding source files, with each line annotated with
the total amount of memory that was allocated as a result of executing this line.
As we discussed before, when running Julia code, the compiler will compile user code at
runtime. Once again, we do not want to measure the memory allocation due to the compiler. To
achieve this, first run the code under measurement once, after starting the Julia process. Then run
the Profile.clear_malloc_data() function to restart the allocation measurement counters.
Finally, run the code under measurement once again, and then exit the process. This way, we will
get the most accurate memory measurements.




CHAPTER 3 - Types in Julia
types are tag-on values that restrict the range of potential values

foo(x::Integer) = "an integer"
foo(x::String) = "a string"
function bar(a, b)
    x :: Int64 = 0
    y = a + b
    return y
end

foo(1)

foo("1")

foo(1.5)

Dispatch is the process of selecting a funciton to be executed at runtime
Dispatch is a runtime process, method overloading is a compile-time concept.
In traditional OOP, dispatch at runtime occurs only on the receiver of the method ie., the object before the dot -- and hence
why it is called "single dispatch".

Julia progs, ∴, cointain many small function definitions for differnt types of arguments.
God pratice is to constrain arg types to the widest level possible.
Use only tight methods when failure is assured with wider types.

consider:

sumsqr(x,y) = x^2 + y^2

sumsqr(1,2)

sumsqr(1.5,2.5)

sumsqr(1+2im, 2+3im)

ABSTRACT TYPES
Abstract types cannot have any instantiated values == Cabnn only be nodes, not leaves of the type hierarchy.
Represent sets of related types.
Int32 and Int64 both inherit from the Integer abstract type

abstract Number

abstract Real <: Number

abstract FloatingPoint <: Real

abstract Integer <: Real

abstract Unsigned <: Integer

Number has no explicit super type - thus a subtype of Any.

Concrete types can be instantiated to values.
Concrete types cannot have any subtypes


COMPOSTIE and immutable types
=============================

type Pixel
    x :: Int64
    y :: Int64
    color :: Int64
end

p = Pixel(4,4,100)

p.x = 10

p.x

immutable IPixel
    x :: Int64
    y :: Int64
    color :: Int64
end

p = IPixel(4,4,100)

p.x = 10

type TPixel{T}
    x :: Int64
    y :: Int64
    color :: T
end

Parametros de tipos are the powerful shiznit.
This now accepts methods for TPixel{Int64}, or TPixel{String},
    and TPixel is now an abstract type itself.

Array{T,N} ==== T is a type and N is a numberrr


TYPE INFERENCE
==============
The type inference algo is a forward dataflow analysis - NOT the Hindley-Milner algo in
    ML langs.

check this
[x for x=1:5]

No type annotations, but we get an Int64.


TYPE STABILITY
==============
Be it. Use it.
Return value of a funciton is dependent only on the types of its arguments and not the values.

Thus type stability can continue across chains of function invocations wihtout actually running the code,
    even though the language is fully dynamic.


function mytrunc(x)
if x < 0
    return 0
else
    return x
end
end

mytrunc(-1)

mytrunc(-2.5)

mytrunc(2.5)

Works for Ints and Floats.

typeof(mytrunc(2.5))

typeof(mytrunc(-2.5))

@code_warntype mytrunc(-2.5)

function trunc_fixed(x)
    if x < 0
        return zero(x)
    else
        return x
    end
end

trunc_fixed(-2.4)

trunc_fixed(-2)

typeof(trunc_fixed(-2))

typeof(trunc_fixed(-2.4))

REMEMBER move the type variable part of the code into a function.

@code_llvm trunc_fixed(2)

@code_llvm trunc_fixed(0)
@code_llvm trunc_fixed(-2.5)


@code_llvm mytrunc(2)
@code_llvm mytrunc(0)
@code_llvm mytrunc(2.5)

using BenchmarkTools

@benchmark mytrunc(2.5)
@benchmark trunc_fixed(2.5)

Identifiying Type-Stability
===========================
look for Union returns and %jl_value_t% in the assembly code



LOOP VARS
===========================

Don't change types of vars from one iteration of the loop to the other.

function sumsqrtn(n)
    r = 0
    for i = 1:n
        r = r + sqrt(i)
    end
    return r
end

function fixsumsqrtn(n)
    r = 0.0
    for i = 1:n
        r = r + sqrt(i)
    end
    return r
end


@benchmark sumsqrtn(1_000_000)

@benchmark fixsumsqrtn(1_000_000)

KERNEL METHODS
==============

function string_zeros(s :: AbstractString)
    x = Array(s == "Int64" ? Int64 : Float64, 1_000_000)
    for i in 1:length(x)
        x[i] = 0
    end
    return x
end

@benchmark string_zeros("Int64")

But here, we are inferring in one part and filling a loop in another -
this calls for 2 functions.

function string_zeros_stable(s :: AbstractString)
    x = Array(s == "Int64" ? Int64 : Float64, 1000000)
    return fill_zeros(x)
end

function fill_zeros(x)
    for i in 1:length(x)
        x[i] = 0
    end
    return x
end

@benchmark string_zeros_stable("Int64")

TYPES IN STORAGE LOCATIONS
==========================

When defining a storage locations for data, it is importnat to specify a concrete type.
    So fo things that hold data, like arrays, dictionaries, or fields in composite types, it is
    best to explicitly define what type it will hold.


Arrays
======

experiment with 2 arrays

a = Int64[1,2,3,4,5,6,7,8,9,10]
bbb = UInt128[1,2,3,4,5,6,7,8,9,10]

function arr_sumsqr{ T <: Number}(x :: Array{T,1})
    r = zero(T)
    for i = 1:length(x)
        r = r + x[i] ^ 2
    end
    return r
end

@benchmark arr_sumsqr(a)

COMPOSITE TYPES
===============

immutable BPoint
    x
    y
end

Compiler does not know actual size, so there might be pointer misdirection.
waaaay better to do this.

immutable ConcretePoint
    x :: Float64
    y :: Float64
end

PARAMETRIC COMPOSITE TYPES ARE THE SHIZNIT
==========================================
What if we wanna work with Float32 and Float 16?

We could try....

immutable PointWithAbstract
    x :: AbstractFloat
    y :: AbstractFloat
end

But this would still mean some pointer misdirections, as compiler does not know
exact layout of the data in memory. Way better to try this.

immutable ParametricPoint{ T <: AbstractFloat}
    x :: T
    y :: T
end

When we write the type in this manner, our code remains generic. We can write our methods with
the confidence that the ParametricPoint type can hold values for any type of a floating point
number. Yet, at runtime, when an instance of this type is created, it is instantiated with a particular
type of float. In other words, once an instance is created, T becomes known. At this point, all the
benefits of specifying the concrete type discussed before are applicable. Both storage and type
inferences are efficient now.




CHAPTER 4 - FUNCTIONS AND MACROSSSSSSSSS
========================================

Write shit tons of small functions based on type.
Learn about the problem with globals.

The trouble with goals.
-----------------------
To keep track of all writes to global variables is akin to solving the halting problem.
Therefore, the data-flow algo sucks.

p = 2

function pow_array(x :: Vector{Float64})
    s = 0.0
    for y in x
        s = s + y^p
    end
    return s
end

t = rand(100000)

@benchmark pow_array(t)

@code_warntype pow_array(t)

const p2 = 2

function pow_array2(x :: Vector{Float64})
    s = 0.0
    for y in x
        s = s + y^p2
    end
    return s
end

@benchmark pow_array2(t)

in JULIA, a const var can change value, but not its type.

@code_warntype pow_array2(2)

INLINING
===========
As we've mentioned before, Julia code consists of many small functions. Unlike most other
language implementations, some of the core primitives in the base library are also implemented in
Julia. This means that the function call overhead has the potential to be a bottleneck in a Julia
program. This is mitigated using some aggressive inlining performed by the Julia compiler.
Inlining is an optimization performed by a compiler, where the contents of a function or method is
inserted directly into the body of the caller of that function. Thus, instead of making a function
call, execution continues directly by executing the operations of the callee within the caller's
body.
In addition, many compiler optimization techniques work within the body of a single function.
Inlining, therefore, allows many more optimization to be effective within the program.

Inlining is done by the Julia compiler, the rest is LLVM magic.


DEFAULT-INLINING
===================

Inline worthiness is done by Julia compiler.
Essentially, small functions with deterministic types.
However, it bloats code size and ∴ balance is needed.

testtrunc(x) = x < 0 ? zero(x) : x

function sqrt_sin(x)
    y = testtrunc(x)
    return sin(sqrt(y)+1)
end

Now we look at the processed AST after the compiler has run its type inference and inlining passes.

@code_typed sqrt_sin(1)

CONTROLLING INLINING
====================

REMEMBER @inline
needs to be in front of a function definition.

No call-site annotation to force inlining.

We define f(x) that performs some numeric ops on args, then g(x) calls f
after transforming its argument.

function f(x)
    a = x*5
    b = a+3
    c = a-4
    d = b/c
end

This is too long to be inlined by default.

g(x) = f(x)

@code_typed g(3)

@inline function f_inline(x)
    a = x*5
    b = a + 3
    c = a-4
    d = b/c
end

g_inline(x) = f_inline(2*x)

@code_typed g_inline(3)

@code_llvm g_inline(3)

Disabling inlining is useful and necessary for debugging.

REMEMBER -inline=no

CLOSURES AND ANONYMOUS FUNCTIONS
================================

. Anonymous functions, as the name suggests, are
functions without a name, and they are usually created at the point where they are passed in to
another function as an argument. In Julia, they are created with the -> operator separating the
arguments from the function body. These, and named functions created within the scope of another
function, and referring to variables from this outer scope, are called closures. This name arises
from the idea of these functions "closing over" the outer scope.


sqr(x) = x ^ 2

@benchmark map(sqr, rand(100000))

@benchmark map(x -> x ^ 2, rand(100000))

USING MACROS FOR PERFORMANCE
============================
macros can help do stuff in compile time and not in run time.

Raw Source
    Parse
        Macro Expansion - macroexpand()
            Lowering        - @code_lowered
                Type inference
                    Inlining
                        Generated Function expansion - @code_typed
                            Code Gen
                                Native Compilation      - @code_native
                                    RUN!

USING Macros

We gonna try evaluating a polynomial

function poly_naive(x, a...)
    p = zero(x)
    for i = 1:length(a)
        p = p + a[i] * x ^ (i-1)
    end
    return p
end

f_naive(x) = poly_naive(x, 1,2,3,4,5)

f_naive(3.5)

1 + 2*3.5 + 3*3.5^2 + 4*3.5^3 + 5*3.5^4

@benchmark f_naive(3.5)

REMEMBER peakflops()

peakflops()

function poly_horner(x, a...)
    b = zero(x)
    for i = length(a) : -1 : 1
        b = a[i] + b*x
    end
    return b
end

f_horner(x) = poly_horner(x,1,2,3,4,5)

@benchmark f_horner(3.5)

REMEMBER
The Horner macro
Improving the speed of this computation starts with realizing that the coefficients of the
polynomial are constants. They do not change and are known when writing the program. In other
words, they are known at compile time. So, maybe we can expand and write out the expression
for the Horner's rule for our polynomial. This will take the following form, for the polynomial
that we used previously:

muladd(x,muladd(x,muladd(x,muladd(x,5,4),3),2),1)

This is likely to be the fastest way to compute our polynomial. However, writing this out for
every polynomial that we might want to use will be extremely annoying. We loose the benefit of
having a general library function that can compute any polynomial.

This is exactly what macros are for!

macro horner(x,p...)
    ex = esc(p[end])
    for i = length(p) -1 : -1 : 1
        ex = :(muladd(t, $ex, $(esc(p[1]))))
    end
    Expr(:block, :(t = $(esc(x))), ex)
end

f_horner_macro(x) = @horner(x,1,2,3,4,5)

@benchmark f_horner_macro(3.5)

REMEMBER Strategy of generating customized code for particualr problems.

GENERATED FUNCTIONS also called staged functions
===================

Macros for after type inference.

Generated functions come in two parts.
They are invoked once for each unique type of its arguments.
    Here, the arguments themselves take the values of their types.
    The return value of this execution MUST be an expression that is used as the body of the function when called with valeus of these types.

This cycle is executed each time the function is called with new types.
    The function is called with types as values once, and then the returned expression is used for all invocations with argument values of htis type.

Using generated functions for performance
    ==============================

REMEMBER use GenFuncs for performance by moving constant parts of the computation earlier into the compilation stage

Toy problem: number of cells in a multidim array.

function prod_dim{T, N}(x :: Array{T,N})
    s = 1
    for i = 1:N
        s = s*size(x,i)
    end
    return s
end

prod_dim(rand(10,5,5))

Optimizing this computation with a generated function starts with the observation that the number
of iterations of the loop is equal to the number of dimensions of the array, which is encoded as a
type parameter for arrays. In other words, for a particular type of input (and array of a particular
dimension), the loop size is fixed. So, what we can try to do in a generated function is move the
loop to the compile time:

@generated function prod_dim_gen_impl{T, N}(x :: Array{T,N})
    ex = :(1)
    for i = 1:N
        ex  = :(size(x, $i) * $ex)
    end
    return ex
end

prod_dim_gen_impl(rand(10,5,5))

Double checking
function prod_dim_gen_impl{T, N}(x::Array{T, N})
    ex = :(1)
        for i = 1:N
            ex = :(size(x, $i) * $ex)
        end
    return ex
end

x = rand(2,2,2)

prod_dim_gen_impl(x)

x = rand(2,2,2,2);

prod_dim_gen_impl(x)

REMEMBER this is a form of loop unrolling

Also, note that this function looks much simpler without the loop. The number of tokens in this
function is significantly reduced. This might make the function inline-worthy and cause the
compiler to inline this function, making this code even faster.

USING NAMED PARAMETERS
======================

REMEMBER Useful for creating APIs
However, compiler cannot infer the types of named parameters effectively

named_param(x; y = 1, z = 1) = x^y + x^z

pos_param(x,y,z) = x^y + x^z

@time for i in 1:100000; named_param(4; y = 2, z = 3); end

@time for i in 1:100000; pos_param(4,2,3); end

CHAPTER 5 - FAST NUMBERS
========================

Default numeric types are as close to metal as possible - so that we get C like speed.
Default sizes depend on the OS.


WORDS_SIZE

REMEMBER bits(3)

bits(3)

isbits(Int64)

REMEMBER isbits

isbits(String)

As a Julia value, basic numeric types can be boxed.

bits(-3)

myadd(x, y) = x + y
Looking at the output of of the following compiled code, (even if, like me, you are not an expert at
reading assembly), it should be apparent that, other than the function overhead to set the stack and
return the result, the generated code simply consists of the CPU instruction to add two machine
integers, addq. There is no boxing/unboxing operation remaining in the native code when the
function is called. Take a look at the following:
julia> @code_native myadd(1,2)


.section __TEXT,__text,regular,pure_instructions
Filename: none
Source line: 1
pushq %rbp
movq %rsp, %rbp
Source line: 1
addq %rsi, %rdi
movq %rdi, %rax
popq %rbp
ret


There is an even bigger advantage to storing numbers using the machine representation. Arrays of
these numbers can be stored using contiguous storage. A type tag is stored once at the start.
Beyond this, data in numerical arrays is stored in a packed form. This not only means that these
arrays can be passed to C libraries as-is (minus the type tag) but also that the compiler can
optimize computations on these arrays easily. There is no need for pointer dereferencing when
operating on numerical arrays of bit types.

Integer Overflow
================

There are no overflow checks present within any base mathematical op in Julia

typemax(Int64)

bits(typemax(Int64))

typemin(Int64)

bits(typemin(Int64))

typemax(Int64) + 1

Pg. 307

bits(TPixel)

40*18

.001 *45000

46440/17.77


.001*3300

1.12^30

bits(.3)

bits(.5)

bits(.7)

bits(.7*.5)

bits(.7*5)

bits(.7*.5)

bits(round(.7*.5,3))

round(.7*.5,3)

fibbi(n) = n <= 1 ? 1 : n*fibbi(n-1)

for i in 1:10
    println("fibbi($i) = ", fibbi(i))
end
