# bottom-c
[``bottom``](https://github.com/bottom-software-foundation/bottom-rs), but it's written in C.

## Building
You'll need ``make``; building can be done by running the following

    make

You can also install ``bottom-c`` on your system

    sudo make install

``bottom-c`` use ``gcc``, but you can also build with the compiler of your choice. To remove ``bottom-c`` from your system, do the following

    sudo make uninstall

Check out the [Makefile](./Makefile) to see what options you need to specify in order to install in a different path and how to set the compiler of your choice.
