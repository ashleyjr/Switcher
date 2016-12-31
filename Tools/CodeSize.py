import subprocess
import os
import matplotlib.pyplot as plt

def main():
    os.chdir("..")
    print subprocess.check_output("cd", shell=True)
    stdout = subprocess.check_output("git rev-list master", shell=True)
    commits = stdout.split("\n")
    size = []
    try:
        for commit in commits:
            if(len(commit) > 10):
                cmd = "git checkout -f " + str(commit) + " Embedded\\Objects\\Switcher.build_log.htm"
                print cmd
                stdout = subprocess.check_output(cmd, shell=True)
            f = open('Embedded\\Objects\\Switcher.build_log.htm', 'r+')
            text = f.read()
            start = text.index("code=")
            start += 5
            found = ""
            while(True):
                if(text[start] == "\n"):
                    break
                else:
                    found += text[start]
                    start += 1
            size = [int(found)] + size
            f.close()
    except:
        print "error"
    print size
    line_x = [0,len(size)]
    line_y = [1024,1024]
    plt.plot(line_x,line_y)
    plt.plot(size)
    plt.ylabel('Code size (bytes)')
    plt.xlabel('Commit')
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    main()