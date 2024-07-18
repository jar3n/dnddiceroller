# DND Dice Roller for DND 5e
Born out of a desire to undercut DNDBeyond and its paywalls, this is a command line application used for playing dnd. The ultimate goal is to do all the core functions of DND and be flexible for adding items and custom abilities.

## Background
DNDBeyond puts a lot of content behind paywalls and for main stories that is fine. However, paywalling class features and certain items is annoying and unfairly limits the creativity you can have when making a character. Initially, I decided to go old school and use a pdf character sheet, but I often forgot all the modifers I need to apply to my character for various rolls. So I tried google's roll dice feature, but that was very limited. Now we are here.

## Install
One of the goals is to package this in an easy installer. For now, you need to clone the repo and build it locally. 

Requirements:
CMake 3.28, Google Protobuf, Boost 

At the head of the local repo run the following steps:

1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `cd ..`
5. `cmake --build <path to build directory>`

## Interface:
SUBJECT TO CHANGES:

You are able to roll a dice with any max number and apply any modifier to the roll. In addition, you are able to roll at advantage or disadvantage. Furthermore, you can create a character, however, the character does not affect the dice rolls:

To roll a dice:
`dnddice --roll <max value>` 
 OR
`dnddice -r <max value>`

To roll with a modifier:
`dnddice --roll <max value> --modifier <modifier value>` OR `dnddice -r <max value> -m <modifier value>`

To roll with advantage:
`dnddice --roll <max value> --advantage` OR `dnddice -r <max value> -A`

To roll with disadvantage:
`dnddice --roll <max value> --disadvantage` OR  `dnddice -r <max value> -D` 
