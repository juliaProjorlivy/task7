#!/bin/bash

FILES=$(ls -lt graph/graph*.png | awk '{print $9}')
echo FILES: $FILES

echo "<html>" >> graph/index.html
echo "  <body>" >> graph/index.html
for f in $FILES
	do
		echo "      <img src="\"$f\""/>" | sed 's/graph\///' >> graph/index.html
        echo "      <br>" >> graph/index.html
	done
echo "  </body>" >> graph/index.html
echo "</html>" >> graph/index.html
