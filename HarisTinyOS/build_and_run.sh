#!/bin/bash

rm -rf x86_64_build && mkdir x86_64_build && cd x86_64_build && cmake ../source/ && make && clear && ./dummy_app
