#!/bin/bash
if [ ! $(which xxd) ]; then
	echo Missing xxd
	exit 1
fi;
xxd -i ./mainwindow.ui > mainwindow_ui.h
