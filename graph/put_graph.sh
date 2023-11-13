#!/bin/bash

FILES=$(ls -lt graph/graph*.png | awk '{print $9}')
cur_date_time=$(date)
counter=1
echo FILES: $FILES

echo "<html>" >> graph/index.html
echo "  <body>" >> graph/index.html
for f in $FILES
	do
		sed -n ${counter}p graph_info.txt >> graph/index.html
		echo "      <br>" >> graph/index.html
		((counter++))
		sed -n ${counter}p graph_info.txt >> graph/index.html
		echo "      <br>" >> graph/index.html
		echo "      <img src="\"$f\""/>" | sed 's/graph\///' >> graph/index.html
        echo "      <br>" >> graph/index.html
		((counter++))
	done
echo "  </body>" >> graph/index.html
echo "</html>" >> graph/index.html
