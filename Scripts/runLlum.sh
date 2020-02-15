#!/bin/bash

#-----------------------------------------------------------
#
# start Llum application
#
#-----------------------------------------------------------


while true
do
	PROCESS=Live
	if pgrep $PROCESS
		then
			echo '-> Live process already exit'
		else
			echo '-> Open Live'
			
			rm -f ~/Library/Preferences/Ableton/Live\ 10.1.7/CrashDetection.cfg
			rm -f ~/Library/Preferences/Ableton/Live\ 10.1.7/CrashRecoveryInfo.cfg
			rm -f -r ~/Library/Preferences/Ableton/Live\ 10.1.7/Crash
			
			open -a open -a Ableton\ Live\ 10\ Trial ~/Desktop/Llum2020/Ableton/Imanol\ Chains_v4\ Project/Imanol\ Chains_v4.als
			
	fi
	
	sleep 2
	
	PROCESS=Llum2020App
	if pgrep $PROCESS
		then
			echo '-> Llum2020App process already exit'
		else
			echo '-> Open Llum2020App'
			
			open -a ~/Desktop/Llum2020/OpenFrameworks/Llum2020App/bin/Llum2020App.app
	fi

	sleep 5
	PROCESS=ProtoPixel
	if pgrep $PROCESS
		then
			echo '-> Create process already exit'
		else
			echo '-> Open ProtoPixel'
			
			open -a ProtoPixel ~/Desktop/Llum2020/Create/Llum2020.ppxproj
	fi

	sleep 30

done
