# Insturctables-Counter

Arduino Shell Download Insturctions:
-----------------------------------

1) Navigate to the 'src' file above
2) Open 'Main.cpp'
3) Copy all of the contents in it(cmd+c)
4) Open Arduino and use a new project
5) Paste(cmd+v) all of the code
6) Make sure all libraries and drivers are installed
7) Change paramaters, info below
8) Upload!

VS Code and PLatformIO Download Instructions:
----------------------------------------------

1) On your computer navigate to the platformio projects file in terminal using the cd command, the file for macs is found 'documents/platformio/projects', at least for me.
2) Type in 'git clone https://github.com/masonhorder/Instructables-Counter'
3) Open VSCode
4) Go to PlatformIO home and open 'instructables-counter'
5) Install all needed libraries
6) Change paramaters, info below
7) Upload!



Parameters Insturctions:
========================

There are three parameters that you need to change. The following sections are instructions for each.

**WIFI:**

Simply just replace SSID with your network name(line #14).

Then change Password and put in your wifi's password(Line #15)


**URL:**

Alright, this is a little more complicated, what you want to do is find where the json file of your project is located on instructables. So the first step is to open up your instructables project on the site. Make sure you are not in editing mode. Now what you want to do is open developer tools, on a mac cmd+opt+i. Now find the tab in developer tools that says 'network'. Once you are here you are going to want to refresh the page. what you want to do is scroll through the XHR tab until you find the one labeled 'getIbleStats'. Now click on it and then copy the link under general -> request url. If you take out the first part(https://www.instructables.com) you are left with something that looks like this: /json-api/getIbleStats?id=ED3Z5LNMCW8HY2E. Take your string that looks like this and plop it into the varialbe 'projectUrl' on line #18. You are good to go and upload the code.



Resources:
==========
Youtube video:


Thingiverse page(for 3d models):