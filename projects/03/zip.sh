#!/bin/bash

find . -name "*.hdl" -print | zip -j project03 -@
