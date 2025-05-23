#!/bin/bash
/usr/sbin/apache2ctl -DFOREGROUND && sleep 10 && service ssh start