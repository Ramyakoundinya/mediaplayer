# mediaplayer


# JUKE-JINIE MEDIA PLAYER

JUKE-JINIE is a  media player is an application that allows users to play various types of media files, such as audio and video files. It provides basic controls for playback, such as play, pause, stop, rewind, and fast forward. Also have some advanced features like setting different visualizers while playing the audio.

************************************************************************************************************************************************************************************************************

## how to install and run the project

To run this application you need to install gstreamer and GTK library.

GStreamer is included in all Linux distributions. We recommend using the latest version of a fast moving distribution such as Fedora, Ubuntu (non-LTS), Debian sid or OpenSuse to get a recent GStreamer release.

All the commands given in this section are intended to be typed in from a terminal.

Warning Make sure you have superuser (root) access rights to install GStreamer.

---------------------------------------------------------

Install GStreamer on Fedora
Run the following command:

dnf install gstreamer1-devel gstreamer1-plugins-base-tools gstreamer1-doc gstreamer1-plugins-base-devel gstreamer1-plugins-good gstreamer1-plugins-good-extras gstreamer1-plugins-ugly gstreamer1-plugins-bad-free gstreamer1-plugins-bad-free-devel gstreamer1-plugins-bad-free-extras

---------------------------------------------------------

Install GStreamer on Ubuntu or Debian
Run the following command:

apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

---------------------------------------------------------
Building applications using GStreamer
---------------------------------------------------------
The only other “development environment” that is required is the gcc compiler and a text editor. In order to compile code that requires GStreamer and uses the GStreamer core library, remember to add this string to your gcc command:

pkg-config --cflags --libs gstreamer-1.0

If you're using other GStreamer libraries, e.g. the video library, you have to add additional packages after gstreamer-1.0 in the above string (gstreamer-video-1.0 for the video library, for example).

If your application is built with the help of libtool, e.g. when using automake/autoconf as a build system, you have to run the configure script from inside the gst-sdk-shell environment.

Warning Depending on the GStreamer libraries you need to use, you will have to add more packages to the pkg-config command, besides gstreamer-1.0 At the bottom of each tutorial's source code you will find the command for that specific tutorial, including the required libraries, in the required order. When developing your own applications, the GStreamer documentation will tell you what library a function belongs to.

---------------------------------------------------------
Installing on Windows
Supported platforms

Windows 7
Windows 8
Windows 8.1
Windows 10
Prerequisites
To develop applications using GStreamer for Windows we recommend using Windows 7 or later. Windows Vista may also work but it is not supported.

GStreamer package includes C headers (.h) and library files (.lib) valid for any version of Microsoft Visual Studio. For convenience, property pages (.props) are also included which extremely simplify creating new projects. These property pages, though, only work with Microsoft Visual Studio 2010 and newer (including the free Visual C++ Express edition).

The recommended system is Windows 7 or newer with Microsoft Visual Studio 2010 or newer. Take a look at its system requirements).

Installing GStreamer for 32-bit platforms requires approximately 286MB of free disk space for the runtime and 207MB for the development files (as of some older version).

Installing GStreamer for 64-bits platforms requires up to approximately 350MB of free disk space for the runtime and 400MB for the development files (as of version 1.15.1).

----------------------------------------------------------
Download and install GStreamer binaries

There are 3 sets of files in GStreamer binaries:

The runtime files are needed to run GStreamer applications. You probably want to distribute these files with your application (or the installer below).
The development files are additional files you need to create GStreamer applications.
The Merge Modules files are additional files you can use to deploy GStreamer binaries alongside your application (see Windows deployment).
Get both the Runtime and Development installers appropriate for your architecture from here:

GStreamer download page

If in doubt, download the 64-bit MSVC packages:

Runtime installer: e.g. gstreamer-1.0-msvc-x86_64-{VERSION}.msi
Development files installer: e.g. gstreamer-1.0-devel-msvc-x86_64-{VERSION}.msi
Execute the installers and choose an installation folder. The suggested default is usually OK.

WarningIf you plan to use Visual Studio, close it before installing GStreamer. The installer will define new environment variables which will not be picked up by Visual Studio if it is open.

On Windows 8 and Windows 10, it might be necessary to log out and log back in to your account after the installation for the newly defined environment variables to be picked up by Visual Studio.

It is the application's responsibility to ensure that, at runtime, GStreamer can access its libraries and plugins. It can be done by adding %GSTREAMER_ROOT_X86%\bin to the PATH environment variable, or by running the application from this same folder.

How to do this: Windows start icon > Search "environment variables" > Edit the system environment variables (will open System Properties)

Environment Variables > System variables > Variable :Path > Edit > New > Paste "C:\gstreamer\1.0\msvc_x86_64\bin" > OK


- [CLICK HERE for more information about installing gstreamer](https://gstreamer.freedesktop.org/documentation/installing/index.html?gi-language=c)

Use this command to install the GTK library in linux.

sudo apt-get install libgtk-3-dev

Follow the steps to install on windows.

Step 1: Download MSYS2 Installer. To install gtk3, we need to download and install MSYS2 which provides a “mintty” terminal that allows users to install different packages and software easily through the command line on Windows. ...
Step 2: Install MSYS2. ...
Step 3: Install gtk3.

- [CLICK HERE for more information about installing GTK library](https://linuxhint.com/install-gtk-3-windows/)

*************************************************************************************************************************************************************************************************


## How to use the application

Play/Pause- The play/pause button is used to play the video and stop the playing whenever you want.

Restart- The restart button in used to restart the current file as it plays from the beginning.

Previous- The previos button is used to play the previous song

Next- The next button is used to play the next song.

60+ - The 60+ button is used to forward 60 seconds from the current playing state.

60- - The 60- button is used to backward 60 seconds from the current playing state.

5+ - The 5+ button is used to forward 5 seconds from the current playing state.

5- - The 5- button is used to backward 5 seconds from the curre

10%+ -The 10%+ button is used to forward 10% of the total duration of the video.

10%- -The 10%- button is used to backward 10% of the total duration of the video.

Visualizers- The visualizer button is used to change the visualizers according to your choice while playing the video.

About- About button displays the information of application name, its version and developers name.

****************************************************************************************************************************************************************************************************

---------------------------------------------------------
Key-board operation:
---------------------------------------------------------
Space - To play and pause the audio and video you can use the space key.

Enter - Enter is used to display the application information.

Up_arrow - It is used to forward the video/audio for 5 seconds.

Down_arrow - It is used to backward the video/audio for 5 seconds.

Right_arrow - This key is used to forward the video/audio for 60 seconds.

Left_arrow - This key is used to backward the video/audio for 60 seconds.

<,>(Angular brackets)- Angular_brackets are used to play the next and previos songs.

{,}(Curly braces)- These curly braces are used to forward and backword the 10% of the total duration of the video/audio from the current position.

***************************************************************************************************************************************************************************************************

## CREDITS

This project was created by:

Dharani S

Geetanjali Patil

Kavya Naik

Megha L

Ramyashree M

Pooja Baadkar

Saurabh Patel

Adarsha N Y

-----------------------------------------------------------------------------------------------------------------------
Special thanks to:

- Sanchit Gharath for providing the initial project concept and feedback and guiding us throughout the project.

-----------------------------------------------------------------------------------------------------------------------
## Documentation

[Documentation](https://saskenit-my.sharepoint.com/:w:/g/personal/ee213043_sasken_com/ES7asCCznipFv6-RyJtBFwcBHRzk4Xah8AJd1e63uADZ0g)
