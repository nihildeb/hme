+++
date = "2015-10-20T16:47:46+01:00"
description = ""
title = "goals"

+++

#### Goals MD

Improve C++ skills for my job. Unfortunately, this includes the constraints: on Windows with Visual Studio. This would not be my personal choice, so I don't apologize.

* I want to create games
* In C++
* They should run on Windows, Linux, and Android
* Fast iteration and reckless abandon
* I will follow the 7DRL development model (release a "game" each week)
* Iteratively build a fast engine which supports a wide variety of 2D games

After evaluating Marmalade and Cocos2d-x, I decided to drop down a layer. They both had a ton of cruft, and too much build magic.

So, I will start with:

* SFML 2.3.2 http://www.sfml-dev.org/documentation/2.3.2/
* EntityX https://github.com/alecthomas/entityx
* easylogging++ https://github.com/easylogging/easyloggingpp
* Boost::Test http://www.boost.org/doc/libs/1_59_0/libs/test/doc/html/index.html

I will follow an Entity-Component-System architecture. I plan to apply it thoroughly and without restraint. I have reviewed the cod of several ECS systems. There are many bad ones which miss the point. There is one good one I have found in C++ which is EntityX.

http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/

Not only does EntityX stay true to the principle, but it keeps an eye towards memory locality of component data which should help cache performance to boot. I will use it as a reference, but I also want to do it differently.

I'll start with EntityX in any case...

