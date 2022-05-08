# CrossPlatformSockets
## Purpose
The intent of this component is to abstract the OS specific of basic TCP and UDP network communications, while additionally providing ways to represent network concepts such as IP and Socket addresses as classes. An important tenant of this component is to provide such classes only in valid formats, such that one will not constantly have to rely on checks to a call like *is_valid()* to determine if the address or object they are currently working with is worth using in its current state. 

This component is partially inspired by the Rust implementation of its std::net library, which can be found here: https://doc.rust-lang.org/stable/std/net/index.html

## Current State
This component is currently unfinished and very much a work in progress. The first phase of 

## Design (Subject to Change)
![Congrats, you found the secret text!](https://github.com/lsoldano93/CrossPlatformSockets/blob/trunk/doc/ClassDiagram.png?raw=true)

## Why are you doing this?
I mostly just want to practice and refresh myself on networking concepts, while also building something I can maintain and use later when a personal project that inevitably requires networking comes into the ole' brain-a-roni.

Feel free to use this as you wish!
