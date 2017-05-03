#!/bin/bash

ME=`whoami`

IPCS_S=`ipcs -m | egrep "0x[0-9a-f]+ [0-9]+.*644" | grep $ME | cut -f2 -d" "`

for id in $IPCS_S; do
	ipcrm -m $id
done
