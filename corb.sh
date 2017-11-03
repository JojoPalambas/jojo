#/bin/sh

# cd recover

if [ $# -lt 1 ]; then
	echo 'Error: 1 argument or more expected' >&2
	exit 1
fi

if [ $1 = '-cd' ]; then
	PWD=/home/depott_g/afs/corb
	exit 0
fi

verbose=1
remove=1
corb=~/corb/

for file in $*; do
	if [ $file = '-v' ]; then
		verbose=1

	elif [ $file = '-q' ]; then
		verbose=0

	elif [ $file = '-cl' ]; then
        for corb_file in $corb*; do
            if [ $verbose -eq 1 ]; then
                echo "rm -rf $corb_file"
            fi
            rm -rf $corb_file
        done
		if [ $verbose -eq 1 ]; then
			echo "The corb has been cleaned."
		fi

  elif [ $file = '-ls' ]; then
		if [ $verbose -eq 1 ]; then
			ls $corb
		fi

  elif [ $file = '-rm' ]; then
		remove=1

  elif [ $file = '-rt' ]; then
		remove=0

  elif [ $file = '-h' ]; then
		if [ $verbose -eq 1 ]; then
			echo 
      echo " --- CORB HELP ---"
      echo
      echo " * USE: corb <files and options>"
      echo " ---> Example: corb file.txt -q doc.doc -v -rm text.txt"
      echo
      echo " * OPTIONS:"
      echo " -v:    verbose mode = from this point, prints all the actions done"
      echo " -q:    quiet mode = from this point, stops printing anything"
      echo " -rm:   remove mode = from this point, move the files to the corb"
      echo " -rt:   restore mode = from this point, restore the files from the corb"
      echo " -cl:   clean = clean the corb"
      echo " -ls:   list of files = shows the files in the corb (needs verbose)"
      echo " -h:    help = shows this help (needs verbose)"
      echo
      echo " ------ END ------"
		fi

  else
    if [ $remove -eq 1 ]; then
	    if [ ! -e $file ]; then
		    if [ $verbose -eq 1 ]; then
			    echo "Error: $file unknown" >&2
	  	  fi

	    else
		    mv -f $file $corb
		    if [ $verbose -eq 1 ]; then
			    echo "$file has been put in the corb."
		    fi
	    fi

    else
      if [ ! -e "$corb/$file" ]; then
		    if [ $verbose -eq 1 ]; then
			    echo "Error: $file unknown in the corb" >&2
	  	  fi

	    else
		    mv -f "$corb/$file" $PWD
		    if [ $verbose -eq 1 ]; then
			    echo "$file has been restored from the corb."
		    fi
	    fi
    fi
  fi
done

if [ $verbose -eq 1 ]; then
	echo
	corbsize=$(wc -w <<< $(ls $corb))
	if [ $corbsize -lt 2 ]; then
		echo There is $corbsize file in the corb.
	else
		echo There are $corbsize files in the corb.
	fi
	
	if [ $corbsize -gt 50 ]; then
		echo "(maybe it should be cleaned soon)"
	fi
fi
