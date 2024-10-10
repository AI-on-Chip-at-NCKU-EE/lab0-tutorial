#!/bin/bash

topdir=$(realpath $(dirname $0)/..)

eval "$(ssh-agent -s)"
ssh-add

read -p "Enter your username: " username
read -p "Enter your email: " email

cd $topdir/lab0
git config user.name $username
git config user.email $email

for i in {1..5}; do
    git clone ssh://git@aislab.ee.ncku.edu.tw:3175/aislab-internal/course/aoc/aoc2025/lab$i.git $topdir/lab$i
    cd $topdir/lab$i
    git config user.name $username
    git config user.email $email
done
