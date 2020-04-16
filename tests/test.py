from pathlib import Path
import os
import subprocess
from shutil import copyfile
import sys

url = 'C:\\Users\\CubeSky\\OneDrive - Universidade de Lisboa\\Projectos\\AASMA\\Exercise\\cmake-build-debug\\Exercise.exe'
tests = 0
failed = 0
for path in Path('').rglob('*.txt'):
    if (path.name.endswith("input.txt")):
        tests += 1
        testName = path.parent.name + "/" + path.name
        f = open(path, 'r')
        outfile = open('out', "w")
        subprocess.run(url, input=f.read(), text=True, stdout=outfile)
        outfile.close()
        fileName = path.parent.name + "/" + path.name.replace("_input.txt", "") + "_output"
        target = open(fileName + ".txt", 'r')
        alternateName = fileName + "_alternative"
        outfile = open("out", 'r')
        if target.read().splitlines() == outfile.read().splitlines():
            print("Passed test: " + testName)
            outfile.close()
            continue
        outfile.seek(0)
        if os.path.isfile(alternateName + ".txt") and open(alternateName + ".txt", 'r').read().splitlines() == outfile.read().splitlines():
            print("Passed test: " + testName)
            outfile.close()
            continue
        print("Failed test: " + testName)
        myout = open("My" + path.parent.name + "/" + path.name.replace("_input.txt", "") + "_output.txt", 'w+')
        myout.close()
        copyfile("out", "My" + path.parent.name + "/" + path.name.replace("_input.txt", "") + "_output.txt")
        failed += 1

        outfile.close()
        os.remove("out")
print("\nFailed " + str(failed) + " of " + str(tests) + " tests.")
