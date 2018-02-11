#!/bin/bash

if [ $1 = "build" ]; then
go build -o iot -i main.go
chmod +x iot
fi

if [ $1 = "install" ]; then
sudo mv iot /usr/bin/
fi

if [ $1 = "create" ]; then
mkdir $2
cd $2
mkdir test
touch test/sample.s
touch $2.go
cp ../manage.sh ./
cd ..
fi

if [ $1 = "test" ]; then
IOT test
fi