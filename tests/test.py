from pathlib import Path
import os
import subprocess
from shutil import copyfile


url = 'C:\\Users\\CubeSky\\OneDrive - Universidade de Lisboa\\Projectos\\AASMA\\Exercise\\cmake-build-debug\\Exercise.exe'
tests = 0
failed = 0
for path in Path('').rglob('*.txt'):
    if (path.name.endswith("input.txt")):
        tests += 1
        testName = path.parent.name + "/" + path.name
        f = open(path, 'r')
        outfile = open('out', "w")
        subprocess.run(url, input="\n".join(f.readlines()), text=True, stdout=outfile)
        outfile.close()
        target = open(path.parent.name + "/" + path.name.replace("_input.txt", "")+"_output.txt" , 'r')
        outfile = open("out", 'r')
        if target.readlines() != outfile.readlines():
            print("Failed test: " + testName)
            myout = open("My" + path.parent.name + "/" + path.name.replace("_input.txt", "")+"_output.txt", 'w+')
            myout.close()
            copyfile("out", "My" + path.parent.name + "/" + path.name.replace("_input.txt", "")+"_output.txt")
            failed += 1
        else:
            print("Passed test: " + testName)

        outfile.close()

print("\nFailed "+ str(failed) + " of " + str(tests) + " tests.")