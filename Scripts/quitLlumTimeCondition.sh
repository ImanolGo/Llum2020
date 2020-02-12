#!/bin/bash

#-----------------------------------------------------------
#
# quit Live application on a certain time
#
#-----------------------------------------------------------


echo "Kill runLive"

#!/bin/bash

kill_time=2350

while true
do
          cur_time=`date "+%H%M"`
          if [ $cur_time -eq $kill_time ]; then
                    echo "Time reached!"
                    ps -ef | grep runLive | grep -v grep | awk '{print $2}' | xargs kill

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


                      ignoring application responses
                        tell application "Max" to quit with saving
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

                    echo '-> Remove Live Preferences'
                    rm -f ~/Library/Preferences/Ableton/Live\ 10.1/CrashDetection.cfg
                    rm -f ~/Library/Preferences/Ableton/Live\ 10.1/CrashRecoveryInfo.cfg
                    rm -f -r ~/Library/Preferences/Ableton/Live\ 10.1/Crash
                    osascript <<EOD
                    tell application "Finder" to shut down
EOD
                    exit 5           # To find exit status of the script
          fi
          echo "Checking Time: "
          echo $cur_time
          sleep 60                 # To execute script every minute
done







