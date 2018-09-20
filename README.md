# AtomView

Installation/Compilation:

Once cloned from github, simply run make in the repository folder.

Note: This program requires OpenGL and X11 and is intended for a Linux environment.  It also expects the GNU C++ compiler to be installed.

    CLI Usage: ./atom-view <IUPAC name> [-Option]
    Options:
        -c --common [name]        Set display name to different common name
        -d --debug                Display debugging information
        -f --form [on/off]        Toggle display of molecular formula (default: off)
           --distribution [val]   Set distribution variable
        -r --resolution [val]     Set resolution variable