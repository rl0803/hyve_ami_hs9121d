#!/bin/sh

#
#Format of the Bond Configuration File
#BondName slave1,slave2...slaveN Mode Miimon
#

BOND_CONFIG_FILE=/etc/network/bond.conf
BOND_SLAVE_FILE=/conf/activeslave.conf


# Check if bond information is found
[ -f $BOND_CONFIG_FILE ] || exit 0

BOND_DEV=`ifconfig | grep bond | awk '{ print $1}'`

# Check the bond device is present or not.
if grep $BOND_DEV /sys/class/net/bonding_masters >/dev/null; then
    echo "$BOND_DEV has been found in the bonding_masters."
else
    exit 0
fi

# Parse the Configuration
BONDCFG=`grep $BOND_DEV $BOND_CONFIG_FILE`
SLAVES=`echo $BONDCFG | awk '{ print $2 }'`
MODE=`echo $BONDCFG | awk '{ print $3 }'`


# Parse the Configuration
SLAVECFG=`grep $BOND_DEV $BOND_SLAVE_FILE`
SLAVE1=`echo $SLAVECFG | awk '{ print $2 }'`
SLAVE=`echo $SLAVE1 | sed 's/,/ /g' `

sleep 2

ACTIVE_SLAVE=/sys/class/net/$BOND_DEV/bonding/active_slave
SLAVE2=`cat $ACTIVE_SLAVE`

if [ $SLAVE != $SLAVE2 ]; then
    if [ $MODE == 1 ]; then
        echo "Bond : Active slave has changed, Setting back to $SLAVE"
        ifenslave -c $BOND_DEV $SLAVE
    fi
fi

exit 0

