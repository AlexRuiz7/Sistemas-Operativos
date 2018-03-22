# Ejecución con at: at "hora" ./4-2.sh

#!/bin/bash

	for ARCHIVO in `ls ~`
	do
		echo $ARCHIVO >> listahome-`date +%Y-%j-%T-$$`
	done
