#!/usr/bin/bash

DIR=`dirname $0`
ROOT=`dirname $DIR`
python2 $DIR/doxy-coverage.py $ROOT/doc/xml | tail -n1 | grep -oe "^[0-9]\+"
