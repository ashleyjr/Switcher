import subprocess


def main():
    stdout = subprocess.check_output("git rev-list master", shell=True)
    commits = stdout.split("\n")
    #for commit in commits:
    #    if(len(commit) > 10):
    #        cmd = "git checkout -f " + str(commit)
    #        print cmd
    #        stdout = subprocess.check_output(cmd, shell=True)
    cmd = "git checkout -f " + str(commits[0])
    subprocess.check_output(cmd, shell=True)                                    # Back top head

if __name__ == '__main__':
    main()