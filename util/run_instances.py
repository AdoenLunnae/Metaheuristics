#!/usr/bin/python3

from sys import argv
from subprocess import call
from os import path
from os.path import basename, realpath


def get_name(instance):
	result = basename(instance)
	return result.split('.')[0] + "_results.txt"


args = [realpath(x) for x in argv[1:]]
print(args)

for item in args[1:]:
	name = get_name(item)
	with open(name, 'w') as f:
		call([args[0], item, "3", item, "5"], stdout=f)

