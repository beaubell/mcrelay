#!/bin/bash

LOCALIP=$1
REMOTEIP=$2

if [ -z "$LOCALIP" ]
then
    echo "Error: LOCALIP not set!"
    exit 1
fi

if [ -z "$REMOTEIP" ]
then
    echo "Error:REMOTEIP not set!"
    exit 1
fi


#COT
echo "Starting COT Relay..."
./udprelay $LOCALIP 239.2.3.1 6969 10000 $REMOTEIP 10000 &

#CHAT
echo "Starting ATAK Chat Relay..."
./udprelay $LOCALIP 224.10.10.1 17012 10001 $REMOTEIP 10001 &

for i in 1 2 ; do
    wait -n
    echo "exit code $?"
done
