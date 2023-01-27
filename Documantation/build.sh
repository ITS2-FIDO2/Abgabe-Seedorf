#! /bin/bash
IFS='.' read -ra ADDR <<< $1
NAME="${ADDR[0]}"

if [[ "${ADDR[1]}" == "md" ]];
then
    pandoc $NAME.md -o $NAME.pdf --from markdown --template eisvogel --number-sections --listings
else
    echo "No .md file Provided"
fi