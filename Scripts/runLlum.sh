#!/bin/bash

#-----------------------------------------------------------
#
# start Live application
#
#-----------------------------------------------------------


echo "-> Quit Ableton Live"
osascript <<EOD
delay 0.5 -- time to release modifier keys if for example the script is run with command-R

if application "Live" is running then
  tell application "System Events"

      set frontmost of process "Live" to true

      keystroke "q" using command down

      keystroke return

  end tell

  ignoring application responses
    tell application "Live" to quit with saving
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


while true
do
	PROCESS=Live
	if pgrep $PROCESS
		then
			echo '-> Live process already exit'
		else
			echo '-> Open Live'
			
			rm -f ~/Library/Preferences/Ableton/Live\ 10.1/CrashDetection.cfg
			rm -f ~/Library/Preferences/Ableton/Live\ 10.1/CrashRecoveryInfo.cfg
			rm -f -r ~/Library/Preferences/Ableton/Live\ 10.1/Crash
			
			open -a Ableton\ Live\ 10\ Suite ~/Desktop/HgZurichProject/HgZurichProject.als
			
			osascript <<EOD

			delay 5.0 -- time to release modifier keys if for example the script is run with command-R

			tell application "System Events"

					set frontmost of process "Live" to true

					keystroke return
					keystroke return

			end tell
EOD


	fi

	sleep 30

done
