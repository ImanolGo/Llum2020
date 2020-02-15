#!/bin/bash

#-----------------------------------------------------------
#
# quit Live application
#
#-----------------------------------------------------------


echo "Kill runLlum"

ps -ef | grep runLlum | grep -v grep | awk '{print $2}' | xargs kill

echo "-> Quit Ableton Live"
osascript <<EOD
delay 0.5 -- time to release modifier keys if for example the script is run with command-R

if application "Live" is running then

  ignoring application responses
    tell application "Live" to quit with saving
  end ignoring

  tell application "System Events"

      set frontmost of process "Live" to true

      keystroke "q" using command down

      keystroke return
      keystroke return

  end tell

  ignoring application responses
    tell application "Max" to quit with saving
  end ignoring

  ignoring application responses
    tell application "ProtoPixel" to quit with saving
  end ignoring

  ignoring application responses
    tell application "ProtoPixel Create" to quit with saving
  end ignoring

  tell application "System Events"

      set frontmost of process "ProtoPixel Create" to true

      --key code 36 --Return

  end tell

  tell application "System Events"

      set frontmost of process "ProtoPixel Create" to true

      keystroke "q" using command down

      --key code 36 --Return
      keystroke return

  end tell


  
  ignoring application responses
    tell application "Llum2020App" to quit with saving
  end ignoring

  delay 10 -- Time to quit the application

end if
EOD

PROCESS=Live

if pgrep $PROCESS
  then
    echo '-> KILL LIVE'
    killall Live
  else
    echo '-> Live already killed'
fi

PROCESS=Max

if pgrep $PROCESS
  then
    echo '-> KILL MAX'
    killall Max
  else
    echo '-> Max already killed'
fi

PROCESS='ProtoPixel Create'

if pgrep $PROCESS
  then
    echo '-> KILL ProtoPixel'
    killall -9 ProtoPixel
    killall -9 "ProtoPixel Create"
  else
    echo '-> ProtoPixel Create already killed'
fi

PROCESS='Llum2020App'

if pgrep $PROCESS
  then
    echo '-> KILL Llum2020App'
    killall Llum2020App
  else
    echo '-> Llum2020App already killed'
fi

echo '-> Remove Live Preferences'

rm -f ~/Library/Preferences/Ableton/Live\ 10.1.7/CrashDetection.cfg
rm -f ~/Library/Preferences/Ableton/Live\ 10.1.7/CrashRecoveryInfo.cfg
rm -f -r ~/Library/Preferences/Ableton/Live\ 10.1.7/Crash
