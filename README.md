# Team-7-AVC-Project

[Group Google Doc](https://docs.google.com/document/d/1E5nax8sHvRvkREA-iLWSAP3fB-MumnZg8RVfdBt5z-o/edit?usp=sharing)\
[Project Kanban](https://github.com/ruhaansaiyad/Team-7-AVC-Project/projects/1)\
[Milestones](https://github.com/ruhaansaiyad/Team-7-AVC-Project/milestones)

## Team Members:
Mohammed Ruhaan Saiyad\
Ming Shane Tong\
Daneel Penman\
Lucas Sarten

## Communication Tools
Facebook\
Google Docs\
Discord\
Github

## Roles:
<table>
    <tbody>
        <tr>
            <th>Member</th>
            <th>Role</th>
        </tr>
        <tr>
            <td>Ruhaan Saiyad</td>
            <td>Project Manager (organising team meetings, reporting regularly on progress) and coding</td>
        </tr>
        <tr>
            <td>Ming Shane Tong</td>
            <td>Software Architect (writing core code and extending functionality)</td>
        </tr>
        <tr>
            <td>Daneel Penman</td>
            <td>Paperworker and coder</td>
        </tr>
        <tr>
            <td>Lucas Sarten</td>
            <td>Coding, testing, and debugging</td>
        </tr>
    </tbody>
</table>

## Timeline
<table>
    <tbody>
        <tr>
            <th>Milestone</th>
            <th>Start Date</th>
            <th>Item Due</th>
            <th>Tasks</th>
            <th>Due Date</th>
        </tr>
        <tr>
            <td>Project Plan</td>
            <td>28/05</td>
            <td>Plan</td>
            <td>
                <ul>
                    <li> [x] Establish communication</li>
                    <li> [x] Initial discussions for project direction</li>
                    <li> [x] Assign roles</li>
                    <li> [x] Assessment of team capabilities </li>
                </ul>
            </td>
            <td>04/06</td>
        </tr>
        <tr>
            <td>Weekly Progress #1</td>
            <td>04/06</td>
            <td>Core</td>
            <td>
                <ul>
                    <li> [x] Install SFML and make sure it works</li>
                    <li> [x] Determine feasibility of idea</li>
                    <li> [x] Discuss structure of program</li>
                    <li> [x] Set up framework</li>
                    <li> [x] Begin working on core</li>
                    <li> [x] Begin testing and debugging core</li>
                    <li> [x] Review Feedback</li>
                    <li> [x] Propose Changes</li>
                    <li> [x] Complete Core</li>
                </ul>
            </td>
            <td>12/06</td>
        </tr>
        <tr>
            <td>Weekly Progress #2</td>
            <td>12/06</td>
            <td>Completion / Challenge</td>
            <td>
                <ul>
                    <li> [x] Begin abstracting for completion</li>
                    <li> [x] Determine how the core code will be modified</li>
                    <li> [ ] Allot tasks</li>
                    <li> [x] Begin work on completion</li>
                    <li> [x] Begin testing and debugging completion</li>
                    <li> [ ] Complete completion</li>
                    <li> [x] Begin Challenge</li>
                    <li> [ ] Testing challenge</li>
                </ul>
            </td>
            <td>19/06</td>
        </tr>
        <tr>
            <td>Reflection</td>
            <td></td>
            <td></td>
            <td>19/06</td>
        </tr>
    </tbody>
</table>

## Install Guide

## Instructions for installation specific for Windows 10 (Unfinished):

1. From https://www.sfml-dev.org/download/sfml/2.5.1/, download the correct SFML library and MingGW builds corresponding to your Operating System version if you haven’t already and extract to folder in directory (C:). 
- For 64-bits systems: download ‘MinGW Builds 7.3.0 (64-bit)’ and ‘GCC 7.3.0 MinGW (SEH) - 64-bit’.
- For 32-bits systems: download ‘MinGW Builds 7.3.0 (32-bit)’ and ‘GCC 7.3.0 MinGW (DW2) - 32-bit’.
2. To set up MinGW, in the Windows search bar, enter ‘Edit the system environment variables’ and click it. In the ‘Advanced’ tab, click ‘Environment Variables’, select the ‘Path’ variable and click ‘Edit’. Click ‘New’ and copy the directory address of the folder stored in (C:) or type ‘C:\x86_64-7.3.0-release-posix-seh-rt_v5-rev0’ and press ‘OK’.


## Windows:
- Download SFML version GCC 7.3.0 MinGW (SEH) - 64-bit found [here](https://www.sfml-dev.org/download/sfml/2.5.1/)  
- Extract the files to C:/SFML
- Download and install MinGW compiler version 7.3.0 (64-bit) found [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download)
- Download and extract the repository files found [here](https://github.com/ruhaansaiyad/Team-7-AVC-Project/archive/master.zip)
- Compile server3.cpp and robot.cpp using the included makefiles.
- Copy the dll files from the SFML/bin folder to the same folder as the exe
- Run the compiled server3.exe file
- Run the compiled robot.exe file
## Linux: 
- Download SFML version Linux GCC - 64-bit found [here](https://www.sfml-dev.org/download/sfml/2.5.1/)  
- Extract the files
- Download and extract the repository files found [here](https://github.com/ruhaansaiyad/Team-7-AVC-Project/archive/master.zip)
- Compile server3.cpp and robot.cpp using the included makefiles.
- Run the compiled server3 file
- Run the compiled robot file
- To change the server map between core, completeion and challenge, change the first line of config.txt to   "mazeFile,[level name].txt".
## Mac: 
- Install Homebrew by opening Terminal (Command+Space type Terminal) and typing the following:       
```/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"``` 
- Install SFML by typing ```brew install sfml``` in Terminal 
- Download and extract the repository files found [here](https://github.com/ruhaansaiyad/Team-7-AVC-Project/archive/master.zip)
- Compile server3.cpp and robot.cpp using the included makefiles.
- Run the compiled server3 file
- Run the compiled robot file

