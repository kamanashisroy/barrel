#!/bin/bash

PID=""

function get_pid {
   PID=`pidof /usr/bin/lua /srv/http/scripts/cron.lua`
}

function stop {
   get_pid
   if [ -z $PID ]; then
      echo "server is not running."
      exit 1
   else
      echo -n "Stopping server.."
      kill -9 $PID
      sleep 1
      echo ".. Done."
   fi
}


function start {
   get_pid
   if [ -z $PID ]; then
      echo  "Starting server.."
      /usr/bin/lua /srv/http/scripts/cron.lua &
      get_pid
      echo "Done. PID=$PID"
   else
      echo "server is already running, PID=$PID"
   fi
}

start

