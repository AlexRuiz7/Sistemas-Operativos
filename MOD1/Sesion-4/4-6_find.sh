#!/bin/bash

find -mtime -1 >> $HOME/"modificados_`date +%Y`-`date +%d`-`date +%H`"
