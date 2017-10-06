#!/bin/sh

# script for building RTEMS Smart Controller

CURRENT=$PWD

# build all Libraries
buildLibraries() 
{

		echo $CURRENT
		# make the engine library
		cd ../engine
		echo Making engine in $PWD
		make $1

		#make the engine interface library
		cd ../engineinterface
		echo Making engineinterface in $PWD
		make $1

		#make the link driver physical libraries
		cd ../link_driver/hal_rtems
		echo Making link physical layer driver in $PWD
		make $1

		#make the link layer libraries
		cd ../
		echo Making link logical layer in $PWD
		make $1

		#return to original dir
		cd $CURRENT

		cd ../../../threads/source
		echo Making  active objects in $PWD
		make $1

		cd hal_rtems
		echo Making rtems threads in $PWD
		make $1


		cd $CURRENT

		cd ../../../mididriver/hal_rtems
		echo Making  active objects in $PWD
		make $1


}

buildLibraries
