---

# Profile

Intrusive Multi-threaded C++ Performance Profiling

* Multi-Threaded

  *Profile multiple threads at the same time*

* Intrusive

  *You choose which Threads, Functions, Scopes, Events + Counters that you want to profile*

* Compiled-out in Production builds

  *You choose whether to include or compile-out profiling calls with a single define 'PROFILE_ENABLED'*

* Default Text file output

  *Generates a default text file output, that can optionally be replaced*

* Visualiser 

  *Profile data can be rendered in this [profile visualiser](https://github.com/JimKnowler/profile-visualiser)

## Requirements

* C++11

* Windows (tested so far on Visual Studio 2013 and used )

## Usage

* Add 'Include' directory to your project's Include Paths

``` C++
-I profile\Profile\include
```

* Link the Profile static library into your project 

  *(use the win32/x64/Release/Debug build as appropriate to match your build settings)*

``` C++
-L profile\Release\Profile.lib
```

* Initialise the Profiler in your main thread, before making any profiling calls from your program

``` C++
PROFILE_INIT(); 
```

* Mark each Thread that you want to profile, before making any profiling calls from it

  *(note: you can label each thread that you profile)*

``` C++
void myThreadEntryFunction( int arg ) {
    PROFILE_THREAD("My Worker Thread #3");

    /// @todo Do work for this thread + make profiling calls
}

```

* Mark each *Function* that you want to profile, before doing any work in it
  
  *(note: The profiler will automatically detect the name of the function being profiled)*

``` C++
void myFunction(int arg) {
    PROFILE_FUNCTION();

    /// @todo Do work in this function
}
```

* Mark any *Scope* within a function that you want to profile separately, before doing any work in it

  *(note: you can label each scope that you profile)*

``` C++
void myFunction(int arg) {
    PROFILE_FUNCTION();

    /// @todo Do work in this function

    {
        PROFILE_SCOPE("the first scope");

        /// @todo do work in this scope that you want to measure separately
    }

    /// @todo Do other work in this function

    {
        PROFILE_SCOPE("the second scope");

        /// @todo do work in this other scope that you want to measure separately
    }

    // @todo Do further work in this function
}
```

* Mark any Event that you want to profile separately
  * *Events are profiled separately for each thread*
  * *Events are captured as a label and a single timestamp*

``` C++
  
  if (someSignificantEventHasHappened) {
    PROFILE_EVENT("my event label");
  }

```

* Monitor a integer counter

  *(note: the counter is initialised by default to 0, and can take any 32bit signed integer value)*

``` C++

// define an instance of the counter
// 'myCounter' is a variable, so you can choose whether to make it a global, local or member variable
PROFILE_COUNTER(myCounter);

// initialise your instance of the counter
PROFILE_COUNTER_INIT(myCounter, "my counter name");

// set your counter to a specific value
PROFILE_COUNTER_SET(myCounter, 29);

// increment your counter by a specified value
PROFILE_COUNTER_INC(myCounter, 2);

// decrement your counter by a specified value
PROFILE_COUNTER_DEC(myCounter, 4);

```

## Default Text Profile Output Format

By default, the profiler generates [text profile data as specified by the visualiser](https://github.com/JimKnowler/profile-visualiser)

## Visualiser

Profile data gathered with this profiler can be [viewed in this profiler visualiser](https://github.com/JimKnowler/profile-visualiser)

<div style="width:100%;display:flex;">

![Screenshot 1](https://raw.githubusercontent.com/JimKnowler/profile-visualiser/master/docs/screenshot-1.png "Screenshot 1")

![Screenshot 2](https://raw.githubusercontent.com/JimKnowler/profile-visualiser/master/docs/screenshot-2.png "Screenshot 2")

![Screenshot 3](https://raw.githubusercontent.com/JimKnowler/profile-visualiser/master/docs/screenshot-3.png "Screenshot 3")

</div>
